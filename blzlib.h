#ifndef BLZLIB_H
#define BLZLIB_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <systemd/sd-bus.h>

typedef struct blz_context blz;
typedef struct blz_dev blz_dev;
typedef struct blz_char blz_char;

typedef void (*blz_notify_handler_t)(const char* data, size_t len, blz_char* ch);
typedef void (*blz_scan_handler_t)(const char* name, const uint8_t* mac);

blz* blz_init(const char* dev);
void blz_fini(blz* ctx);

bool blz_scan_start(blz* ctx, blz_scan_handler_t cb);
bool blz_scan_stop(blz* ctx);

blz_dev* blz_connect(blz* ctx, const uint8_t* mac);
void blz_disconnect(blz_dev* dev);

blz_char* blz_get_char_from_uuid(blz_dev* dev, const char* uuid);

bool blz_char_write(blz_char* ch, const char* data, size_t len);
int blz_char_read(blz_char* ch, char* data, size_t len);
bool blz_char_notify_start(blz_char* ch, blz_notify_handler_t cb);
bool blz_char_notify_stop(blz_char* ch);
/** need to close(fd) to release */
int blz_char_write_fd_acquire(blz_char* ch);

void blz_loop(blz* ctx);
int blz_get_fd(blz* ctx);
int blz_get_events(blz* ctx);
uint64_t blz_get_timeout(blz* ctx);
void blz_process(blz* ctx);
sd_bus* blz_get_sdbus(blz* ctx);

#endif
