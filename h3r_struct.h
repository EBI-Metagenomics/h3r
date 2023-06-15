#ifndef H3R_STRUCT_H
#define H3R_STRUCT_H

#include "stats.h"
#include "tophits.h"

struct h3r
{
  int errnum;
  char const *errstr;
  struct stats stats;
  struct tophits tophits;
};

#endif
