#ifndef POPUPALERT_H
#define POPUPALERT_H

#include <QDialog>

namespace Ui {
class popupalert;
}

class popupalert : public QDialog
{
    Q_OBJECT

public:
    explicit popupalert(QWidget *parent = nullptr);
    ~popupalert();

private:
    Ui::popupalert *ui;
};

#endif // POPUPALERT_H
