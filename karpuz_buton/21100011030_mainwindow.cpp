
//İREM SILA SARIKAYA  21100011030

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <thread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dosya_oku();
    dosya_oku2();


    QTimer* timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::createButton);
    timer->start(750);

    QTimer* timer1 = new QTimer(this);

    connect(timer1, &QTimer::timeout, this, &MainWindow::yerDegistir);
    timer1->start(500);


    QTimer* timer3 = new QTimer(this);

    connect(timer3, &QTimer::timeout, this, &MainWindow::sayac);
    timer3->start(1000);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createButton()
{

    int random_sayi=rand()%(liste.size()-0)+0;
    QList<QString> karpuz_konum=liste.at(random_sayi).split(" ");
    int x=karpuz_konum.at(0).toInt();
    int y=karpuz_konum.at(1).toInt();

    button = new karpuz(this);
    button->setGeometry(x,y,100,100);
    button->setStyleSheet("border-image:url(:/resimler/image/1.png);");

    button->setIconSize(QSize(100,100));

    karpuzlar.push_back(button);

    button->show();

    kacan=karpuzlar.size()-kesilen;
    ui->label_kacan->setText("KACAN KARPUZ SAYISI: <font color='red'>" + QString::number(kacan)+ "</font>" );


    connect(button, &QPushButton::clicked, this, &MainWindow::hideButton);

    if(süre==0)
    {

        QFile myFile2("C:/Users/Lenovo/Documents/karpuz_buton/skorlar.txt");
            if(!myFile2.open(QIODevice::Append))
        {
            QMessageBox::critical(this,"Hata!",myFile2.errorString());
            return;
        }

        QTextStream stream2(&myFile2);
        stream2 << "\n" << kesilen;
        myFile2.close();

        int en_buyuk = kesilen;


        for(int i=0;i<liste2.size();i++)
        {
            if(liste2[i].toInt()>en_buyuk)
                en_buyuk=liste2[i].toInt();
        }


        if(en_buyuk>kesilen)
        {

            QMessageBox::information(this,"Bilgi!","OYUN BİTTİ! Maksimum Skoru Geçemediniz!\n"
                                                     " Kesilen Karpuz Sayisi:"+QString::number(kesilen)+
                                                         "\nKaçırılan Karpuz Sayısı:"+QString::number(kacan)+"\nMkasimum Skor:"+QString::number(en_buyuk),"Ok");

        }
        else
        {

            QMessageBox::information(this,"Bilgi!","OYUN BİTTİ! Tebrikler Maksimum Skor Sizde!\n"
                                                     " Kesilen Karpuz Sayisi:"+QString::number(kesilen)+
                                                         "\nKaçırılan Karpuz Sayısı:"+QString::number(kacan)+"\nMkasimum Skor:"+QString::number(kesilen),"Ok");
        }

        close();

    }

}


void MainWindow::yerDegistir()
{
   for(int i=0;i<karpuzlar.size();i++)
    {
        if(süre>0)
            {
            karpuzlar[i]->setGeometry(karpuzlar[i]->x(),karpuzlar[i]->y()+50,100,100);
        }
    }
}

void MainWindow::hideButton()
{
    kesilen++;
    karpuz* clckdbutton = qobject_cast<karpuz*>(sender());
    karpuz* kesik = new karpuz(this);
    ui->label_kesilen->setText("KESİLEN KARPUZ SAYISI: <font color='#66ff00'>" + QString::number(kesilen)+ "</font>" );
    clckdbutton->hide();
    kesik->setGeometry(clckdbutton->x(),clckdbutton->y(),100,100);
    kesik->setStyleSheet("border-image:url(:/resimler/image/2.png);");
    kesik_karpuzlar.push_back(kesik);
    kesik->show();

    QTimer* timer2 = new QTimer(this);

    timer2->start(2000);
    connect(timer2, &QTimer::timeout, this, [=](){
        kesik->hide();
    });
}



void MainWindow::sayac()
{
    if(süre>0)
    {
        süre--;
    }
    ui->countdownLabel->setText("SÜRE: <font color='blue'>" + QString::number(süre)+ "</font>" );

}



void MainWindow::dosya_oku()
{
    QFile myFile("C:/Users/Lenovo/Documents/karpuz_buton/konumlar.txt");
        if(!myFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Hata!",myFile.errorString());
        return;
    }

    QTextStream stream(&myFile);
    while (!stream.atEnd()) {
        QString tut = stream.readLine();
        liste <<tut;
    }

    myFile.close();
}

void MainWindow::dosya_oku2()
{


    QFile myFile2("C:/Users/Lenovo/Documents/karpuz_buton/skorlar.txt");
        if(!myFile2.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Hata!",myFile2.errorString());
        return;
    }

    QTextStream stream2(&myFile2);
    while (!stream2.atEnd()) {
        QString tut1 = stream2.readLine();
        liste2 << tut1;
    }

    myFile2.close();

}

