#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QRandomGenerator>
#include <QGraphicsTextItem>
#include <QMessageBox>

bool flagmatr=0;
bool drawed=0;
int N;
int rez1[100];
int rez2[100];
int xdot[20];
int ydot[20];
int minx=600;
int miny=600;
int maxx=0;
int maxy=0;

// final_path[] stores the final solution ie, the
// path of the salesman.
int final_path[100];

// visited[] keeps track of the already visited nodes
// in a particular path
bool visited[100];

// Stores the final minimum weight of shortest tour.
int final_res = INT_MAX;


QRandomGenerator *rg=QRandomGenerator::global();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setFixedSize(830,565);
    ui->button_ok->hide();
    ui->button_random->hide();
    ui->tableWidget->hide();
    ui->label_vtext->hide();
    ui->label_vznac->hide();
    scene=new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    setWindowTitle("Travelling Salesman Problem");
    on_horizontalSlider_sliderMoved(3);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->label->setText(QString::number(position));
    N=position;
    scene->clear();
    for(int i=1;i<=position;i++)
    {
        xdot[i]=rg->bounded(10,500);
        ydot[i]=200*i/4;
        if(xdot[i]<minx) minx=xdot[i];
        if(xdot[i]>maxx) maxx=xdot[i];
        if(ydot[i]<miny) miny=ydot[i];
        if(ydot[i]>maxy) maxy=ydot[i];
    }
    for(int i=1;i<=N;i++)
    {
        ellipse[i]=scene->addEllipse(xdot[i], ydot[i], 8, 8,QPen(), QBrush(Qt::SolidPattern));
        QGraphicsTextItem *text=scene->addText(QString::number(i));
        if(xdot[i]==minx)
            text->setPos(xdot[i]-19,ydot[i]);
        else if(xdot[i]==maxx)
            text->setPos(xdot[i]+19,ydot[i]);
        else if(ydot[i]==miny)
            text->setPos(xdot[i]-4,ydot[i]-19);
        else if(ydot[i]==maxy)
            text->setPos(xdot[i]-4,ydot[i]+19);
        else text->setPos(xdot[i]-4,ydot[i]-19);
    }
    flagmatr=0;
    ui->label_vtext->hide();
    ui->label_vznac->hide();
}

void MainWindow::on_button_matrix_clicked()
{
    if (drawed)
    {
        scene->clear();
        for(int i=1;i<=N;i++)
        {
            ellipse[i]=scene->addEllipse(xdot[i], ydot[i], 8, 8,QPen(), QBrush(Qt::SolidPattern));
            QGraphicsTextItem *text=scene->addText(QString::number(i));
            if(xdot[i]==minx)
                text->setPos(xdot[i]-19,ydot[i]);
            else if(xdot[i]==maxx)
                text->setPos(xdot[i]+19,ydot[i]);
            else if(ydot[i]==miny)
                text->setPos(xdot[i]-4,ydot[i]-19);
            else if(ydot[i]==maxy)
                text->setPos(xdot[i]-4,ydot[i]+19);
            else text->setPos(xdot[i]-4,ydot[i]-19);
        }
    }
    ui->label->hide();
    ui->label_2->hide();
    ui->button_matrix->hide();
    ui->button_calc->hide();
    ui->button_clear->hide();
    ui->horizontalSlider->hide();
    ui->graphicsView->hide();
    ui->label_vtext->hide();
    ui->label_vznac->hide();
    ui->tableWidget->show();
    ui->button_ok->show();
    ui->button_random->show();
    ui->label_3->hide();
    ui->tableWidget->setFixedSize(N*60+19,N*30+25);
    MainWindow::setFixedSize(N*60+19,N*30+100);
    ui->button_ok->move((N*60+19)/2-64,N*30+64);
    ui->button_random->move((N*60+19)/2-95,N*30+28);
    ui->tableWidget->setRowCount(N);
    ui->tableWidget->setColumnCount(N);
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        {
            //QTableWidgetItem *a=new QTableWidgetItem(" ");
            //ui->tableWidget->setItem(i,j,a);
            if(i==j){
            QTableWidgetItem *null=new QTableWidgetItem("X");
            null->setFlags(null->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->setItem(i,j,null);
            ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);}
        }
    flagmatr=1;
}

void MainWindow::on_button_random_clicked()
{
    for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
            {
                if(!(i==j)){
                QTableWidgetItem *a=new QTableWidgetItem(QString::number(rg->bounded(1,100)));
                ui->tableWidget->setItem(i,j,a);
                ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);}
            }
}

