#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Worder.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QMessageBox>

extern SearchList *list;
extern SearchList *sortlist;
extern HashTable *hash;
extern TimeCompare comparetime;

clock_t start, end;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->ImportWordSource,SIGNAL(triggered()),this,SLOT(ShowFileChoice()));
    connect(ui->ImportStatic,SIGNAL(triggered()),this,SLOT(ImportStaticlist()));
    connect(ui->ImportHash,SIGNAL(triggered()),this,SLOT(ImportHashlist()));
//    connect(ui->ImportSort,SIGNAL(triggered()),this,SLOT(ImportSortlist()));

    connect(ui->ExportStatic,SIGNAL(triggered()),this,SLOT(SaveStatic()));
    connect(ui->ExportHash,SIGNAL(triggered()),this,SLOT(SaveHash()));
    connect(ui->ExportSort,SIGNAL(triggered()),this,SLOT(SaveSort()));
    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(Exit()));

    connect(ui->BuildStatic,SIGNAL(triggered()),this,SLOT(BuildStatic()));
    connect(ui->BuildSort,SIGNAL(triggered()),this,SLOT(BuildSort()));
    connect(ui->BuildHash,SIGNAL(triggered()),this,SLOT(BuildHash()));

    connect(ui->SearchStatic,SIGNAL(triggered()),this,SLOT(SearchStatic()));
    connect(ui->SearchSort,SIGNAL(triggered()),this,SLOT(SearchSort()));
    connect(ui->SearchHash,SIGNAL(triggered()),this,SLOT(SearchHash()));

    connect(ui->DestroyStatic,SIGNAL(triggered()),this,SLOT(DestroyStatic()));
    connect(ui->DestroySort,SIGNAL(triggered()),this,SLOT(DestroySort()));
    connect(ui->DestroyWord,SIGNAL(triggered()),this,SLOT(DestroyWord()));
    connect(ui->DestroyTable,SIGNAL(triggered()),this,SLOT(DestroyTable()));

    connect(ui->TraverseStatic,SIGNAL(triggered()),this,SLOT(TraverseStatic()));
    connect(ui->TraverseSort,SIGNAL(triggered()),this,SLOT(TraverseSort()));
    connect(ui->TraverseHash,SIGNAL(triggered()),this,SLOT(TraverseHash()));

    connect(ui->AnalyzeHash,SIGNAL(triggered()),this,SLOT(AnalyzeHash()));
    connect(ui->AnalyzeTable,SIGNAL(triggered()),this,SLOT(AnalyzeTable()));
    connect(ui->HelpDeveloper,SIGNAL(triggered()),this,SLOT(DeveloperInfo()));
    connect(ui->HelpAbout,SIGNAL(triggered()),this,SLOT(About()));
}

MainWindow::~MainWindow()//free memory
{
    delete ui;
}

void MainWindow::ShowFileChoice()
{
    ui->ImportFileName->clear();
    QString filename=QFileDialog::getOpenFileName(this,tr("导入文件"),"/");
    ui->ImportFileName->setText(filename);
}

void MainWindow::ImportStaticlist()
{
    ui->ImportFileName->clear();
    QString filename=QFileDialog::getOpenFileName(this,tr("导入文件"),"/");
    ui->ImportFileName->setText(filename);
    if(list)
    {
        QMessageBox::information(this,"错误","静态表已存在！");
        return;
    }
    else if(filename.isEmpty())
    {
        QMessageBox::information(this,"错误","输入路径为空！");
        return;
    }
    QByteArray ba = filename.toLatin1();
    char *file = ba.data();
    if(LoadFromFile(1,file) == 1)
        QMessageBox::information(this,"成功","导入静态表成功！");
    else
        QMessageBox::information(this,"错误","导入静态表失败！");

}

