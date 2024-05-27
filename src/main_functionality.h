#pragma once
#include <stdint.h>

WIFI_ERROR_MESSAGE_t wifi_connect();
void update_data();
void create_and_send_weather();
void AES_ECB_decrypt_buffer(struct AES_ctx *ctx, uint8_t *buf, size_t length);
void AES_ECB_encrypt_buffer(struct AES_ctx *ctx, uint8_t *buf, size_t length);
void pad_input(uint8_t *input, size_t *length);
void init_all();
void main_function();