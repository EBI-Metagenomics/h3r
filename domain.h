#ifndef DOMAIN_H
#define DOMAIN_H

#include "alidisplay.h"
#include "static_assert.h"
#include <stdbool.h>
#include <stdint.h>

struct domain;
struct lip_file;

struct domain
{
  unsigned long ienv;
  unsigned long jenv;
  unsigned long iali;
  unsigned long jali;
  float envsc;
  float domcorrection;
  float dombias;
  float oasc;
  float bitscore;
  double lnP;
  bool is_reported;
  bool is_included;
  unsigned pos_score_size;
  float *pos_score;
  struct alidisplay ad;
};

h3r_static_assert(sizeof(long) >= 8);

void h3r_domain_init(struct domain *);
int h3r_domain_setup(struct domain *, unsigned scores_size);
void h3r_domain_cleanup(struct domain *);
int h3r_domain_pack(struct domain const *, struct lip_file *);
int h3r_domain_unpack(struct domain *, struct lip_file *);

#endif
