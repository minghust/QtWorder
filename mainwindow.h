#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;


public slots:
    void ShowFileChoice();
    void ImportStaticlist();
    void ImportHashlist();
//    void ImportSortlist();
    void SaveStatic();
    void SaveHash();
    void SaveSort();
    void Exit();

    void BuildStatic();
    void BuildSort();
    void BuildHash();

    void SearchStatic();
    void SearchSort();
    void SearchHash();

    void DestroyStatic();
    void DestroySort();
    void DestroyWord();
    void DestroyTable();

    void TraverseStatic();
    void TraverseSort();
    void TraverseHash();

    void AnalyzeHash();
    void AnalyzeTable();

    void DeveloperInfo();
    void About();

};


#endif // MAINWINDOW_H