void MainWindow::on_button_ok_clicked()
{
    if(matrixcheck()){
    MainWindow::setFixedSize(830,565);
    ui->label->show();
    ui->label_2->show();
    ui->button_matrix->show();
    ui->button_calc->show();
    ui->button_clear->show();
    ui->horizontalSlider->show();
    ui->graphicsView->show();
    ui->label_3->show();
    ui->tableWidget->hide();
    ui->button_ok->hide();
    ui->button_random->hide();}
    else QMessageBox::warning(this,"Ошибка","Заполните матрицу смежности положительными значениями");
}

bool MainWindow::matrixcheck()
{
    if(flagmatr){
    for(int i=0;i<N;i++)
       for(int j=0;j<N;j++)
       {
           if(!(i==j))
           {
          QTableWidgetItem *it=ui->tableWidget->item(i,j);
           if(it->text()==" "||it->text().toInt()<0) return 0;
           }
       }
    return 1;
    } else return 0;
}

// Function to copy temporary solution to
// the final solution
void copyToFinal(int curr_path[])
{
    for (int i = 0; i < N; i++)
        final_path[i] = curr_path[i];
    final_path[N] = curr_path[0];
}

// Function to find the minimum edge cost
// having an end at the vertex i
int firstMin(int adj[100][100], int i)
{
    int min = INT_MAX;
    for (int k = 0; k < N; k++)
        if (adj[i][k] < min && i != k)
            min = adj[i][k];
    return min;
}

// function to find the second minimum edge cost
// having an end at the vertex i
int secondMin(int adj[100][100], int i)
{
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < N; j++)
    {
        if (i == j)
            continue;

        if (adj[i][j] <= first)
        {
            second = first;
            first = adj[i][j];
        }
        else if (adj[i][j] <= second &&
            adj[i][j] != first)
            second = adj[i][j];
    }
    return second;
}

// function that takes as arguments:
// curr_bound -> lower bound of the root node
// curr_weight-> stores the weight of the path so far
// level-> current level while moving in the search
//         space tree
// curr_path[] -> where the solution is being stored which
//                would later be copied to final_path[]

void TSPRec(int adj[100][100], int curr_bound, int curr_weight,int level, int curr_path[])
{
    // base case is when we have reached level N which
    // means we have covered all the nodes once
    if (level == N)
    {
        // check if there is an edge from last vertex in
        // path back to the first vertex
        if (adj[curr_path[level - 1]][curr_path[0]] != 0)
        {
            // curr_res has the total weight of the
            // solution we got
            int curr_res = curr_weight +
                adj[curr_path[level - 1]][curr_path[0]];

            // Update final result and final path if
            // current result is better.
            if (curr_res < final_res)
            {
                copyToFinal(curr_path);
                final_res = curr_res;
            }
        }
        return;
    }

    // for any other level iterate for all vertices to
    // build the search space tree recursively
    for (int i = 0; i < N; i++)
    {
        // Consider next vertex if it is not same (diagonal
        // entry in adjacency matrix and not visited
        // already)
        if (adj[curr_path[level - 1]][i] != 0 &&
            visited[i] == false)
        {
            int temp = curr_bound;
            curr_weight += adj[curr_path[level - 1]][i];

            // different computation of curr_bound for
            // level 2 from the other levels
            if (level == 1)
                curr_bound -= ((firstMin(adj, curr_path[level - 1]) +
                    firstMin(adj, i)) / 2);
            else
                curr_bound -= ((secondMin(adj, curr_path[level - 1]) +
                    firstMin(adj, i)) / 2);

            // curr_bound + curr_weight is the actual lower bound
            // for the node that we have arrived on
            // If current lower bound < final_res, we need to explore
            // the node further
            if (curr_bound + curr_weight < final_res)
            {
                curr_path[level] = i;
                visited[i] = true;

                // call TSPRec for the next level
                TSPRec(adj, curr_bound, curr_weight, level + 1,
                    curr_path);
            }

            // Else we have to prune the node by resetting
            // all changes to curr_weight and curr_bound
            curr_weight -= adj[curr_path[level - 1]][i];
            curr_bound = temp;

            // Also reset the visited array
            memset(visited, false, sizeof(visited));
            for (int j = 0; j <= level - 1; j++)
                visited[curr_path[j]] = true;
        }
    }
}

