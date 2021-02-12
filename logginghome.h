#ifndef LOGGINGHOME_H
#define LOGGINGHOME_H

#include "popupalert.h"
#include <QMainWindow>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui { class LoggingHome; }
QT_END_NAMESPACE

class LoggingHome : public QMainWindow
{
    Q_OBJECT

public:
    LoggingHome(QWidget *parent = nullptr);
    ~LoggingHome();


private slots:

    void url_changed();
    void url_updated();
    void url_request_sender();
    void on_setURLButton_clicked();
    void url_download_finished(QNetworkReply *);

    void on_checkBox_multiple_clicked(bool checked);
    void on_checkBox_singlechange_clicked(bool checked);

    void on_verticalSlider_sliderMoved(int position);

    void on_reuseURLButton_clicked();

private: //object creation
    Ui::LoggingHome *ui;
    QNetworkAccessManager *networkmanager;
    popupalert *popup_obj;
    QUrl url_obj;

    QString url_String;
    QString url_reply_string;
    QString url_past_reply_string;



    //flags
    bool valid=false;
    bool allow_multiple=false;
    bool single_change=false;

    //counters
    int request_counter=0;
    int resp;

    //read in values
    float reply_float;
    float past_reply_float;
    int delta;
    float sensitivitythreshold=0.4; //

};
#endif // LOGGINGHOME_H
