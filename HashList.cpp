//
// Created by ZhangMing
//

#include "Worder.h"
#include <QString>
extern HashTable *hash;

/**
 * 函数名称: InitHash
 * 函数功能: 初始化哈希表
 * 输入参数: 无
 * 输出参数: int型值，成功返回1，失败返回0；
 *
 * 调用说明: 由DealData函数调用
 */
int InitHash(void)
{
    int i;
    hash = (HashTable *)malloc(sizeof(HashTable));
    hash->elem = (HashElem *)malloc(sizeof(HashElem) * HASH_TABLE_LENGTH);
    if (!hash || !(hash->elem))
    {
        printf("内存不足！\n");
        return 0;
    }
    hash->list_length = HASH_TABLE_LENGTH;
    hash->cur_length = 0;
    //初始化hash表
    for (i = 0; i < hash->list_length; i++)
    {
        hash->elem[i].count = 0;
        hash->elem[i].attribute = (WordAttr *)malloc(sizeof(WordAttr));
        hash->elem[i].attribute->next = NULL;
        hash->elem[i].next = NULL;
    }
    return 1;
}

/**
 * 函数名称: InsertHash
 * 函数功能: 将单词信息插入哈希表
 * 输入参数: word，pagenum，linenum，分别为读取到的单词和页码以及行数
 * 输出参数: 插入成功返回1，失败返回0
 *
 * 调用说明: 由DealData函数调用，调用Hash函数
 */
int InsertHash(char *word, int pagenum, int linenum)
{
    int value = Hash(word);
    int i;
    WordAttr *attr = (WordAttr *)malloc(sizeof(WordAttr));
    
    if (!hash->elem[value].count)
    {
        //哈希表中无此单词
        if (hash->cur_length == hash->list_length)
        {
            HashElem *newbase = (HashElem *)realloc(hash->elem, sizeof(HashElem) * (HASH_TABLE_LENGTH + ADDED_LENGTH));
            if (!newbase)
            {
                printf("内存不足！\n");
                return 0;
            }
            hash->elem = newbase;
            hash->list_length += ADDED_LENGTH;
            for (i = hash->cur_length; i < hash->list_length; i++)
            {
                hash->elem[i].count = 0;
                hash->elem[i].attribute = (WordAttr *)malloc(sizeof(WordAttr));
                hash->elem[i].attribute->next = NULL;
                hash->elem[i].next = NULL;
            }
            i = hash->cur_length;
        }
        
        hash->elem[value].count++;
        strcpy(hash->elem[value].word, word);
        attr->linenum = linenum;
        attr->pagenum = pagenum;
        attr->next = hash->elem[value].attribute->next;
        hash->elem[value].attribute->next = attr;
        hash->cur_length++;
    }
    else
    {
        if (!strcmp(hash->elem[value].word, word))
        {
            //出现重复单词
            hash->elem[value].count++;
            attr->linenum = linenum;
            attr->pagenum = pagenum;
            attr->next = hash->elem[value].attribute->next;
            hash->elem[value].attribute->next = attr;
        }
        else
        {
            //单词不同，存储地址相同，出现冲突
            HashElem *p;
            for (p = hash->elem[value].next; p != NULL; p = p->next)
            {
                if (!strcmp(p->word, word))
                {
                    p->count++;
                    attr->linenum = linenum;
                    attr->pagenum = pagenum;
                    attr->next = p->attribute->next;
                    p->attribute->next = attr;
                    return 1;
                }
            }
            p = (HashElem *)malloc(sizeof(HashElem));
            p->attribute = (WordAttr *)malloc(sizeof(WordAttr));
            p->attribute->next = NULL;
            p->count = 1;
            strcpy(p->word, word);
            
            attr->linenum = linenum;
            attr->pagenum = pagenum;
            attr->next = p->attribute->next;
            p->attribute->next = attr;
            
            p->next = hash->elem[value].next;
            hash->elem[value].next = p;
        }
    }
    return 1;
}

/**
 * 函数名称: SearchHashlist
 * 函数功能: 查找哈希表
 * 输入参数: searchword表示待搜索的单词
 * 输出参数: 查找成功返回1，失败返回-1
 *
 * 调用说明: 由Run函数调用，调用Hash函数
 */
HashElem *SearchHashlist(char *searchword)
{

    HashElem *p;
    int value = Hash(searchword);
    if (hash->elem[value].count > 0)
    {
        if (!strcmp(hash->elem[value].word, searchword) && hash->elem[value].count>0)
        {
            return &(hash->elem[value]);
        }
        for (p = hash->elem[value].next; p != NULL; p = p->next)
        {
            if (!strcmp(p->word, searchword) && p->count>0)
            {
                return p;
            }
        }
    }
    return NULL;
}

/**
 * 函数名称: DeleteHash
 * 函数功能: 删除哈希表中单词
 * 输入参数: searchword表示待删除的单词
 * 输出参数: 删除成功返回1，失败返回-1
 *
 * 调用说明: 由Run函数调用，调用Hash函数
 */
