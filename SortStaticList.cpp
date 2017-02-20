//
// Created by ZhangMing
//

#include "Worder.h"
extern SearchList *sortlist;
extern SearchList *list;

/**
 * 函数名称: BuildSortlist
 * 函数功能: 初始化并建立待排序的静态表
 * 输入参数: 无
 * 输出参数: int型值，1表示建立成功，0表示失败
 *
 * 调用说明: 由Sort函数调用
 */
int BuildSortlist(void)
{
    int i;
    WordAttr *attr, *p;
    sortlist = (SearchList *)malloc(sizeof(SearchList));
    sortlist->elem = (WordAndCount *)malloc(sizeof(WordAndCount) * (list->list_length));
    if (!sortlist || !(sortlist->elem))
    {
        printf("内存不足！\n");
        return 0;
    }
    sortlist->list_length = list->list_length;
    sortlist->cur_length = list->cur_length;
    //同步线性表
    for (i = 0; i < list->list_length; i++)
    {
        sortlist->elem[i].attribute = (WordAttr *)malloc(sizeof(WordAttr));
        sortlist->elem[i].attribute->next = NULL;
        sortlist->elem[i].count = list->elem[i].count;
        strcpy(sortlist->elem[i].word, list->elem[i].word);
        p = list->elem[i].attribute->next;
        for (; p != NULL; p = p->next)
        {
            attr = (WordAttr *)malloc(sizeof(WordAttr));
            attr->linenum = p->linenum;
            attr->pagenum = p->pagenum;
            attr->next = sortlist->elem[i].attribute->next; //后进先出建立链表
            sortlist->elem[i].attribute->next = attr;
        }
    }
    Sort();
    return 1;
}

/**
 * 函数名称: Sort
 * 函数功能: 快速排序静态表
 * 输入参数: 无
 * 输出参数: int型值，1表示排序成功，0表示失败
 *
 * 调用说明: 由Run函数调用，调用BuildSorlist函数，QSort函数
 */
int Sort(void)
{
    QSort(1, sortlist->cur_length);
    return 1;
}

/**
 * 函数名称: QSort
 * 函数功能: 递归快速排序
 * 输入参数: low，high表示静态表索引
 * 输出参数: 无
 *
 * 调用说明: 由Sort函数调用，递归调用QSort函数，调用Partition函数
 */
void QSort(int low, int high)
{
    if (low < high)
    {
        int pivotloc = Partition(low, high);
        QSort(low, pivotloc - 1);
        QSort(pivotloc + 1, high);
    }
}

/**
 * 函数名称: Partition
 * 函数功能: 排序静态表
 * 输入参数: low，high表示静态表索引
 * 输出参数: int型值，low，表示快排每次的标定值
 *
 * 调用说明: 由QSort函数调用
 */
int Partition(int low, int high)
{
    WordAndCount pivotkey = sortlist->elem[low - 1];
    while (low < high)
    {
        while (low < high && strcmp(sortlist->elem[high - 1].word, pivotkey.word) >= 0)
        {
            high--;
        }
        sortlist->elem[low - 1] = sortlist->elem[high - 1];
        while (low < high && strcmp(sortlist->elem[low - 1].word, pivotkey.word) <= 0)
        {
            low++;
        }
        sortlist->elem[high - 1] = sortlist->elem[low - 1];
    }
    sortlist->elem[low - 1] = pivotkey;
    return low;
}

/**
 * 函数名称: SearchBin
 * 函数功能: 二分查找
 * 输入参数: searchword表示待搜索的单词
 * 输出参数: int型值，mid表示搜索到该单词并返回索引，失败返回-1
 *
 * 调用说明: 由Run函数调用
 */
int SearchBin(char *searchword)
{
    int low = 0, high = sortlist->cur_length - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (strcmp(sortlist->elem[mid].word, searchword) == 0)
        {
            return mid; //找到该单词并返回
        }
        else if (strcmp(sortlist->elem[mid].word, searchword) < 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1; //未找到此单词
}

/**
 * 函数名称: DestroySortlist
 * 函数功能: 删除有序表
 * 输入参数: 无
 * 输出参数: 无
 *
 * 调用说明: 由Run函数调用
 */
int DestroySortlist(void)
{
//    if (!sortlist)
//    {
//        printf("排序表不存在！\n");
//        return 0;
//    }
    WordAttr *p, *q;
    for (int i = 0; i < sortlist->cur_length; i++)
    {
        p = sortlist->elem[i].attribute->next;
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
    free(sortlist->elem);
    sortlist->elem = NULL;
    free(sortlist);
    sortlist = NULL;
    return 1;
}

/**
 * 函数名称: TraverseSortlist
 * 函数功能: 遍历有序表
 * 输入参数: 无
 * 输出参数: 无
 *
 * 调用说明: 由Run函数调用
 */
QString TraverseSortlist(void)
{
    QString re;
    for (int i = 0; i < sortlist->cur_length; i++)
    {
        WordAttr *tmp;
        re += QString::number(i+1,10)+".单词："+QString(QLatin1String(sortlist->elem[i].word))+"\n";
        for (tmp = sortlist->elem[i].attribute->next; tmp != NULL; tmp = tmp->next)
        {
            re += "页码:"+QString::number(tmp->pagenum,10)+"\t行数:"+QString::number(tmp->linenum,10)+"\n";
        }
        re +=  "出现次数:"+QString::number(sortlist->elem[i].count,10)+"\n\n";
    }
    re +="遍历结束！\n";
    return re;
}
