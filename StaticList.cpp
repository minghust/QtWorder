//
// Created by ZhangMing
//

#include "Worder.h"
extern SearchList *list;

/**
 * 函数名称: InitList
 * 函数功能: 初始化静态表
 * 输入参数: 无
 * 输出参数: int型值，1表示初始化成功，0表示失败
 *
 * 调用说明: 由DealData函数调用
 */
int InitList(void)
{
    int i;
    list = (SearchList *)malloc(sizeof(SearchList));
    list->elem = (WordAndCount *)malloc(sizeof(WordAndCount) * LIST_BASE_LENGTH);
    if (!list || !(list->elem))
    {
        printf("内存不足！\n");
        return 0;
    }
    list->list_length = LIST_BASE_LENGTH;
    list->cur_length = 0;
    //初始化线性表
    for (i = 0; i < list->list_length; i++)
    {
        list->elem[i].count = 0;
        list->elem[i].attribute = (WordAttr *)malloc(sizeof(WordAttr));
        list->elem[i].attribute->next = NULL;
    }
    return 1;
}

/**
 * 函数名称: Create
 * 函数功能: 创建静态表
 * 输入参数: word，pagenum，linenum，分别为读取到的单词和页码以及行数
 * 输出参数: int型值，1表示创建成功，0表示失败
 *
 * 调用说明: 由DealData函数调用
 */
int Create(char *word, int pagenum, int linenum)
{
    WordAttr *attr;
    int i = 0;
    /* 遍历线性表，查找相同单词 */
    for (i = 0; i < list->cur_length; i++)
    {
        if (!strcmp(list->elem[i].word, word))//如果静态表中有该单词，则将该单词属性插入该单词的属性链表中
        {
            list->elem[i].count++;
            attr = (WordAttr *)malloc(sizeof(WordAttr));
            attr->linenum = linenum;
            attr->pagenum = pagenum;
            attr->next = list->elem[i].attribute->next; //后进先出建立链表
            list->elem[i].attribute->next = attr;
            return 1;
        }
    }
    
    if (list->cur_length == list->list_length)
    {
        WordAndCount *newbase = (WordAndCount *)realloc(list->elem, sizeof(WordAndCount) * (list->list_length + ADDED_LENGTH));
        if (!newbase)
        {
            printf("内存不足！\n");
            return 0;
        }
        list->elem = newbase;
        list->list_length += ADDED_LENGTH;
        for (i = list->cur_length; i < list->list_length; i++)
        {
            list->elem[i].count = 0;
            list->elem[i].attribute = (WordAttr *)malloc(sizeof(WordAttr));
            list->elem[i].attribute->next = NULL;
        }
        i = list->cur_length;
    }
    
    /* 无相同单词 */
    list->elem[i].count++;
    strcpy(list->elem[i].word, word);
    attr = (WordAttr *)malloc(sizeof(WordAttr));
    attr->linenum = linenum;
    attr->pagenum = pagenum;
    attr->next = list->elem[i].attribute->next; //后进先出建立链表
    list->elem[i].attribute->next = attr;
    list->cur_length++;
    
    //printf("%s\n", list->elem[i].word);
    return 1;
}

/**
 * 函数名称: Destroy
 * 函数功能: 销毁静态表
 * 输入参数: 无
 * 输出参数: int型值，1表示销毁成功，0表示失败
 *
 * 调用说明: 由DealData函数调用
 */
int Destroy(void)
{
//    if (!list)
//    {
//        printf("静态表不存在！\n");
//        return 0;
//    }
    WordAttr *p, *q;
    for (int i = 0; i < list->cur_length; i++)
    {
        p = list->elem[i].attribute->next;
        q = p->next;
        while (p)
        {
            free(p);
            p = q;
            if (!p)
            {
                break;
            }
            q = q->next;
        }
    }
    free(list->elem);
    list->elem = NULL;
    free(list);
    list = NULL;
    return 1;
}

/**
 * 函数名称: Search
 * 函数功能: 搜索静态表中待搜索的单词信息
 * 输入参数: 待搜索的单词
 * 输出参数: int型值，成功返回单词在静态表中的索引，失败返回-1
 *
 * 调用说明: 由Run函数调用
 */
int Search(char *searchword)
{
    int i;
    
    for (i = 0; i < list->cur_length; i++)
    {
        if (!strcmp(list->elem[i].word, searchword))
        {
            return i;
        }
    }
    return -1;
}

/**
 * 函数名称: ShowInfo
 * 函数功能: 显示单词各信息
 * 输入参数: 静态查找表元素信息
 * 输出参数: 无
 *
 * 调用说明: 由Run函数调用
 */
void ShowInfo(WordAndCount *res)
{
    WordAndCount *con = res;
    WordAttr *tmp;
    printf("单词 %s:\n", con->word);
    
    for (tmp = con->attribute->next; tmp != NULL; tmp = tmp->next)
    {
        printf("页码:%d\t行数:%d\n", tmp->pagenum, tmp->linenum);
    }
    printf("出现次数:%d\n", con->count);
    putchar('\n');
}

/**
 * 函数名称: Traverse
 * 函数功能: 遍历静态表
 * 输入参数: 无
 * 输出参数: 无
 *
 * 调用说明: 由Run函数调用
 */
QString Traverse(void)
{
    QString re;
    for (int i = 0; i < list->cur_length; i++)
    {
        WordAttr *tmp;
        re += QString::number(i+1,10)+".单词："+QString(QLatin1String(list->elem[i].word))+"\n";
        for (tmp = list->elem[i].attribute->next; tmp != NULL; tmp = tmp->next)
        {
            re += "页码:"+QString::number(tmp->pagenum,10)+"\t行数:"+QString::number(tmp->linenum,10)+"\n";
        }
        re +=  "出现次数:"+QString::number(list->elem[i].count,10)+"\n\n";

    }
    re +="遍历结束！\n";
    return re;
}
