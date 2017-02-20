//
// Created by ZhangMing
//

#include "Worder.h"
extern SearchList *list;
extern SearchList *sortlist;
extern HashTable *hash;

/**
 * 函数名称: DealData
 * 函数功能: 逐行逐页读取并处理数据，
 *          同时根据选择创建静态表或哈希表
 * 输入参数: choice，用户对于创建不同表的选择
 * 输出参数: int型值，1表示创建成功，0表示失败
 *
 * 调用说明: 由Run函数调用，调用初始化和创建函数
 */
int DealData(int choice, char *filename)
{
    if (choice == 1)
        InitList();
    else if (choice == 2)
        InitHash();
    FILE *fp;
    int pagenum = 1, linenum = 0;
    int a = 1;
    int isLink = 0;
    char word[WORD_MAX_LENGTH + 1]; //存储每一个单词
    char perline[LINE_MAX_LENGTH + 1]; //存储读取的一行内容
    char *p = perline; //指向一行内容的指针
    char *pword = word;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("打开文件失败！\n");
        return 0;
    }
    while (fgets(perline, LINE_MAX_LENGTH, fp))
    {
        linenum++;
        p = perline;
        if (*p == '\n') continue; //处理空行
        while (a)
        {
            while (!isalpha(*p)) //处理单词前的非字母字符
            {
                p++;
                if (*p == '\n')
                    break;
            }
            if (*p == '\n')
                break;
            if (isLink) //处理连字符
            {
                char linkword[WORD_MAX_LENGTH + 1]; //存储连字符的下一行单词
                sscanf(p, "%s", linkword);
                char *plinkword = linkword;
                while (isalpha(*plinkword) && *plinkword != '\0')
                {
                    plinkword++;
                    p++;
                }
                *plinkword = '\0';
                strcat(word, linkword); //连接两单词
                if (choice == 1)
                {
                    if (!Create(word, pagenum, linenum))
                    {
                        printf("读取单词失败！\n");
                        return 0;
                    }
                }
                else if (choice == 2)
                {
                    if (!InsertHash(word, pagenum, linenum))
                    {
                        printf("读取单词失败！\n");
                        return 0;
                    }
                }
                if (*p == '\n')
                    break;
                while (!isalpha(*p) && *p != '\n') //处理单词前的非字母字符
                    p++;
                if (*p == '\n')
                    break;
            }
            a = sscanf(p, "%s", word);//word[]最大存储30个字母
            pword = word;
            while (1)
            {
                if (*p == '\n')
                {
                    isLink = 0;
                    break;
                }
                p++;
                if (!isalpha(*pword++)) //处理所取词中单词后的非字母字符
                {
                    pword--;
                    if (*pword == '-' && *p == '\n')
                        isLink = 1; //最后一个单词后面有连字符，不管破折号，默认破折号是--
                    else
                        isLink = 0;
                    *pword = '\0';
                    break;
                }
            }
            if (isLink) //若本句最后是连字符，则break到下一行读取数据
                break;
            word[WORD_MAX_LENGTH] = '\0';
            if (choice == 1)
            {
                if (!Create(word, pagenum, linenum))
                {
                    printf("读取单词失败！\n");
                    return 0;
                }
            }
            else if (choice == 2)
            {
                if (!InsertHash(word, pagenum, linenum))
                {
                    printf("读取单词失败！\n");
                    return 0;
                }
            }
            if (*p == '\n')
                break;
        }
        a = 1;
        if (linenum >= MAX_LINES_ONE_PAGE)
        {
            pagenum++;
            linenum = 0;
        }
    }
    fclose(fp);
    return 1;
}
