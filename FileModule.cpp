//
// Created by ZhangMing
//

#include "Worder.h"
extern SearchList *list;
extern SearchList *sortlist;
extern HashTable *hash;

/**
 * 函数名称: ExportToFile
 * 函数功能: 根据选择将静态表或哈希表导出为文本文件
 * 输入参数: choice，用户选择,filename,文件名
 * 输出参数: int型值，导出成功返回1，失败返回-1
 *
 * 调用说明: 由Run函数调用
 */
int ExportToFile(int choice,char *filename)
{
    FILE *fp;
    WordAttr *p;
    
    if (choice == 1) //保存静态表中的数据
    {
        fp = fopen(filename, "w");
        if (!fp)
        {
            return -1;
        }
        for (int i = 0; i < list->cur_length; i++)
        {
            p = list->elem[i].attribute->next;
            fprintf(fp, "%s %d\n", list->elem[i].word, list->elem[i].count);
            
            while (p)
            {
                fprintf(fp, "%d %d\n", p->pagenum, p->linenum);
                p = p->next;
            }
        }
        fclose(fp);
        return 1;
    }
    else if (choice == 2)
    {
        //hash
        fp = fopen(filename, "w");
        HashElem *q;
        for (int i = 0; i < hash->list_length; i++)
        {
            if (!fp)
            {
                return -1;
            }
            if (hash->elem[i].count != 0)
            {
                fprintf(fp, "%s %d\n", hash->elem[i].word, hash->elem[i].count);
                p = hash->elem[i].attribute->next;
                while (p)
                {
                    fprintf(fp, "%d %d\n", p->pagenum, p->linenum);
                    p = p->next;
                }
                for (q = hash->elem[i].next; q != NULL; q = q->next)
                {
                    fprintf(fp, "%s %d\n", q->word, q->count);
                    p = q->attribute->next;
                    while (p)
                    {
                        fprintf(fp, "%d %d\n", p->pagenum, p->linenum);
                        p = p->next;
                    }
                }
            }
        }
        fclose(fp);
        return 1;
    }
    else if (choice == 3)
    {
        //sortlist
        fp = fopen(filename, "w");
        if (!fp)
        {
            return -1;
        }
        for (int i = 0; i < sortlist->cur_length; i++)
        {
            p = sortlist->elem[i].attribute->next;
            fprintf(fp, "%s %d\n", sortlist->elem[i].word, sortlist->elem[i].count);
            
            while (p)
            {
                fprintf(fp, "%d %d\n", p->pagenum, p->linenum);
                p = p->next;
            }
        }
        fclose(fp);
        return 1;
    }
    return 1;
}

/**
 * 函数名称: LoadFromFile
 * 函数功能: 根据选择将文本文件导入为静态表或哈希表
 * 输入参数: choice，用户选择
 * 输出参数: int型值，导入成功返回1，失败返回-1
 *
 * 调用说明: 由Run函数调用
 */
int LoadFromFile(int choice, char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (!fp)
    {
        return -1;
    }
    char word[WORD_MAX_LENGTH];
    int pagenum, linenum;
    int count;
    //建立静态表
    if (choice == 1)
    {
        if (InitList())
        {
            while (!feof(fp))
            {
                fscanf(fp, "%s %d\n", word, &count);
                while (fscanf(fp, "%d %d\n", &pagenum, &linenum) == 2)
                {
                    //当读取到单词时fscanf返回0，跳出循环
                    Create(word, pagenum, linenum);
                }
            }
            fclose(fp);
            return 1;
        }
        fclose(fp);
        return -1;
    }
    //建立哈希表
    else if (choice == 2)
    {
        if (InitHash())
        {
            while (!feof(fp))
            {
                fscanf(fp, "%s %d\n", word, &count);
                while (fscanf(fp, "%d %d\n", &pagenum, &linenum) == 2)
                {
                    //当读取到单词时fscanf返回0，跳出循环
                    InsertHash(word, pagenum, linenum);
                }
            }
            fclose(fp);
            return 1;
        }
    }
    //建立排序表
    else if (choice == 3)
    {
        int i;
        WordAttr *attr;
        sortlist = (SearchList *)malloc(sizeof(SearchList));
        sortlist->elem = (WordAndCount *)malloc(sizeof(WordAndCount) * (sortlist->list_length));
        
        if (!sortlist || !(sortlist->elem))
        {
            return -1;
        }
        sortlist->list_length = LIST_BASE_LENGTH;
        sortlist->cur_length = 0;
        for (i = 0; i < sortlist->list_length; i++)
        {
            sortlist->elem[i].count = 0;
            sortlist->elem[i].attribute = (WordAttr *)malloc(sizeof(WordAttr));
            sortlist->elem[i].attribute->next = NULL;
        }
        for (i = 0; !feof(fp); i++)
        {
            if (sortlist->cur_length == sortlist->list_length)
            {
                WordAndCount *newbase = (WordAndCount *)realloc(sortlist->elem, sizeof(WordAndCount) * (sortlist->list_length + ADDED_LENGTH));
                if (!newbase)
                {
                    return -1;
                }
                sortlist->elem = newbase;
                sortlist->list_length += ADDED_LENGTH;
                for (i = sortlist->cur_length; i < sortlist->list_length; i++)
                {
                    sortlist->elem[i].count = 0;
                    sortlist->elem[i].attribute = (WordAttr *)malloc(sizeof(WordAttr));
                    sortlist->elem[i].attribute->next = NULL;
                }
                i = sortlist->cur_length;
            }
            
            fscanf(fp, "%s %d\n", word, &count);
            strcpy(sortlist->elem[i].word, word);
            sortlist->elem[i].count = count;
            sortlist->cur_length++;
            while (fscanf(fp, "%d %d\n", &pagenum, &linenum) == 2)
            {
                //当读取到单词时fscanf返回0，跳出循环
                attr = (WordAttr *)malloc(sizeof(WordAttr));
                attr->linenum = linenum;
                attr->pagenum = pagenum;
                attr->next = sortlist->elem[i].attribute->next;
                sortlist->elem[i].attribute->next = attr;
            }
        }
        fclose(fp);
        return 1;
    }
    return 1;
}
