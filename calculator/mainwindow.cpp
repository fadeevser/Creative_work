#include "mainwindow.h"
#include "ui_mainwindow.h"

extern int year;
extern double percent;

double percent = 0;
double sum = 0;
double vklad;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    QString perc= arg1;
    percent=perc.toDouble();
    if ((percent <=0)||(percent>100))
        ui->lineEdit_3->setText("Ошибка ввода!");
    else ui->lineEdit_3->setText("0");
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QString summa= arg1;
    sum = summa.toDouble();
    if ((sum <= 0))
    ui->lineEdit_3->setText("Ошибка ввода!");
    else if ((sum < 1000) && (ui->comboBox->currentIndex()==3))
        ui->lineEdit_3->setText("Ошибка ввода!");
    else ui->lineEdit_3->setText("0");
}

bool check=false;
void MainWindow::on_pushButton_clicked(bool)
{
    check=(!check);
    if (check)
    {
    sum /=76;
    vklad /=76;
    ui->lineEdit->setText(QVariant(round(sum*100)/100).toString());
    ui->label_4->setText("$");
    ui->lineEdit_3->setText(QVariant(round(vklad*100)/100).toString());
    }
    else
    {
    sum *=76;
    vklad *=76;
    ui->lineEdit->setText(QVariant(round(sum*100)/100).toString());
    ui->label_4->setText("₽");
    ui->lineEdit_3->setText(QVariant(round(vklad*100)/100).toString());
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    switch (ui->comboBox->currentIndex())
    {
    case 1: {
        vklad=sum*(1+percent/100); break;
    }
    case 2: {
        vklad=sum*(pow((1+percent/100), 12)); break;
    }
    case 3: {
        if (sum < 1000) ui->lineEdit_3->setText("Ошибка ввода!");
        else
        {
        vklad=sum;
        for(int i=0; i<365; i++)
        {
        vklad+=int(vklad/1000)*1000*(percent/100);
        }
        }
        break;
    }
    case 4: {
        vklad=sum*(pow((1+percent/100),365)); break;
    }
    }
    ui->lineEdit_3->setText(QVariant(round(vklad*100)/100).toString());
}

void MainWindow::on_pushButton_3_clicked()
{
    sum=0;
    ui->lineEdit->setText(QString::number(sum));
    percent=0;
    ui->lineEdit_2->setText(QString::number(percent));
    vklad=0;
    ui->lineEdit_3->setText(QString::number(vklad));
    ui->comboBox->setCurrentIndex(0);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if ((sum < 1000) && (index==3))
            ui->lineEdit_3->setText("Ошибка ввода!");
        else ui->lineEdit_3->setText("0");
}
