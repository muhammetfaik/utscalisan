#include "sipclient.h"

#define THIS_FILE    "sipclient.cpp"
#define PROGRAM_NAME    "SIPCLIENT"

char SIP_SERVER[20]="192.168.168.1";
char USER_NAME[20]="112";
char USER_PASSWORD[20]="112";

bool act_conference;


pjsua_call_id call_id_global = -1;
pjsua_player_id ringtone;
pjsua_conf_port_id ringtone_port;





/**********************************************************************************************
                   INITIALIZE PJSUA WITH SPECIFIC SETTINGS
***********************************************************************************************/
void sipclient::initialize_pjsua() {
    pj_status_t stat;
    pj_status_t status;
    pj_status_t action_status;
    pj_str_t fstr = pj_str("/home/semih/UTSound/ringtone.wav");


    //showStatus("Creating stack..");
    status = pjsua_create();
    if (status != PJ_SUCCESS) {
        showError("pjsua_create", status);
        return; // false;
    }

    showStatus("Initializing stack..");

    pjsua_config init_config;


    pjsua_config_default(&init_config);
    pjsua_callback ua_cb;
    pj_bzero(&ua_cb, sizeof(ua_cb));
    init_config.cb.on_incoming_call = &cb_on_incoming_call;
    init_config.cb.on_call_state = &cb_on_call_state;
    init_config.cb.on_reg_state2 = &cb_on_reg_state2;
    init_config.cb.on_call_media_state = &cb_on_media_state;
    init_config.cb.on_buddy_state = &cb_on_buddy_state;
    init_config.max_calls = 16;

    pjsua_logging_config log_config;
    pjsua_logging_config_default(&log_config);
    log_config.console_level = 4;

    action_status = pjsua_init(&init_config, &log_config, NULL);
    if (action_status != PJ_SUCCESS){
       error_exit("Error in the function pjsua_init()", action_status);
       goto on_error;
    }

    add_transport();

    showStatus("Starting stack..");
    action_status = pjsua_start();              //Starting PJSUA
    if (action_status != PJ_SUCCESS)
       error_exit("Error in the function pjsua_start()", action_status);

    stat = pjsua_player_create(&fstr, 0, &ringtone);
    if (stat != PJ_SUCCESS) {
        PJ_LOG(1, (THIS_FILE, "Unable to open ringtone\n"));
        ringtone = 0;
        ringtone_port = 0;
    } else {
        ringtone_port = pjsua_player_get_conf_port(ringtone);
    }



    add_account();

    action_status = pjsua_acc_set_registration(0, PJ_TRUE);
    if (action_status != PJ_SUCCESS){
        error_exit("Error in account uregistration", action_status);
        goto on_error;
    }

    return;

on_error:
    pjsua_destroy();
    return; // false;

}
//-----------------------------------------//
void sipclient::showStatus(const char *msg)
{
    PJ_LOG(3,(THIS_FILE, "%s", msg));


    //QString msg_ = QString::fromUtf8(msg);

    //emit signalShowStatus(msg_);
}
void sipclient::showError(const char *title, pj_status_t status)
{
    char errmsg[PJ_ERR_MSG_SIZE];
    char errline[120];

    pj_strerror(status, errmsg, sizeof(errmsg));
    snprintf(errline, sizeof(errline), "%s error: %s", title, errmsg);
    showStatus(errline);
}

void sipclient::unreg_pjsua(){
    pj_status_t action_status;
    action_status = pjsua_acc_set_registration(0, PJ_FALSE);
    if (action_status != PJ_SUCCESS)
        error_exit("Error in account unregistration", action_status);
}
/**********************************************************************************************
                   ADD SIP TRANSPORT WITH PORT NUMBER
***********************************************************************************************/
void sipclient::add_transport() {
    pjsua_transport_config transport_config;
    pjsua_transport_id transport_id;

    pjsua_transport_config_default(&transport_config);
    transport_config.port = 0;

    pj_status_t action_status = pjsua_transport_create(PJSIP_TRANSPORT_UDP, &transport_config, &transport_id);
    if (action_status != PJ_SUCCESS)
        error_exit("Error creating transport", action_status);

    pjsua_transport_info transpot_info;
    action_status = pjsua_transport_get_info(transport_id, &transpot_info);
    if (action_status != PJ_SUCCESS)
        error_exit("Error creating transport", action_status);
}

