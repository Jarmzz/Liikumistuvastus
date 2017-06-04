#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QSlider>
#include <video.h>
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updatePlayerUI(QImage img);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void passageSlot();
private:
    Ui::MainWindow *ui;
    video* myPlayer;
    QSlider* mySlider;
};
#endif // MAINWINDOW_H