// This function sets up final_path[]
void TSP(int adj[100][100])
{
    int curr_path[N + 1];

    // Calculate initial lower bound for the root node
    // using the formula 1/2 * (sum of first min +
    // second min) for all edges.
    // Also initialize the curr_path and visited array
    int curr_bound = 0;
    memset(curr_path, -1, sizeof(curr_path));
    memset(visited, 0, sizeof(curr_path));

    // Compute initial bound
    for (int i = 0; i < N; i++)
        curr_bound += (firstMin(adj, i) +
            secondMin(adj, i));

    // Rounding off the lower bound to an integer
    curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 :
        curr_bound / 2;

    // We start at vertex 1 so the first vertex
    // in curr_path[] is 0
    visited[0] = true;
    curr_path[0] = 0;

    // Call to TSPRec for curr_weight equal to
    // 0 and level 1
    TSPRec(adj, curr_bound, 0, 1, curr_path);
}
void MainWindow::on_button_calc_clicked()
{
    if(matrixcheck()){
            int adj[100][100];
            for (int i = 0; i < N; i++)
            {
                adj[i][i] = 0;
                for (int j = 0; j < N; j++)
                {
                    if(!(i==j)){
                        QTableWidgetItem *it=ui->tableWidget->item(i,j);
                        adj[i][j]=it->text().toInt();}
                }
            }

            TSP(adj);

            for (int i = 0; i < N; i++)
            {
                rez1[i]=final_path[i] + 1;
                rez2[i]=final_path[i + 1] + 1;
            }

           ui->label_vtext->show();
           ui->label_vznac->show();
           ui->label_vznac->setText(QString::number(final_res));
           memset(visited,0,sizeof visited);
           memset(final_path,0,sizeof final_path);
           final_res=INT_MAX;
           draw();
    }
    else QMessageBox::warning(this,"Ошибка","Заполните матрицу смежности положительными значениями");
}


void MainWindow::draw()
{
    flagmatr=1;
    QPen qline;qline.setColor(Qt::black);qline.setWidth(1);
    QFont font;font.setPixelSize(12); font.setBold(1);
    for(int i=0;i<N;i++)
    {
        drawarrow
                (ellipse[rez1[i]]->rect().x()+4,
                ellipse[rez1[i]]->rect().y()+4,
                ellipse[rez2[i]]->rect().x()+4,
                ellipse[rez2[i]]->rect().y()+4);
        int textx=(ellipse[rez1[i]]->rect().x()+ellipse[rez2[i]]->rect().x())/2;
        int texty=(ellipse[rez1[i]]->rect().y()+ellipse[rez2[i]]->rect().y())/2;
        QTableWidgetItem *it=ui->tableWidget->item(rez1[i]-1,rez2[i]-1);
        QGraphicsTextItem *text=scene->addText(it->text());
        text->setFont(font);
        text->setPos(textx,texty-7);
    }
    for(int i=1;i<=N;i++)
    {
        ellipse[i]=scene->addEllipse(xdot[i], ydot[i], 8, 8,QPen(), QBrush(Qt::SolidPattern));
        QGraphicsTextItem *text=scene->addText(QString::number(i));
        if(xdot[i]==minx)
            text->setPos(xdot[i]-19,ydot[i]);
        else if(xdot[i]==maxx)
            text->setPos(xdot[i]+19,ydot[i]);
        else if(ydot[i]==miny)
            text->setPos(xdot[i]-4,ydot[i]-19);
        else if(ydot[i]==maxy)
            text->setPos(xdot[i]-4,ydot[i]+19);
        else text->setPos(xdot[i]-4,ydot[i]-19);
    }
    drawed=1;
    minx=600;
    miny=600;
    maxx=0;
    maxy=0;
}

void MainWindow::drawarrow(int x1,int y1,int x2, int y2)
{
       QPen line;
       line.setColor(QColor(255,255,255));
       line.setWidth(2);
       QPen arr;
       arr.setColor(QColor(0,0,0));
       arr.setWidth(1);
       float x, y;
       float f1x2 , f1y2;
       float lons, ugol;

       const float ostr = 0.25;        // острота стрелки

       scene->addLine(x1, y1, x2, y2,line);

       x = x2 - x1;
       y = y2 - y1;

       ugol = atan2(y, x);             // угол наклона линии

       lons = 14;

       f1x2 = x2 - lons * cos(ugol - ostr);
       f1y2 = y2 - lons * sin(ugol - ostr);

       scene->addLine(x2, y2, f1x2, f1y2,arr);

       f1x2 = x2 - lons * cos(ugol + ostr);
       f1y2 = y2 - lons * sin(ugol + ostr);

       scene->addLine(x2, y2, f1x2, f1y2,arr);
}


void MainWindow::on_button_clear_clicked()
{
    drawed=0;
    flagmatr=0;
    on_horizontalSlider_sliderMoved(N);
}
