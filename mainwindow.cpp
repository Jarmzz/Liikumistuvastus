#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSlider>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    myPlayer = new video();
    QObject::connect(myPlayer, SIGNAL(processedImage(QImage))
                              ,this, SLOT(updatePlayerUI(QImage)));
    ui->setupUi(this);
    mySlider = new QSlider();
    QObject::connect(mySlider, SIGNAL(valueChanged(int))
                     ,this, SLOT(passageSlot()));
}
void MainWindow::updatePlayerUI(QImage img)
{
    if (!img.isNull())
    {
        ui->label->setAlignment(Qt::AlignCenter);
        ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(),
                                           Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}
MainWindow::~MainWindow()
{
    delete myPlayer;
    delete mySlider;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    myPlayer->loadVideo();
}
void MainWindow::on_pushButton_2_clicked()
{
    if (myPlayer->isStopped())
    {
        myPlayer->Play();
        ui->pushButton_2->setText(tr("Stop"));
    }else
    {
        myPlayer->Stop();
        ui->pushButton_2->setText(tr("Play"));
    }
}
void MainWindow::passageSlot()
{
    qDebug() << "Vana value:" << myPlayer->minArea;
    myPlayer->minArea = mySlider->value();
    qDebug() << "Uus value:" << myPlayer->minArea;

}
