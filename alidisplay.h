#ifndef ALIDISPLAY_H
#define ALIDISPLAY_H

#include "static_assert.h"
#include <stdio.h>

struct lip_file;

struct alidisplay
{
  unsigned presence;

  char *rfline;
  char *mmline;
  char *csline;
  char *model;
  char *mline;
  char *aseq;
  char *ntseq;
  char *ppline;
  unsigned N;

  char *hmmname;
  char *hmmacc;
  char *hmmdesc;
  unsigned hmmfrom;
  unsigned hmmto;
  unsigned M;

  char *sqname;
  char *sqacc;
  char *sqdesc;
  unsigned sqfrom;
  unsigned sqto;
  unsigned L;
};

h3r_static_assert(sizeof(unsigned) >= 4);

int h3r_alidisplay_init(struct alidisplay *);
void h3r_alidisplay_cleanup(struct alidisplay *);
int h3r_alidisplay_pack(struct alidisplay const *, struct lip_file *);
int h3r_alidisplay_unpack(struct alidisplay *, struct lip_file *);
void h3r_alidisplay_print(struct alidisplay const *, FILE *file);

#endif
