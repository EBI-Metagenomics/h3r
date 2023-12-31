#include "strerror.h"
#include "rc.h"
#include <stdio.h>

static char const *msg[] = {
    [H3R_EUNPACK] = "unpack failure",
    [H3R_EPACK] = "pack failure",
    [H3R_ENOMEM] = "insufficient free memory",
};

#define array_size(arr) (sizeof(arr) / sizeof((arr)[0]))

char const *h3r_strerror(int rc)
{
  if (rc > 0 && rc < (int)array_size(msg)) return msg[rc];

  static char unknown[32] = {0};
  snprintf(unknown, sizeof unknown, "unknown error #%d", rc);
  return unknown;
}