/**********************************************************************************************
                   ADD USER ACCOUNT FOR THE DOMAIN FRM ARGUMENTS
***********************************************************************************************/
void sipclient::add_account() {
    pjsua_acc_config account_config;
    pjsua_acc_id account_id;


    pjsua_acc_config_default(&account_config);
    char sip_uri[50];
    snprintf(sip_uri, sizeof(sip_uri), "sip:%s@%s", USER_NAME, SIP_SERVER);
    char sip[50];
    snprintf(sip, sizeof(sip), "sip:%s", SIP_SERVER);
    account_config.id = pj_str(sip_uri);
    account_config.reg_uri = pj_str(sip);
    account_config.cred_count = 1;
    account_config.cred_info[0].realm = pj_str("asterisk");
    //account_config.cred_info[0].realm = pj_str("myvoipapp.com");
    account_config.cred_info[0].scheme = pj_str("digest");
    account_config.cred_info[0].username = pj_str(USER_NAME);
    account_config.cred_info[0].data_type = PJSIP_CRED_DATA_PLAIN_PASSWD;
    account_config.cred_info[0].data = pj_str(USER_PASSWORD);
    account_config.register_on_acc_add = PJ_FALSE;

    pj_status_t action_status = pjsua_acc_add(&account_config, PJ_TRUE, &account_id);
    if (action_status != PJ_SUCCESS)
        error_exit("Error in adding account", action_status);

    action_status = pjsua_acc_set_online_status(0, PJ_TRUE);
    if (action_status != PJ_SUCCESS)
        error_exit("Error in modifying account presence", action_status);
}

/**********************************************************************************************
                   HANGUP CALL
***********************************************************************************************/
void sipclient::hang_up(){
    pjsua_call_hangup_all();
}

/**********************************************************************************************
                   ANSWER CALL
***********************************************************************************************/
void sipclient::answer(){
    pjsua_call_answer(call_id_global, 200, NULL, NULL);   //Answer incoming calls with 200 OK
    stopRingTone();
}

/**********************************************************************************************
                   CANCEL CALL
***********************************************************************************************/
void sipclient::cancel(){
    pjsua_call_answer(call_id_global, 486, NULL, NULL);      //Answer incoming calls with 486 Busy
}

/**********************************************************************************************
                   MAKE A CALL TO DESIRED DESTINATION
***********************************************************************************************/
void sipclient::make_call(char input_uri[40]){

    int conference;

    pjsua_acc_id account_id;

    printf("Enter the destination URI \n");

    /*
    scanf("%s", input_uri);
    printf("uri %s \n", input_uri);

    printf("Do you want to conference?   1/0 ; \n");
    scanf("%d", &conference);

    if (conference == 1) {
        act_conference = 1;
    } else {
        act_conference = 0;
    }
    */
    pj_status_t action_status = pjsua_verify_url(input_uri);
    if (action_status != PJ_SUCCESS)
        printf("Invalid URL entered. Try again. \n");
    else {
        pj_str_t destination_uri = pj_str(input_uri);
        //action_status = pjsua_call_make_call(account_id, &destination_uri, 0, NULL, NULL, NULL);
        action_status = pjsua_call_make_call(0, &destination_uri, 0, NULL, NULL, NULL);
        if (action_status != PJ_SUCCESS)
            error_exit("Error making call", action_status);
    }

}

/**********************************************************************************************
                   ADD BUDDY FROM ANY DESIRED DESTINATION
***********************************************************************************************/
void sipclient::add_buddy() {
    pjsua_buddy_id buddy_id;
    char input_uri[40];

    printf("Enter the destination URI to add as buddy along with port number \n");
    scanf("%s", input_uri);
    printf("buddy uri %s \n", input_uri);

    pj_status_t action_status = pjsua_verify_url(input_uri);
    if (action_status != PJ_SUCCESS)
        printf("Invalid URL entered. Try again. \n");
    else {
        pj_str_t destination_uri = pj_str(input_uri);
        pjsua_buddy_id destination_bud_id = pjsua_buddy_find(&destination_uri);
        if (destination_bud_id == PJSUA_INVALID_ID) {
            pjsua_buddy_config config;
            pjsua_buddy_config_default(&config);
            config.uri = destination_uri;;
            config.subscribe = 1;
            action_status = pjsua_buddy_add(&config, &buddy_id);
            if (action_status != PJ_SUCCESS)
                error_exit("Error on adding buddy", action_status);
        }
    }
}

/**********************************************************************************************
                   FUNCTION TO HANDLE THE ERRORS AND DESTROY PJSUA
***********************************************************************************************/
void sipclient::error_exit(const char *error_msg, pj_status_t action_status) {
    pjsua_perror(PROGRAM_NAME, error_msg, action_status);
    pjsua_destroy();
    exit(1);
}

/*********************************************************
//              RINGTONE
*********************************************************/
void sipclient::playRingTone() {
    pjsua_conf_connect(ringtone_port, 0);
}

void sipclient::stopRingTone() {
    pjsua_conf_disconnect(ringtone_port, 0);
}

