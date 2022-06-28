#ifndef SIPCLIENT_H
#define SIPCLIENT_H

#include<pjsua.h>
#include <QObject>
#include <QList>

#define SIP_PORT		5260

class SIPId {
public:
    char *id;
    char *name;
    char *passwd;
    int  flags;
    int  user_int;
    void *user_data;
    int  user_type;
};

class SIPConn {
public:
    static const int S_FREE = 0;
    static const int S_CALL = 1;
    static const int S_ACTIVE = 2;
    static const int S_HANGED = 3;
    static const int S_HOLDING = 4;
    static const int S_REJECTED = 5;

    static const int D_UNKNOWN  = 0;
    static const int D_INCOMING = 1;
    static const int D_OUTGOING = 2;

    SIPConn();
    SIPConn(const SIPConn &other);

    int   local;
    int   remote;
    pjsua_call_id   call_id;
    int   status;
    int   dir;
    int   n_data;
    bool  bcast;
    char  uses_link[128];
    char  rem_id[128];
    char  local_id[128];
    char  remote_num[128];
    char  location[128];
    char  equ_name[128];
    int   ui_state;
    int   conf_port;
    int   conn_hnd;
    pjsua_recorder_id   recorder_id;
};

class sipclient: public QObject
{
    Q_OBJECT
public:

    sipclient *sip;

    sipclient();

    static void initialize_pjsua();

    static void add_transport();

    static void user_register();

    void unreg_pjsua();

    static void make_call(char input_uri[40]);

    void hang_up();

    void answer();

    void cancel();

    void add_buddy();

    static void add_account();

    static void error_exit(const char *error_msg, pj_status_t action_status);

    static void showStatus(const char *msg);

    static void showError(const char *title, pj_status_t status);

    static void playRingTone();

    static void stopRingTone();

private:

    static void cb_on_incoming_call(pjsua_acc_id account_id, pjsua_call_id call_id, pjsip_rx_data *rdata);

    static void cb_on_call_state(pjsua_call_id call_id, pjsip_event *e);

    static void cb_on_reg_state2(pjsua_acc_id account_id, pjsua_reg_info *info);

    static void cb_on_buddy_state(pjsua_buddy_id buddy_id);

    static void cb_on_media_state(pjsua_call_id call_id);

    uint32_t            frame_ptime;

};

#endif // SIPCLIENT_H
