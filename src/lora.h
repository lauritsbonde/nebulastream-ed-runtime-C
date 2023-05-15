#ifndef LORA_H
#define LORA_H

#include <stdlib.h>
#include <stdint.h>

void send_message(uint8_t* serializedData, uint8_t len);
void receive_message(void);
int connect_lorawan(void);

#endif /* LORA_H */