/**********************************************************************************************
                   CALLBACK FUNCTION TO HANDLE INCOMING CALLS
***********************************************************************************************/
void sipclient::cb_on_incoming_call(pjsua_acc_id account_id, pjsua_call_id call_id, pjsip_rx_data *rdata) {
    pjsua_call_info call_info;

    if (pjsua_call_get_count() > 1) {
        pjsua_call_answer(call_id, 486, NULL, NULL);      //Answer incoming calls with 486 Busy
        return;
    }

    PJ_UNUSED_ARG(account_id);
    PJ_UNUSED_ARG(rdata);

    pjsua_call_get_info(call_id, &call_info);
    call_id_global = call_id;
    PJ_LOG(3, (PROGRAM_NAME, "Incoming call from %.*s",
            (int) call_info.remote_info.slen,
            call_info.remote_info.ptr));


    playRingTone();

    printf("Enter 'answer' the call..\n");



    return;
}

/**********************************************************************************************
                   CALLBACK FUNCTION TO CAPTURE CALL STATUS
***********************************************************************************************/
void sipclient::cb_on_call_state(pjsua_call_id call_id, pjsip_event *e) {
    pjsua_call_info call_info;

    PJ_UNUSED_ARG(e);

    pjsua_call_get_info(call_id, &call_info);

    PJ_LOG(3, (PROGRAM_NAME, "Call %d state=%.*s", call_id,
            (int) call_info.state_text.slen,
            call_info.state_text.ptr));
}

/**********************************************************************************************
                   CALLBACK FUNCTION TO CAPTURE REGISTRATION STATUS
***********************************************************************************************/
void sipclient::cb_on_reg_state2(pjsua_acc_id account_id, pjsua_reg_info *info) {
    PJ_UNUSED_ARG(account_id);

    if (info != NULL && info->cbparam != NULL)
        PJ_LOG(3, (PROGRAM_NAME, "Expiration=%d", info->cbparam->expiration));
}

/**********************************************************************************************
                   CALLBACK FUNCTION FUNCTION TO CAPTURE BUDDY STATUS
***********************************************************************************************/
void sipclient::cb_on_buddy_state(pjsua_buddy_id buddy_id) {
    pjsua_buddy_info bi;

    pjsua_buddy_get_info(buddy_id, &bi);

    PJ_LOG(3, (PROGRAM_NAME, "Buddy %.*s with id %d is %.*s",
            (int) bi.uri.slen, bi.uri.ptr, bi.id,
            (int) bi.status_text.slen, bi.status_text.ptr));
}

/*********************************************************
//              CONNECT SOUNDS
*********************************************************/
void sipclient::cb_on_media_state(pjsua_call_id call_id) {

    pjsua_call_info call_info;

    pjsua_call_get_info(call_id, &call_info);
    printf("Media status event: %d\n", call_id);

    for (unsigned i = 0; i < call_info.media_cnt; ++i) {
        if (call_info.media[i].type == PJMEDIA_TYPE_AUDIO) {

            switch (call_info.media[i].status) {

                case PJSUA_CALL_MEDIA_ACTIVE: {
                    printf(".........Connect conf.....\n ");
                    pjsua_conf_connect(call_info.media[i].stream.aud.conf_slot, 0);
                    pjsua_conf_connect(0, call_info.media[i].stream.aud.conf_slot);

                    if (act_conference) {
                        pjsua_call_id call_ids[PJSUA_MAX_CALLS];
                        printf("PJSUA_MAX_CALLS:  %d  \n ", PJSUA_MAX_CALLS);
                        unsigned call_cnt = PJ_ARRAY_SIZE(call_ids);
                        unsigned j;

                        /* Get all calls, and establish media connection between
                         * this call and other calls.
                         */
                        pjsua_enum_calls(call_ids, &call_cnt);
                        for (j = 0; j < call_cnt; ++j) {
                            if (call_ids[j] != call_id) {
                                pjsua_conf_connect(call_info.media[i].stream.aud.conf_slot,
                                                   pjsua_call_get_conf_port(call_ids[j]));
                                pjsua_conf_connect(pjsua_call_get_conf_port(call_ids[j]),
                                                   call_info.media[i].stream.aud.conf_slot);
                            }
                        }
                    }
                    act_conference = 0;

                    break;
                }
                case PJSUA_CALL_MEDIA_LOCAL_HOLD:
                    printf("MEDIA STATUS: LOCAL HOLD\n");
                    break;

                case PJSUA_CALL_MEDIA_REMOTE_HOLD:
                    printf("MEDIA STATUS: REMOTE HOLD\n");
                    break;
                case PJSUA_CALL_MEDIA_NONE:
                    printf("MEDIA STATUS: NONE\n");
                    break;
                default:
                    break;
            }

        }

    }

}
