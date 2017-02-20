//
// Created by ZhangMing
//

#include "Worder.h"
extern SearchList *list;
extern SearchList *sortlist;
extern HashTable *hash;
extern TimeCompare comparetime;
/**
 * 函数名称: Run
 * 函数功能: 启动程序
 * 输入参数: 无
 * 输出参数: 无
 *
 * 调用说明: main函数调用，同时调用各处理函数
 */
void Run(void)
{
    clock_t start, finish; //计算算法时间
    int choice;
    int a = 1;
    char searchword[WORD_MAX_LENGTH];
    
    while (a)
    {
        system("clear");
        printf("\n\n");
        printf("  |-------------------------------------------------------|\n");
        printf("  |                       单词索引                        |\n");
        printf("  |-------------------------------------------------------|\n");
        printf("  |  	  1. 建立静态表       |      10. 哈希表查找       |\n");
        printf("  |  	  2. 建立哈希表       |      11. 删除表单词       |\n");
        printf("  |  	  3. 查找静态表       |      12. 遍历哈希表       |\n");
        printf("  |  	  4. 遍历静态表       |      13. 删除哈希表       |\n");
        printf("  |  	  5. 删除静态表       |      14. 哈希表分析       |\n");
        printf("  |       6. 建立有序表       |      15. 导入至文件       |\n");
        printf("  |       7. 有序表查找       |      16. 从文件恢复       |\n");
        printf("  |       8. 删除有序表       |      17. 表性能分析       |\n");
        printf("  |       9. 遍历有序表       |      0.  退出本程序       |\n");
        printf("  |-------------------------------------------------------|\n");
        printf("  请选择你的操作[0~17]:");
        
        scanf("%d", &a);
        if (a >= 3 && a <= 6)
        {
            if (!list)
            {
                printf("未建立静态表！\n");
                getchar(); getchar();
                continue;
            }
        }
        else if (a>=7 && a<=9)
        {
            if (!sortlist)
            {
                printf("未建立有序表！\n");
                getchar(); getchar();
                continue;
            }
        }
        else if (a >= 10 && a <= 14)
        {
            if (!hash)
            {
                printf("未建立哈希表！\n");
                getchar(); getchar();
                continue;
            }
        }
        switch (a)
        {
            case 0:
                printf("已退出程序！\n");
                exit(0);
            case 1:
                start = clock();
                if (list)
                {
                    printf("静态表已存在！\n");
                    getchar(); getchar();
                    break;
                }
                if (DealData(a))
                    printf("静态表建立成功！\n");
                else
                    printf("静态表建立失败！\n");
                finish = clock();
                comparetime.CreateTimeList = (double)((finish - start) / CLOCKS_PER_SEC);
                getchar(); getchar();
                break;
            case 2:
                start = clock();
                if (hash)
                {
                    printf("哈希表已存在！\n");
                    getchar(); getchar();
                    break;
                }
                if (DealData(a))
                    printf("哈希表建立成功！\n");
                else
                    printf("哈希表建立失败！\n");
                finish = clock();
                comparetime.CreateTimeHash = (double)((finish - start) / CLOCKS_PER_SEC);
                getchar(); getchar();
                break;
            case 3:
                printf("输入待查询单词：");
                scanf("%s", searchword);
                
                start = clock();
                a = Search(searchword);
                finish = clock();
                comparetime.SearchTimeList = (double)((finish - start) / CLOCKS_PER_SEC);
                if (a < 0)
                {
                    printf("无此单词！\n");
                    getchar(); getchar();
                    break;
                }
                ShowInfo(&(list->elem[a]));
                printf("\n查找时间：%f seconds\n", comparetime.SearchTimeList);
                getchar(); getchar();
                break;
            case 4:
                start = clock();
                Traverse();
                finish = clock();
                comparetime.TraverseTimeList = (double)((finish - start) / CLOCKS_PER_SEC);
                getchar(); getchar();
                break;
            case 5:
                start = clock();
                if (Destroy())
                {
                    printf("表删除成功！\n");
                    finish = clock();
                    comparetime.DestroyTimeList = (double)((finish - start) / CLOCKS_PER_SEC);;
                }
                
                getchar(); getchar();
                break;
            case 6:
                if (!BuildSortlist())
                {
                    printf("有序表建立失败！\n");
                    return;
                }
                else
                {
                    printf("有序表建立成功！\n");
                }
                getchar(); getchar();
                break;
                break;
            case 7:
                printf("输入待查询单词：");
                scanf("%s", searchword);
                
                start = clock();
                a = SearchBin(searchword);
                finish = clock();
                if (a < 0)
                {
                    printf("无此单词！\n");
                    getchar(); getchar();
                    break;
                }
                ShowInfo(&(sortlist->elem[a]));
                printf("\n查找时间：%f seconds\n", (double)((finish - start) / CLOCKS_PER_SEC));
                getchar(); getchar();
                break;
            case 8:
                if (DestroySortlist())
                    printf("表删除成功！\n");
                getchar(); getchar();
                break;
            case 9:
                TraverseSortlist();
                getchar(); getchar();
                break;
            case 10:
                start = clock();
                printf("输入待查询的单词：");
                scanf("%s", searchword);
                a = SearchHash(searchword); //单词属性在该函数中显示
                finish = clock();
                comparetime.SearchTimeHash = (double)((finish - start) / CLOCKS_PER_SEC);
                if (a < 0)
                {
                    printf("无此单词！\n");
                    getchar(); getchar();
                    break;
                }
                getchar(); getchar();
                break;
            case 11:
                printf("输入待删除的单词：");
                scanf("%s", searchword);
                a = DeleteHash(searchword);
                if (a)
                    printf("删除单词成功！\n");
                else
                    printf("删除单词失败！\n");
                getchar(); getchar();
                break;
            case 12:
                start = clock();
                TraverseHash();
                finish = clock();
                comparetime.TraverseTimeHash = (double)((finish - start) / CLOCKS_PER_SEC);
                getchar(); getchar();
                break;
            case 13:
                start = clock();
                a = DestroyHash();
                if (a)
                {
                    printf("删除哈希表成功！\n");
                    finish = clock();
                    comparetime.DestroyTimeHash = (double)((finish - start) / CLOCKS_PER_SEC);
                }
                getchar(); getchar();
                break;
            case 14:
                AnalyzeHash();
                getchar(); getchar();
                break;
            case 15:
                printf("1.导入静态表至文件\n2.导入哈希表至文件\n3.导入排序表至文件\n");
                scanf("%d", &choice);
                if (choice < 1 || choice>3)
                {
                    printf("请选择1~3选项！\n");
                    getchar(); getchar();
                    break;
                }
                if (ExportToFile(choice) == 1)
                    printf("导入至文件成功！\n");
                else
                    printf("导入至文件失败！\n");
                getchar(); getchar();
                break;
            case 16:
                printf("1.从文件导出至静态表\n2.从文件导出至哈希表\n3.从文件导出至排序表\n");
                scanf("%d", &choice);
                if (choice < 1 || choice>3)
                {
                    printf("请选择1~3选项！\n");
                    getchar(); getchar();
                    break;
                }
                if (LoadFromFile(choice) == 1)
                    printf("恢复表成功！\n");
                else
                    printf("恢复表失败！\n");
                getchar(); getchar();
                break;
            case 17:
                AnalyzeTable();
                getchar(); getchar();
                break;
            default: break;
        }
        a = 1;
    }
}
