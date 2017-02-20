//
// Created by ZhangMing
//

#ifndef _WORDER_H_
#define _WORDER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <QString>

#define LINE_MAX_LENGTH 500		 //每行读取的长度 500
#define MAX_LINES_ONE_PAGE 100	 //每页读取的最多行数//
#define WORD_MAX_LENGTH 30		 //单词的最大长度
#define LIST_BASE_LENGTH 5000	 //线性表初始长度//
#define ADDED_LENGTH 20			 //表每次增加的长度//
#define HASH_TABLE_LENGTH 1000	 //哈希表初始化长度//

/* ---------------------静态表结构--------------------- */

/* 单词页码和行号属性节点 */
typedef struct wordattr
{
    int pagenum;				 //该单词出现的页码
    int linenum;				 //该单词出现的行号
    struct wordattr *next;		 //指向下一个相同单词的属性节点
}WordAttr;

/* 单词出现的数目及单词内容节点 */
typedef struct wordandcount
{
    int count;					 //该单词出现的次数
    char word[WORD_MAX_LENGTH];	 //该单词内容
    WordAttr *attribute;		 //指向该单词所在的行号和页码
}WordAndCount;

/* 静态表结构 */
typedef struct searchlist
{
    int list_length;		     //查找表总表长
    int cur_length;		         //查找表当前(已用)长度
    WordAndCount *elem;	         //查找表元素类型
}SearchList;

/* ---------------------哈希表结构--------------------- */

/* 哈希表元素节点结构 */
typedef struct hashelem
{
    char word[WORD_MAX_LENGTH];  //该单词内容
    int count;				     //该单词出现的次数
    WordAttr *attribute;         //指向该单词所在的行号和页码
    struct hashelem *next;       //链地址法处理的下一个单词
}HashElem;

/* 哈希表结构 */
typedef struct hashtable
{
    HashElem *elem;			     //哈希表元素类型
    int cur_length;			     //哈希表当前长度
    int list_length;             //哈希表总表长
}HashTable;

/* ---------------------效率比较结构--------------------- */

typedef struct timecompare
{
    //建表时间
    double CreateTimeList;
    double CreateTimeHash;
    //查找时间
    double SearchTimeList;
    double SearchTimeHash;
    //遍历时间
    double TraverseTimeList;
    double TraverseTimeHash;
}TimeCompare;

/* -----------------------全局变量----------------------- */

/* --------------------静态表相关函数--------------------- */

int Create(char *word, int pagenum, int linenum);		 /*创建静态表*/
int InitList(void);										 /*初始化静态表*/
int Search(char *searchword);							 /*搜索静态表中待搜索的单词信息*/
void ShowInfo(WordAndCount *res);						 /*显示单词各信息*/
int Destroy(void);										 /*销毁静态表*/
QString Traverse(void);									 /*遍历静态表*/

/* --------------------有序表相关函数--------------------- */

int BuildSortlist(void);								 /*初始化并建立待排序的静态表*/
int Sort(void);											 /*快速排序静态表*/
void QSort(int low, int high);							 /*递归快速排序*/
int Partition(int low, int high);						 /*排序静态表*/
int SearchBin(char *searchword);						 /*二分查找*/
int DestroySortlist(void);								 /*删除有序表*/
QString TraverseSortlist(void);							 /*遍历有序表*/

/* --------------------哈希表相关函数--------------------- */

int InitHash(void);										 /*初始化哈希表*/
int InsertHash(char *word, int pagenum, int linenum);	 /*将单词信息插入哈希表*/
int DestroyHash(void);									 /*销毁哈希表*/
HashElem *SearchHashlist(char *searchword);						 /*查找哈希表*/
int DeleteHash(char *searchword);						 /*删除哈希表中单词*/
QString TraverseHashlist(void);								 /*遍历哈希表*/
int Hash(char *key);									 /*哈希函数，处理key值，返回value值*/
QString AnalyzeHashlist(void);                           /*哈希函数分析*/

/* ---------------------数据处理函数--------------------- */

int DealData(int choice, char *filename);/*逐行逐页读取并处理数据，同时根据选择创建静态表或哈希表*/
void Run(void);											 /*启动程序*/
int ExportToFile(int choice,char *filename);							 /*根据选择将静态表或哈希表导出为文本文件*/
int LoadFromFile(int choice, char *filename);							 /*根据选择将文本文件导入为静态表或哈希表*/
QString Analyze(void);								 /*分析对比两种表的查找性能*/

/* ---------------------------------------------------- */

#endif //_WORDER_H_
