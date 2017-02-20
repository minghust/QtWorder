//
// Created by ZhangMing
//

#include "Worder.h"

extern TimeCompare comparetime;
extern SearchList *list;
extern HashTable *hash;

/**
 * 函数名称: Analyze
 * 函数功能: 测试对比分析两种查找表性能
 * 输入参数: 无
 * 输出参数: 无
 *
 * 调用说明: 由Run函数调用
 */
QString Analyze(void)
{
    QString string = "";
    string += "-------------比较结果--------------\n-----------------------------------\n-----------建表时间比较-------------\n";
    if (list && hash)
    {
        string += "静态表："+QString::number(comparetime.CreateTimeList)+"毫秒\n";
        string += "哈希表："+QString::number(comparetime.CreateTimeHash)+"毫秒\n\n";
    }
    else
    {
        string += "静态表和哈希表未完全建立！\n\n";
    }
    string += "-----------查找时间比较-------------\n";
    if (list && hash)
    {
        string += "静态表："+QString::number(comparetime.SearchTimeList)+"毫秒\n";
        string += "哈希表："+QString::number(comparetime.SearchTimeHash)+"毫秒\n\n";
    }
    else
    {
        string += "静态表和哈希表未完全建立！\n\n";
    }
    string += "-----------遍历时间比较-------------\n";
    if (list && hash)
    {
        string += "静态表："+QString::number(comparetime.TraverseTimeList)+"毫秒\n";
        string += "哈希表："+QString::number(comparetime.TraverseTimeHash)+"毫秒\n\n";
    }
    else
    {
        string += "静态表和哈希表未完全建立！\n\n";
    }
    string += "-----------------------------------\n-------------比较结束--------------\n";
    return string;
}
