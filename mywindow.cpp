#include "mywindow.h"
#include "ui_mywindow.h"

MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    ui->setupUi(this);

    szer = ui->rysujFrame->width();
    wys = ui->rysujFrame->height();
    pocz.x = ui->rysujFrame->x();
    pocz.y = ui->rysujFrame->y();

    backgroundColor.setRgb(255, 255, 255, 255);
    foregroundColor.setRgb(0, 0, 0, 255);
    temporaryColor.setRgb(255, 0, 0, 255);

    img = new QImage(":/obrazBitowy.png");
}

MyWindow::~MyWindow()
{
    delete ui;
}

void MyWindow::on_exitButton_clicked()
{
    qApp->quit();
}

void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    p.drawImage(pocz.x, pocz.y, *img);
}

void MyWindow::on_cleanButton_clicked()
{
    czysc();
    update();
}

void MyWindow::on_powrotButton_clicked()
{
    img = new QImage(":/obrazBitowy");
    update();
}

void MyWindow::on_erozjaButton_clicked()
{
    zmienObraz('e');
    update();
}

void MyWindow::on_dylacjaButton_clicked()
{
    zmienObraz('d');
    update();
}

void MyWindow::on_otwarcieButton_clicked()
{
    zmienObraz('o');
    update();
}

void MyWindow::on_zamkniecieButton_clicked()
{
    zmienObraz('z');
    update();
}

void MyWindow::zmienObraz(char operacja)
{
    punkt pkt;

    if(operacja == 'd')
    {
        for(pkt.y = 1; pkt.y < wys - 1; pkt.y ++)
        {
            for(pkt.x = 1; pkt.x < szer - 1; pkt.x ++)
            {
                pikselDylacja(pkt);
            }
        }
        for(pkt.y = 1; pkt.y < wys - 1; pkt.y ++)
        {
            for(pkt.x = 1; pkt.x < szer - 1; pkt.x ++)
            {
                if(img->pixelColor(pkt.x, pkt.y) == temporaryColor){
                    img->setPixelColor(pkt.x, pkt.y, foregroundColor);
                }
            }
        }
    }
    else if(operacja == 'e')
    {
        for(pkt.y = 1; pkt.y < wys - 1; pkt.y ++)
        {
            for(pkt.x = 1; pkt.x < szer - 1; pkt.x ++)
            {
                pikselErozja(pkt);
            }
        }
        for(pkt.y = 1; pkt.y < wys - 1; pkt.y ++)
        {
            for(pkt.x = 1; pkt.x < szer - 1; pkt.x ++)
            {
                if(img->pixelColor(pkt.x, pkt.y) == temporaryColor){
                    img->setPixelColor(pkt.x, pkt.y, backgroundColor);
                }
            }
        }
    }
    else if(operacja == 'o')
    {
        zmienObraz('e');
        zmienObraz('d');
    }
    else if(operacja == 'z')
    {
        zmienObraz('d');
        zmienObraz('e');
    }
}

void MyWindow::pikselDylacja(punkt &piksel)
{
    if(img->pixelColor(piksel.x, piksel.y) == backgroundColor){
        if(img->pixelColor(piksel.x - 1, piksel.y) == foregroundColor ||
           img->pixelColor(piksel.x + 1, piksel.y) == foregroundColor ||
           img->pixelColor(piksel.x, piksel.y - 1) == foregroundColor ||
           img->pixelColor(piksel.x, piksel.y + 1) == foregroundColor)
           {
                img->setPixelColor(piksel.x, piksel.y, temporaryColor);
           }
    }
}

void MyWindow::pikselErozja(punkt &piksel)
{
    if(img->pixelColor(piksel.x, piksel.y) == foregroundColor){
        if(img->pixelColor(piksel.x - 1, piksel.y) == backgroundColor ||
           img->pixelColor(piksel.x + 1, piksel.y) == backgroundColor ||
           img->pixelColor(piksel.x, piksel.y - 1) == backgroundColor ||
           img->pixelColor(piksel.x, piksel.y + 1) == backgroundColor)
           {
                img->setPixelColor(piksel.x, piksel.y, temporaryColor);
           }
    }
}

void MyWindow::zamalujPiksel(punkt &piksel, QColor &color)
{
    unsigned char *ptr;
    ptr = img->bits();
    int szer = img->width();
    int skladowaRed = 4*piksel.x + szer*4*piksel.y + 2;
    int skladowaGreen = 4*piksel.x + szer*4*piksel.y + 1;
    int skladowaBlue = 4*piksel.x + szer*4*piksel.y;

    if ((piksel.x>=0)&&(piksel.y>=0)&&(piksel.x<szer)&&(piksel.y<wys))
    {
            ptr[skladowaRed]= color.red();
            ptr[skladowaGreen] = color.green();
            ptr[skladowaBlue] = color.blue();
    }
}

void MyWindow::czysc()
{
    punkt pkt;

    for(pkt.y = 0; pkt.y < wys; pkt.y ++)
    {
        for(pkt.x = 0; pkt.x < szer; pkt.x ++)
        {
            zamalujPiksel(pkt, backgroundColor);
        }
    }
}














