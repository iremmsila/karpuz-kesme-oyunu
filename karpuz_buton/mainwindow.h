
//İREM SILA SARIKAYA  21100011030

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QList>
#include <QTimer>
#include <QVector>
#include <QObject>
#include <QMouseEvent>
#include "karpuz.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void createButton();
    void dosya_oku();
    void dosya_oku2();
    void yerDegistir();
    void hideButton();
    void sayac();

private:
    Ui::MainWindow *ui;
    QList<QString> liste;
    QList<QString> liste2;
    karpuz *button;
    int süre=31;
    int kesilen =0;
    int kacan;
    int i=0;


    QTimer *timer;
    QTimer* timer1;
    QTimer *timer3;
    QList <karpuz*> karpuzlar;
    QList <karpuz*> kesik_karpuzlar;
};
#endif // MAINWINDOW_H
