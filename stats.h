#ifndef STATS_H
#define STATS_H

#include "static_assert.h"
#include "zsetby.h"
#include <stdint.h>

struct stats;
struct lip_file;

struct stats
{
  double Z;
  double domZ;

  enum zsetby Z_setby;
  enum zsetby domZ_setby;

  unsigned nmodels;
  unsigned nseqs;
  unsigned n_past_msv;
  unsigned n_past_bias;
  unsigned n_past_vit;
  unsigned n_past_fwd;

  unsigned nhits;
  unsigned nreported;
  unsigned nincluded;
};

h3r_static_assert(sizeof(unsigned) >= 4);

void h3r_stats_init(struct stats *);
int h3r_stats_pack(struct stats const *, struct lip_file *);
int h3r_stats_unpack(struct stats *, struct lip_file *);

#endif