int DeleteHash(char *searchword)
{
    int value = Hash(searchword);
    HashElem *p;
    WordAttr *pattr, *qattr;
    if (hash->elem[value].count == 0)
    {
        return 0;
    }
    else
    {
        if (!strcmp(hash->elem[value].word, searchword))
        {
            hash->elem[value].count = 0;
            hash->cur_length--;
            pattr = hash->elem[value].attribute->next;
            qattr = pattr->next;
            while (pattr)
            {
                free(pattr);
                pattr = qattr;
                if (!pattr)
                {
                    break;
                }
                qattr = qattr->next;
            }
            return 1;
        }
        else
        {
            for (p = hash->elem[value].next; p != NULL; p = p->next)
            {
                if (!strcmp(p->word, searchword))
                {
                    p->count = 0;
                    hash->cur_length--;
                    pattr = p->attribute->next;
                    qattr = pattr->next;
                    while (pattr)
                    {
                        free(pattr);
                        pattr = qattr;
                        if (!pattr)
                        {
                            break;
                        }
                        qattr = qattr->next;
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

/**
 * 函数名称: TraverseHash
 * 函数功能: 遍历哈希表
 * 输入参数: 无
 * 输出参数: 无
 *
 * 调用说明: 由Run函数调用
 */
QString TraverseHashlist(void)
{
    int i;
    WordAttr *tmp;
    HashElem *p;
    int count = 0;
    QString re = "";
    for (i = 0; i < hash->list_length; i++)
    {
        if (hash->elem[i].count)
        {
            count++;
            re += QString::number(count,10)+".单词："+QString(QLatin1String(hash->elem[i].word))+" value="+QString::number(i,10)+"\n";
            for (tmp = hash->elem[i].attribute->next; tmp != NULL; tmp = tmp->next)
            {
                re += "页码:"+QString::number(tmp->pagenum,10)+"\t行数:"+QString::number(tmp->linenum,10)+"\n";
            }
            re +=  "出现次数:"+QString::number(hash->elem[i].count,10)+"\n\n";
            for (p = hash->elem[i].next; p != NULL; p = p->next)
            {
                if (p->count) //检验单词是否被删
                {
                    count++;
                    re += QString::number(count,10)+".单词："+QString(QLatin1String(p->word))+" value="+QString::number(i,10)+"\n";
                    for (tmp = p->attribute->next; tmp != NULL; tmp = tmp->next)
                    {
                        re += "页码:"+QString::number(tmp->pagenum,10)+"\t行数:"+QString::number(tmp->linenum,10)+"\n";
                    }
                    re +=  "出现次数:"+QString::number(p->count,10)+"\n\n";
                }
            }
        }
    }
    re +="遍历结束！\n";
    return re;
}

/**
 * 函数名称: DestroyHash
 * 函数功能: 销毁哈希表
 * 输入参数: 无
 * 输出参数: int型值，销毁成功返回1，失败返回0
 *
 * 调用说明: 由Run函数调用
 */
int DestroyHash(void)
{
//    if (!hash)
//    {
//        printf("无哈希表！\n");
//        return 0;
//    }
    int i;
    WordAttr *pattr, *qattr;
    HashElem *pelem, *qelem;
    for (i = 0; i < hash->list_length; i++)
    {
        if (hash->elem[i].count)
        {
            pattr = hash->elem[i].attribute->next;
            qattr = pattr->next;
            //释放哈希表单词
            while (pattr)
            {
                free(pattr);
                pattr = qattr;
                if (!pattr)
                {
                    break;
                }
                qattr = qattr->next;
            }
            if (!hash->elem[i].next) //该地址只有一个单词, 无冲突
                continue;
            pelem = hash->elem[i].next;
            qelem = pelem->next;
            while (pelem)
            {
                pattr = pelem->attribute->next;
                qattr = pattr->next;
                while (pattr)
                {
                    free(pattr);
                    pattr = qattr;
                    if (!pattr)
                    {
                        break;
                    }
                    qattr = qattr->next;
                }
                free(pelem);
                pelem = qelem;
                if (!pelem)
                {
                    break;
                }
                qelem = qelem->next;
            }
        }
    }
    free(hash->elem);
    hash->elem = NULL;
    free(hash);
    hash = NULL;
    return 1;
}

/**
 * 函数名称: Hash
 * 函数功能: 哈希函数，处理key值，返回value值
 * 输入参数: key，哈希表索引
 * 输出参数: int型值，哈希之后的value值
 *
 * 调用说明: 由各哈希数据处理函数调用
 */
int Hash(char *key)
{
    int res = 0;
    char *p = key;
    while (*p)
    {
        res += *p + (p - key) * (*p++);
    }
    return res % HASH_TABLE_LENGTH;
}

/**
 * 函数名称: AnalyzaHashlist
 * 函数功能: 分析哈希函数哈希之后哈希表的疏密程度和冲突数
 * 输入参数: 无
 * 输出参数: 无
 *
 * 调用说明: 由Run函数调用
 */
QString AnalyzeHashlist(void)
{
    HashElem *p;
    int i;
    int count = 0;
    QString string = "";
    for (i = 0; i < hash->list_length; i++)
    {
        count = 0;
        if (hash->elem[i].count)
        {
            string += "\n";
            string += "索引："+QString::number(i,10)+"\n";
            for (p = hash->elem[i].next; p != NULL; p = p->next)
            {
                count++;
            }
            string += "冲突数："+QString::number(count,10)+"\n";
        }
    }
    string += "分布较为均匀，冲突数较少\n";
    return string;
}
