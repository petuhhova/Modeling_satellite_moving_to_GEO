#include "pmy.h"
#include "ui_pmy.h"
#include "math.h"

pmy::pmy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pmy)
{
    ui->setupUi(this);
    U=new vector(6371000,0.0,0.0,0.00124,20170+mpol);
    thr1= new QThread;
    //m1 =new QMutex;
    //l=1.0;
    f = new func(forse,dt);
    //th = new QThread();
    timer= new QTimer();
    is_stopped=true;
    //this->moveToThread(th);
    mpol=2000;
    s=QString::number(mpol)+"kg";
    ui->label->setText(s);
    ui->mslider->setRange(400,3000);
    ui->mslider->setValue(2000);
    QObject::connect(ui->mslider, SIGNAL(valueChanged(int)), this, SLOT(setMass()));
    QObject::connect(ui->quickButton, SIGNAL(clicked()), this, SLOT(quick()));
        QObject::connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startcalc()));
        QObject::connect(this, SIGNAL(started()),this,SLOT(docalc()));
        //QObject::connect(this, SIGNAL(stepdone()),this,SLOT(isPaused()));
        QObject::connect(timer, SIGNAL(timeout()),this,SLOT(isPaused()));
        QObject::connect(this, SIGNAL(dostep()),this,SLOT(docalc()));
        QObject::connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stopcalc()));
        QObject::connect(ui->pauseButton, SIGNAL(clicked()), this, SLOT(pause()),Qt::DirectConnection);
        //QObject::connect(ui->calcButton, SIGNAL(clicked()), this, SLOT(calc()));
        //QObject::connect(thr1, SIGNAL(started()), f, SLOT(runge()),Qt::DirectConnection);
        //QObject::connect(f, SIGNAL(finished()), thr1, SLOT(quit()),Qt::DirectConnection);
        //QObject::connect(thr2, SIGNAL(started()), ui->pwidget1, SLOT(repaint()),Qt::DirectConnection);
        //QObject::connect(ui->pwidget1, SIGNAL(repainted()), thr2, SLOT(quit()),Qt::DirectConnection);
        QObject::connect(f, SIGNAL(startactive()), this, SLOT(setForse()));
         QObject::connect(ui->saveButton, SIGNAL(clicked()), ui->pwidget1, SLOT(save()));
         QObject::connect(ui->Button5, SIGNAL(clicked()), this, SLOT(setdt5()));
         QObject::connect(ui->Button10, SIGNAL(clicked()), this, SLOT(setdt10()));
         QObject::connect(ui->Button30, SIGNAL(clicked()), this, SLOT(setdt30()));


}
void pmy::setdt5()
{
    dt=5;
}
void pmy::setdt10()
{
    dt=10;
}
void pmy::setdt30()
{
    dt=30;
}
void pmy::quick()
{
    ui->textEdit->clear();
    ui->textlog->clear();
    t=0.0;
    *(f->t)=t;
    *(f->U)=*U;
    ui->pwidget1->polyPoints1.clear();
    ui->pwidget1->polyPoints2.clear();
    std::fstream fout;
    fout.open("D:/table.txt", std::ios_base::out | std::ios_base::trunc);//открытие файла для записи, предварительно его очистив
         while((U->ro<46000)||(t<1000000))
        {

             if (tactive>=(tstep*stepcounter)&&(f->U->m>mpol+mstep))
             {
                 stepcounter++;
                 f->U->m-=mstep;
                 f->forse=0.0;

             }
             if(f->U->m<=mpol)//топливо закончилось
                { f->forse=0.0;}
             if(f->U->ro>=42164137)//вышли за ГСО
                { f->forse=0.0;}
             //Далее либо скорость больше или равна первой космической
             if(((U->speed>=pow(f->gamma*f->mass/f->U->ro,0.5))&&(f->U->ro>=30164137))||(U->speed>=0.8*pow(2*f->gamma*f->mass/f->U->ro,0.5))||((U->speed>=0.75*pow(2*f->gamma*f->mass/f->U->ro,0.5))&&((f->U->ro>=20164137))))
                { f->forse=0.0;}
             f->runge();
                *U=*(f->U);
                t+=dt;
             if (f->forse!=0.0)
             {
                 tactive+=dt;
                 ui->pwidget1->polyPoints2+=QPointF(U->ro*cos(U->fi),U->ro*sin(U->fi));
             }
             ui->textlog->append(QString::number(t) + '\t' + QString::number(U->ro) + "\t" + QString::number(U->fi) +"\t"+QString::number(U->m) + "\t" + "\n");
             ui->pwidget1->polyPoints1+=QPointF(U->ro*cos(U->fi),U->ro*sin(U->fi));
            fout<<t<<"\t"<<U->ro<<"\t"<<U->speed<<"\t"<<std::endl;
             if (ui->pwidget1->miny>U->ro*sin(U->fi))
                   ui->pwidget1->miny=U->ro*sin(U->fi);
            if (ui->pwidget1->maxy<U->ro*sin(U->fi))
                   ui->pwidget1->maxy=U->ro*sin(U->fi);
            if (ui->pwidget1->minx>U->ro*cos(U->fi))
                   ui->pwidget1->minx=U->ro*cos(U->fi);
             if (ui->pwidget1->maxx<U->ro*cos(U->fi))
                   ui->pwidget1->maxx=U->ro*cos(U->fi);
        }
         ui->pwidget1->repaint();
         t=0;
         f->forse=20000;
         tactive=0.0;
         stepcounter=1;

         *U=vector(6371000,0.0,0.0,0.00124,20170+mpol);
         ui->pwidget1->minx=-42000000;
         ui->pwidget1->maxx=42000000;
         ui->pwidget1->miny=-42000000;
         ui->pwidget1->maxy=42000000;
         if (U->m<=mpol)
             ui->textEdit->append("Топливо кончилось!:\n");
         ui->textEdit->append("Время:\t"+QString::number(t)+" c\nРастояние:\t"+ QString::number(U->ro/1000.0)+"км\nСкорость:\t"+QString::number(U->speed)+ "м/с\nМасса спутника: "+QString::number(U->m)+" кг\nКоличество ступеней: "+QString::number(stepcounter));

   }
