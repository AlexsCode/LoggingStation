#include "popupalert.h"
#include "ui_popupalert.h"

popupalert::popupalert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::popupalert)
{
    ui->setupUi(this);
 }

popupalert::~popupalert()
{
    delete ui;
}
