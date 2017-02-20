#include "mainwindow.h"
#include "Worder.h"
#include <QApplication>

SearchList *list = NULL;
SearchList *sortlist = NULL;
HashTable *hash = NULL;
TimeCompare comparetime;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("单词索引器");
    w.show();

    return a.exec();
}
