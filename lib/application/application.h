#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "includes.h"
#include "cJSON.h"

#ifdef __AVR__
  #include <util/delay.h>
#else
  #include <unistd.h>
#endif

extern bool ping_timeout;
extern int timeout_count;
extern char received_message[128];
extern struct AES_ctx my_AES_ctx;

void init_all();
void pad_input(uint8_t *input, size_t *length);
void AES_ECB_encrypt_buffer(struct AES_ctx *ctx, uint8_t *buf, size_t length);
void AES_ECB_decrypt_buffer(struct AES_ctx *ctx, uint8_t *buf, size_t length);
void create_and_send_weather();
void update_data();
WIFI_ERROR_MESSAGE_t wifi_connect();
void app_start();

