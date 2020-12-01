#include "popupalert.h"
#include "ui_popupalert.h"
#include <QSoundEffect>
#include <QUrl>



popupalert::popupalert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::popupalert)
{
    ui->setupUi(this);
    window_alert.setSource(QUrl::fromLocalFile(":/sounds/alert.wav"));
    window_alert.play();
}

popupalert::~popupalert()
{
    delete ui;
}
