#include "mainwindow.h"
#include "sipclient.h"
#include <QApplication>


int main(int argc, char *argv[])
{



    /*
    if (argc != 4) {
        printf("Invalid arguments. Please enter SIP Domain IP address followed by username followed by password."                 "Example: 169.254.1.4 username password \n");
        return 0;
    }

    strcpy(SIP_SERVER, argv[1]);            //argv[1] corresponds to SIP DOMAIN
    strcpy(USER_NAME, argv[2]);             //argv[2] corresponds to user account name
    strcpy(USER_PASSWORD, argv[3]);         //argv[3] corresponds to the user password for the account
    */
    /*
    pj_status_t action_status;


    sip->initialize_pjsua(); //Initialize PJSUA
    action_status = pjsua_create();        //Creating PJSUA
    if (action_status != PJ_SUCCESS)
        sip->error_exit("Error in the function pjsua_create()", action_status);



    sip->add_transport();                       //Adding transport for SIP

    action_status = pjsua_start();         //Starting PJSUA
    if (action_status != PJ_SUCCESS)
        sip->error_exit("Error in the function pjsua_start()", action_status);

    sip->add_account();                         //Adding user account
    */
    //sip->call_processing();                     //All the main processing for client

    //pjsua_destroy();                       //Destroy PJSUA for shutdown

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