void MainWindow::ImportHashlist()
{
    ui->ImportFileName->clear();
    QString filename=QFileDialog::getOpenFileName(this,tr("导入文件"),"/");
    ui->ImportFileName->setText(filename);
    if(hash)
    {
        QMessageBox::information(this,"错误","哈希表已存在！");
        return;
    }
    else if(filename.isEmpty())
    {
        QMessageBox::information(this,"错误","输入路径为空！");
        return;
    }
    QByteArray ba = filename.toLatin1();
    char *file = ba.data();
    if(LoadFromFile(2,file) == 1)
        QMessageBox::information(this,"成功","导入哈希表成功！");
    else
        QMessageBox::information(this,"错误","导入哈希表失败！");
}
//void MainWindow::ImportSortlist()
//{
//    ui->ImportFileName->clear();
//    QString filename=QFileDialog::getOpenFileName(this,tr("导入文件"),"/");
//    ui->ImportFileName->setText(filename);
//    if(sortlist)
//    {
//        QMessageBox::information(this,"错误","排序表已存在！");
//        return;
//    }
//    else if(filename.isEmpty())
//    {
//        QMessageBox::information(this,"错误","输入路径为空！");
//        return;
//    }
//    QByteArray ba = filename.toLatin1();
//    char *file = ba.data();
//    if(LoadFromFile(3,file) == 1)
//        QMessageBox::information(this,"成功","导入排序表成功！");
//    else
//        QMessageBox::information(this,"错误","导入排序表失败！");
//}
void MainWindow::SaveStatic()
{
    ui->ExportFileName->clear();
    QString filename = QFileDialog::getSaveFileName(this, tr("保存文件"),"/",tr("Config Files (*.txt)"));
    ui->ExportFileName->setText(filename);
    if(filename.isEmpty())
    {
        QMessageBox::information(this,"错误","输入路径为空！");
        return;
    }
    QByteArray ba = filename.toLatin1();
    char *file = ba.data();
    if(!list)
    {
        QMessageBox::information(this,"错误","无静态表！");
        return;
    }
    if(ExportToFile(1,file))
        QMessageBox::information(this,"成功","导入至文件成功！");
    else
        QMessageBox::information(this,"错误","导入至文件失败！");

}

void MainWindow::SaveHash()
{
    ui->ExportFileName->clear();
    QString filename = QFileDialog::getSaveFileName(this, tr("保存文件"),"/",tr("Config Files (*.txt)"));
    ui->ExportFileName->setText(filename);
    if(filename.isEmpty())
    {
        QMessageBox::information(this,"错误","输入路径为空！");
        return;
    }
    QByteArray ba = filename.toLatin1();
    char *file = ba.data();
    if(!hash)
    {
        QMessageBox::information(this,"错误","无哈希表！");
        return;
    }
    if(ExportToFile(2,file))
        QMessageBox::information(this,"成功","导入至文件成功！");
    else
        QMessageBox::information(this,"错误","导入至文件失败！");
}
void MainWindow::SaveSort()
{
    ui->ExportFileName->clear();
    QString filename = QFileDialog::getSaveFileName(this, tr("保存文件"),"/",tr("Config Files (*.txt)"));
    ui->ExportFileName->setText(filename);
    if(filename.isEmpty())
    {
        QMessageBox::information(this,"错误","输入路径为空！");
        return;
    }
    QByteArray ba = filename.toLatin1();
    char *file = ba.data();
    if(!sortlist)
    {
        QMessageBox::information(this,"错误","无排序表！");
        return;
    }
    if(ExportToFile(3,file))
        QMessageBox::information(this,"成功","导入至文件成功！");
    else
        QMessageBox::information(this,"错误","导入至文件失败！");

}
void MainWindow::Exit()
{
    QApplication *app = nullptr;
    app->quit();
}

void MainWindow::BuildStatic()
{
    if(ui->ImportFileName->text().isEmpty())
    {
        QMessageBox::information(this,"错误","输入路径为空！");
        return;
    }
    QByteArray ba = ui->ImportFileName->text().toLatin1();
    char* filename = ba.data();
    if(list)
    {
        QMessageBox::information(this,"错误","静态表已存在！");
        return;
    }
    start = clock();
    if(DealData(1, filename))
        QMessageBox::information(this,"成功","静态表建立成功！");
    else
        QMessageBox::information(this,"错误","静态表建立失败！");
    end = clock();
    comparetime.CreateTimeList = (double)(end - start);
}