void pmy::setForse()
{
    if(f->U->m>mpol+mepsilon)
     if(f->U->ro<=42164137)
      if((U->speed<pow(f->gamma*f->mass/f->U->ro,0.5))||((f->U->ro<20164137)&&(U->speed<0.8*pow(2*f->gamma*f->mass/f->U->ro,0.5)))||((U->speed<0.75*pow(2*f->gamma*f->mass/f->U->ro,0.5))&&(f->U->ro<30164137)))//скорость меньше 1ой космической
    {f->forse=20000.0-2000*(stepcounter-1);
    //ui->textlog->append("Forse activated"+'\t'+ QString::number(f->forse) + '\n');
      }

}
void pmy::setMass()
{

        QString text;
        //bool* ok= new bool;
        mpol=ui->mslider->value();
        //forse=text.toFloat(ok);
        s=QString::number(mpol)+"kg";
        ui->label->setText(s);


}

    void pmy::startcalc()

{
        if (is_stopped==true)
        {
            ui->textEdit->clear();
            ui->textlog->clear();
            is_stopped=false;
        t=0.0;
        *(f->t)=t;
        *(f->U)=*U;
        ui->pwidget1->polyPoints1.clear();
        ui->pwidget1->polyPoints2.clear();
        ui->textlog->append("TIME:\t RADIUS:\t SPEED:\t ");
        ui->textlog->append(QString::number(t) + '\t' + QString::number(U->ro) + "\t" + QString::number(U->speed) +"\n");
        ui->pwidget1->polyPoints1+=QPointF(U->ro*cos(U->fi),U->ro*sin(U->fi));

        is_paused=false;
        ui->pwidget1->repaint();
        emit started();
    }
    }

    void pmy::docalc()
{

        if (tactive>=(tstep*stepcounter)&&(f->U->m>mpol+mstep))
        {

              f->U->m-=mstep;
            f->forse=0.0;
            stepcounter++;

        }
        if(f->U->m<=mpol+mepsilon)//топливо закончилось
             f->forse=0.0;
        if(f->U->ro>=42164137)//вышли за ГСО
            f->forse=0.0;
        //Далее либо скорость больше или равна первой космической
        if(((U->speed>=pow(f->gamma*f->mass/f->U->ro,0.5))&&(f->U->ro>=30164137))||(U->speed>=0.8*pow(2*f->gamma*f->mass/f->U->ro,0.5))||((U->speed>=0.75*pow(2*f->gamma*f->mass/f->U->ro,0.5))&&((f->U->ro>=20164137))))
            f->forse=0.0;

        //thr1->start();
        f->runge();
        *U=*(f->U);
        t+=dt;
        if (f->forse!=0.0)
        {
            tactive+=dt;
            ui->pwidget1->polyPoints2+=QPointF(U->ro*cos(U->fi),U->ro*sin(U->fi));
        }

        ui->textlog->append(QString::number(t) + '\t' + QString::number(U->ro) + "\t" + QString::number(U->speed) +"\t"+QString::number(U->m) + "\t" + "\n");
        ui->pwidget1->polyPoints1+=QPointF(U->ro*cos(U->fi),U->ro*sin(U->fi));
        if (ui->pwidget1->miny>U->ro*sin(U->fi))
                ui->pwidget1->miny=U->ro*sin(U->fi);
        if (ui->pwidget1->maxy<U->ro*sin(U->fi))
                ui->pwidget1->maxy=U->ro*sin(U->fi);
        if (ui->pwidget1->minx>U->ro*cos(U->fi))
                ui->pwidget1->minx=U->ro*cos(U->fi);
        if (ui->pwidget1->maxx<U->ro*cos(U->fi))
                ui->pwidget1->maxx=U->ro*cos(U->fi);
        ui->pwidget1->repaint();
        timer->start(1);
}

    void pmy::isPaused()

    {
        if (is_stopped==false)
        {
        timer->stop();
        if (is_paused==false)
        {
            emit dostep();

        }
        }

    }
    void pmy::pause()
    {
        if (is_stopped==false)
        {
        if (is_paused==true)
          {
            ui->textEdit->clear();
            is_paused=false;
        emit dostep();
        }
        else
        {

            is_paused=true;
            if (U->m<=mpol+mepsilon)
                ui->textEdit->append("Топливо кончилось!\n");
            ui->textEdit->append("Время:\t"+QString::number(t)+"c\nРастояние:\t"+ QString::number(U->ro/1000.0)+"км\nСкорость:\t"+QString::number(U->speed)+ "м/с\nМасса:\t"+QString::number(U->m)+"кг");
        }
    }
 }

    void pmy::stopcalc()
    {
        ui->textEdit->clear();
        if (U->m<=mpol+mepsilon)
            ui->textEdit->append("Топливо кончилось!:\n");
        ui->textEdit->append("Время:\t"+QString::number(t)+" c\nРастояние:\t"+ QString::number(U->ro/1000.0)+"км\nСкорость:\t"+QString::number(U->speed)+ "м/с\nМасса спутника: "+QString::number(U->m)+" кг\nКоличество ступеней: "+QString::number(stepcounter));
        is_paused=true;
        is_stopped=true;
        t=0;
        f->forse=20000;
        tactive=0.0;
        stepcounter=1;

        *U=vector(6371000,0.0,0.0,0.00124,20170+mpol);
        ui->pwidget1->minx=-43000000;
        ui->pwidget1->maxx=43000000;
        ui->pwidget1->miny=-43000000;
        ui->pwidget1->maxy=43000000;


    }
    void pmy::save()
    {
        draw=QPixmap(size());//объект для сохраненияскриншота
        render(&draw);//текщий виджет впиксмап
        image=draw.toImage();// в имейдж
        image.save("D:/picture.jpg");
    }
pmy::~pmy()
{
    delete ui;
}
