#include "logginghome.h"
#include "ui_logginghome.h"
#include "popupalert.h"
#include <QUrl>
#include <QDebug>
//Using QT 5.12 which doesnt have the latest Network Classes.
#include <QNetworkReply> // handles replies
#include <QNetworkAccessManager> //creates management


#include <QString>


LoggingHome::LoggingHome(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoggingHome)
{
    ui->setupUi(this);
    setWindowTitle(tr("LoggerStation"));
    //this->setWindowState(Qt::WindowMinimized); // this will hide window on start
    networkmanager = new QNetworkAccessManager(this); //Creates Access manager
    connect(networkmanager,&QNetworkAccessManager::finished,this,&LoggingHome::url_download_finished);

}

LoggingHome::~LoggingHome()
{
    delete ui;
}


void LoggingHome::url_changed(){

    url_obj=url_String; //creates URL object of string from urlLineEdit
    valid =  url_obj.isValid(); // bool validation if url is URI confrom/non empty

    if (valid == true){
        LoggingHome::url_request_sender();

    }
    else {
        qDebug()<<"non valid URL";
        //throw error better|debug code
    }
}

void LoggingHome::on_setURLButton_clicked()
{
    url_String  = ui->urlLineEdit->text(); // sets the URL to watch for as url string
    LoggingHome::url_changed(); // calls the new URL changed function.

}

void LoggingHome::url_download_finished(QNetworkReply *reply)
{

    url_reply_string = reply->readAll();

    if (request_counter<2){
        url_past_reply_string = url_reply_string;
        LoggingHome::url_request_sender();
        qDebug()<< "Request too low";
        //saves the first request into string and loops to send new GET.
        //Allows to use past html to cache to allow detection of current changes.
    }
    else{
            if(single_change==false){

                        reply_float = url_reply_string.toFloat();//converts string to float
                        past_reply_float= url_past_reply_string.toFloat();//converts past string to float
                        delta = (reply_float-past_reply_float); //difference between current reading and last

                        if (    ((delta/past_reply_float)*100)>(sensitivitythreshold)||((delta/past_reply_float)*100)< -(sensitivitythreshold)){ //if change between reading is bigger than 0.4
                            qDebug()<<"greater than"<<sensitivitythreshold <<"% change";
                            qDebug()<<delta;
                            url_past_reply_string = url_reply_string; //reset past to current

                                LoggingHome::url_updated();//Fires the first popup


                        }
                        else {
                            qDebug()<<((delta/past_reply_float)*100);
                            qDebug()<<"less than"<< sensitivitythreshold<<"% change";
                            url_past_reply_string = url_reply_string;
                            LoggingHome::url_request_sender();
                        }
            }
            if(single_change==true){ // if single change box ticked


                        resp = QString::compare(url_reply_string,url_past_reply_string); //gets difference codes as int
                        switch(resp){ // depending on whether same or different then redirected to different functions.
                        case 0: qDebug()<< "Same"<<resp<<request_counter;
                            LoggingHome::url_request_sender(); // sends to continue request loop
                            break;

                        case 1: qDebug()<< "different"<<resp<<request_counter;
                            LoggingHome::url_updated(); //flags alert
                            break;
                        case -1:qDebug()<< "different"<<resp<<request_counter;
                            LoggingHome::url_request_sender();
                            break;
                        }//end of switch
        }//end of bool if
//            else{

//                qDebug()<<"Error";
//            }


    }//end of else


}

void LoggingHome::url_updated(){

    popup_obj = new popupalert();
    popup_obj->setWindowState(Qt::WindowMaximized);
    popup_obj->show(); //creates secondary popup window and displays
     if(allow_multiple==true){
            LoggingHome::url_request_sender(); //this will continue the loop even though popup occured.
     }

}

void LoggingHome::url_request_sender()
{
    networkmanager->get(QNetworkRequest(url_obj));//GET requests with new URL.
    request_counter++; //steps request counter up per request sent.
}

void LoggingHome::on_checkBox_multiple_clicked(bool checked)
{
    allow_multiple = checked; //setting flag from checkbox
}

void LoggingHome::on_checkBox_singlechange_clicked(bool checked)
{
    single_change=checked;//setting flag from checkbox
}

/* To Do
 * Possible :Add Q-Timer with interval timer ( must be short for polling rate- if any)
 * Possible: Assign the Cache changes button to save differences to file via QFile.
 * Urgent:Save reply into Memory. (done)
 * Urgent:Compare reply to past memory. (done)
 * Urgent:Launch Popup-Alert if reply is different. (Done)
 * Urgent: Add counter so Loop doesn't exit after first iteration (Done)
 *
 * Urgent: Tick box or 5% of variance allowed. Alters the end loop if looking for absolute difference (done)
 *
 * Good static test site : http://www.brainjar.com/java/host/test.html
 * Good Dynamic test Site: https://time.is
 */



void LoggingHome::on_verticalSlider_sliderMoved(int position)
{   sensitivitythreshold = position ;  //gives the position of the slider as float
    sensitivitythreshold=sensitivitythreshold/10; // uses float to tune to delta % change threshold
}
