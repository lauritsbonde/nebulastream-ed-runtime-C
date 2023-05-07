#include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <time.h>

// #include "lora.h"

// #include "thread.h"
// #include "msg.h"
// #include "fmt.h"
// #include "net/loramac.h"
// #include "semtech_loramac.h"

// extern semtech_loramac_t loramac;

// static uint8_t deveui[LORAMAC_DEVEUI_LEN];
// static uint8_t appeui[LORAMAC_APPEUI_LEN];
// static uint8_t appkey[LORAMAC_APPKEY_LEN];

// void send_message(uint8_t* serializedData, uint8_t len)
// {
//     printf("Sending: %s\n", serializedData);
//     /* Try to send the message */
//     uint8_t ret = semtech_loramac_send(&loramac,serializedData, len);
//     if (ret != SEMTECH_LORAMAC_TX_DONE) {
//         printf("Cannot send message, ret code: %d\n", ret);
//         return;
//     }
// }

// msg_t receive_message(void) {
//     msg_t msg;
//     msg_receive(&msg);

//     return msg;
// }

// int connect_lorawan(void)
// {
//     /* Convert identifiers and keys strings to byte arrays */
//     fmt_hex_bytes(deveui, CONFIG_LORAMAC_DEV_EUI_DEFAULT);
//     fmt_hex_bytes(appeui, CONFIG_LORAMAC_APP_EUI_DEFAULT);
//     fmt_hex_bytes(appkey, CONFIG_LORAMAC_APP_KEY_DEFAULT);
//     semtech_loramac_set_deveui(&loramac, deveui);
//     semtech_loramac_set_appeui(&loramac, appeui);
//     semtech_loramac_set_appkey(&loramac, appkey);

//     /* Use a fast datarate, e.g. BW125/SF7 in EU868 */
//     semtech_loramac_set_dr(&loramac, LORAMAC_DR_5);

//     /* Join the network if not already joined */
//     if (!semtech_loramac_is_mac_joined(&loramac)) {
//         /* Start the Over-The-Air Activation (OTAA) procedure to retrieve the
//          * generated device address and to get the network and application session
//          * keys.
//          */
//         printf("Starting join procedure\n");
//         if (semtech_loramac_join(&loramac, LORAMAC_JOIN_OTAA) != SEMTECH_LORAMAC_JOIN_SUCCEEDED) {
//             printf("Join procedure failed\n");
//             return 1;
//         }

//     }
//     printf("Join procedure succeeded");

//     /* trigger the first send */
//     msg_t msg;
//     kernel_pid_t sender_pid = thread_getpid();
//     msg_send(&msg, sender_pid);
//     return 0;
// }

void remove_me(void){
    printf("fix lora.c");
}