void MainWindow::BuildSort()
{
    if(ui->ImportFileName->text().isEmpty())
    {
        QMessageBox::information(this,"错误","输入路径为空！");
        return;
    }
    else if(sortlist)
    {
        QMessageBox::information(this,"错误","有序表已存在！");
        return;
    }
    else if(!list)
    {
        QMessageBox::information(this,"错误","未建立静态表！");
        return;
    }
    else
    {
        if(BuildSortlist())
            QMessageBox::information(this,"成功","建立有序表成功！");
        else
            QMessageBox::information(this,"错误","建立有序表失败！");
    }
}
void MainWindow::BuildHash()
{
    if(ui->ImportFileName->text().isEmpty())
    {
        QMessageBox::information(this,"错误","输入路径为空！");
    }
    QByteArray ba = ui->ImportFileName->text().toLatin1();
    char* filename = ba.data();
    if(hash)
    {
        QMessageBox::information(this,"错误","哈希表已存在！");
        return;
    }
    start = clock();
    if(DealData(2, filename))
        QMessageBox::information(this,"成功","哈希表建立成功！");
    else
        QMessageBox::information(this,"错误","哈希表建立失败！");
    end = clock();
    comparetime.CreateTimeHash = (double)(end - start);
}

void MainWindow::SearchStatic()
{
    ui->ShowPanel->clear();
    if(ui->ImportFileName->text().isEmpty())
    {
        QMessageBox::information(this,"错误","输入路径为空！");
        return;
    }
    if(!list)
    {
        QMessageBox::information(this,"错误","无静态表！");
        return;
    }
    if(ui->SearchWord->text().isEmpty())
    {
        QMessageBox::information(this,"错误","无单词！");
        return;
    }
    QByteArray ba = ui->SearchWord->text().toLatin1();
    char *searchword = ba.data();

    start = clock();
    int i = Search(searchword);
    end = clock();
    comparetime.SearchTimeList = (double)(end - start);
    if(i == -1)
    {
        QMessageBox::information(this,"错误","无此单词！");
    }
    else
    {
        WordAndCount *con = &(list->elem[i]);
        WordAttr *tmp;
        QString string = "单词："+QString(QLatin1String(con->word))+":\n";

        for (tmp = con->attribute->next; tmp != NULL; tmp = tmp->next)
        {
            string += "页码:"+QString::number(tmp->pagenum,10)+"\t"+"行数:"+QString::number(tmp->linenum,10)+"\n";
        }
        string += "出现次数:"+QString::number(con->count,10)+"\n";
        ui->ShowPanel->setText(string);
    }
}
void MainWindow::SearchSort()
{
    ui->ShowPanel->clear();
    if(ui->ImportFileName->text().isEmpty())
    {
        QMessageBox::information(this,"错误","输入路径为空！");
        return;
    }
    if(!sortlist)
    {
        QMessageBox::information(this,"错误","无有序表！");
        return;
    }
    if(ui->SearchWord->text().isEmpty())
    {
        QMessageBox::information(this,"错误","无单词！");
        return;
    }

    QByteArray ba = ui->SearchWord->text().toLatin1();
    char *searchword = ba.data();
    int i = SearchBin(searchword);
    if(i == -1)
    {
        QMessageBox::information(this,"错误","无此单词！");
    }
    else
    {
        WordAndCount *con = &(sortlist->elem[i]);
        WordAttr *tmp;
        QString string = "单词："+QString(QLatin1String(con->word))+":\n";

        for (tmp = con->attribute->next; tmp != NULL; tmp = tmp->next)
        {
            string += "页码:"+QString::number(tmp->pagenum,10)+"\t"+"行数:"+QString::number(tmp->linenum,10)+"\n";
        }
        string += "出现次数:"+QString::number(con->count,10)+"\n";
        ui->ShowPanel->setText(string);
    }
}

void MainWindow::SearchHash()
{
    ui->ShowPanel->clear();
    if(ui->ImportFileName->text().isEmpty())
    {
        QMessageBox::information(this,"错误","输入路径为空！");
        return;
    }
    if(!hash)
    {
        QMessageBox::information(this,"错误","无哈希表！");
        return;
    }
    if(ui->SearchWord->text().isEmpty())
    {
        QMessageBox::information(this,"错误","无单词！");
        return;
    }
    QByteArray ba = ui->SearchWord->text().toLatin1();
    char *searchword = ba.data();
    start = clock();
    HashElem *p = SearchHashlist(searchword);
    end = clock();
    comparetime.SearchTimeHash = (double)(end - start);

    if(!p)
        QMessageBox::information(this,"错误","无此单词！");
    else
    {
        WordAttr *q;
        QString res = "";
        res = "单词："+QString(QLatin1String(p->word))+":\n";
        for (q = p->attribute->next; q != NULL; q = q->next)
        {
            res += "页码:"+QString::number(q->pagenum,10)+"\t行数:"+QString::number(q->linenum,10)+"\n";
        }
        res +=  "出现次数:"+QString::number(p->count,10)+"\n";
        ui->ShowPanel->setText(res);
    }
}

void MainWindow::DestroyStatic()
{
    if(ui->ImportFileName->text().isEmpty())
    {
        QMessageBox::information(this,"错误","输入路径为空！");
        return;
    }
    ui->ShowPanel->clear();
    if(!list)
    {
        QMessageBox::information(this,"错误","无静态表！");
        return;
    }
    Destroy();
    QMessageBox::information(this,"成功","静态表删除成功！");
}
void MainWindow::DestroySort()
{
    if(ui->ImportFileName->text().isEmpty())
    {
        QMessageBox::information(this,"错误","输入路径为空！");
    }
    ui->ShowPanel->clear();
    if(!sortlist)
    {
        QMessageBox::information(this,"错误","无排序表！");
        return;
    }
    DestroySortlist();
    QMessageBox::information(this,"成功","排序表删除成功！");
}
void MainWindow::DestroyWord()
{
    if(ui->ImportFileName->text().isEmpty())
    {
        QMessageBox::information(this,"错误","输入路径为空！");
    }
    ui->ShowPanel->clear();
    if(ui->SearchWord->text().isEmpty())
    {
        QMessageBox::information(this,"错误","无单词！");
        return;
    }
    QByteArray ba = ui->SearchWord->text().toLatin1();
    char *searchword = ba.data();
    if(!hash)
    {
        QMessageBox::information(this,"错误","无哈希表！");
        return;
    }
    if(DeleteHash(searchword))
        QMessageBox::information(this,"成功","删除单词成功！");
    else
        QMessageBox::information(this,"错误","无此单词！");
}
void MainWindow::DestroyTable()
{
    if(ui->ImportFileName->text().isEmpty())
    {
        QMessageBox::information(this,"错误","输入路径为空！");
    }
    ui->ShowPanel->clear();
    if(!hash)
    {
        QMessageBox::information(this,"错误","无哈希表！");
        return;
    }
    DestroyHash();
    QMessageBox::information(this,"成功","哈希表删除成功！");
}

void MainWindow::TraverseStatic()
{
    if(ui->ImportFileName->text().isEmpty())
    {
        QMessageBox::information(this,"错误","输入路径为空！");
    }
    ui->ShowPanel->clear();
    if(!list)
    {
        QMessageBox::information(this,"错误","无静态表！");
        return;
    }
    start = clock();
    QString string = Traverse();
    end = clock();
    comparetime.TraverseTimeList = (double)(end - start);

    ui->ShowPanel->setText(string);
}
void MainWindow::TraverseSort()
{
    if(ui->ImportFileName->text().isEmpty())
    {
        QMessageBox::information(this,"错误","输入路径为空！");
    }
    ui->ShowPanel->clear();
    if(!sortlist)
    {
        QMessageBox::information(this,"错误","无有序表！");
        return;
    }
    ui->ShowPanel->setText(TraverseSortlist());
}

void MainWindow::TraverseHash()
{
    if(ui->ImportFileName->text().isEmpty())
    {
        QMessageBox::information(this,"错误","输入路径为空！");
    }

    ui->ShowPanel->clear();
    if(!hash)
    {
        QMessageBox::information(this,"错误","无哈希表！");
        return;
    }
    start = clock();
    QString string = TraverseHashlist();
    end = clock();
    comparetime.TraverseTimeHash = (double)(end - start);

    ui->ShowPanel->setText(string);}

void MainWindow::AnalyzeHash()
{
    QString string = AnalyzeHashlist();
    ui->ShowPanel->clear();
    ui->ShowPanel->setText(string);
}

void MainWindow::AnalyzeTable()
{
    QString string = Analyze();
    ui->ShowPanel->clear();
    ui->ShowPanel->setText(string);
}

void MainWindow::DeveloperInfo()
{
    ui->ShowPanel->clear();
    ui->ShowPanel->setText("\n\n\n\n"
                           "\t\t\t开发者：张铭\n\n\t\t\t邮箱：   U201511086@hust.edu.cn\n\n\t\t\tGithub：minghust");
}

void MainWindow::About()
{
    ui->ShowPanel->clear();
    ui->ShowPanel->setText("\n\n\n\n\n"
                           "\t\t\t数据结构课程设计\n\n\t\t\t    单词索引器");
}
