#include "h3r.h"
#include "expect.h"
#include "h3r_struct.h"
#include "lip/lip.h"
#include "rc.h"
#include <stdlib.h>

struct h3r *h3r_new(void)
{
  struct h3r *result = malloc(sizeof(*result));
  if (!result) return 0;
  result->errnum = 0;
  result->errstr = NULL;
  h3r_stats_init(&result->stats);
  h3r_tophits_init(&result->tophits);
  return result;
}

void h3r_del(struct h3r const *result)
{
  if (result->errstr) free((void *)result->errstr);
  h3r_tophits_cleanup((struct tophits *)&result->tophits);
  free((void *)result);
}

int h3r_pack(struct h3r const *result, FILE *file)
{
  struct lip_file f = {0};
  lip_file_init(&f, file);

  lip_write_map_size(&f, 1);
  lip_write_cstr(&f, "h3result");

  lip_write_map_size(&f, 2);
  lip_write_cstr(&f, "stats");
  int rc = h3r_stats_pack(&result->stats, &f);
  if (rc) return rc;

  lip_write_cstr(&f, "tophits");
  return h3r_tophits_pack(&result->tophits, &f);
}

int h3r_unpack(struct h3r *result, FILE *file)
{
  struct lip_file f = {0};
  lip_file_init(&f, file);

  if (!h3r_expect_map_size(&f, 1)) return H3R_EUNPACK;

  if (!h3r_expect_key(&f, "h3result")) return H3R_EUNPACK;

  if (!h3r_expect_map_size(&f, 2)) return H3R_EUNPACK;
  if (!h3r_expect_key(&f, "stats")) return H3R_EUNPACK;
  int rc = h3r_stats_unpack(&result->stats, &f);
  if (rc) return rc;

  if (!h3r_expect_key(&f, "tophits")) return H3R_EUNPACK;
  return h3r_tophits_unpack(&result->tophits, &f);
}

int h3r_errnum(struct h3r const *x) { return x->errnum; }

char const *h3r_errstr(struct h3r const *x) { return x->errstr; }

void h3r_print_targets(struct h3r const *r, FILE *file)
{
  h3r_tophits_print_targets(&r->tophits, file, r->stats.Z);
}

void h3r_print_domains(struct h3r const *r, FILE *file)
{
  h3r_tophits_print_domains(&r->tophits, file, r->stats.Z, r->stats.domZ);
}

void h3r_print_targets_table(struct h3r const *r, FILE *file)
{
  h3r_tophits_print_targets_table("-", &r->tophits, file, true, r->stats.Z);
}

void h3r_print_domains_table(struct h3r const *r, FILE *file)
{
  h3r_tophits_print_domains_table("-", &r->tophits, file, true, r->stats.Z,
                                  r->stats.domZ);
}

unsigned h3r_nhits(struct h3r const *r) { return r->tophits.nhits; }

char const *h3r_hit_name(struct h3r const *r, unsigned idx)
{
  return h3r_tophits_hit_name(&r->tophits, idx);
}

char const *h3r_hit_acc(struct h3r const *r, unsigned idx)
{
  return h3r_tophits_hit_acc(&r->tophits, idx);
}

double h3r_hit_evalue_ln(struct h3r const *r, unsigned idx)
{
  return h3r_tophits_hit_evalue_ln(&r->tophits, idx, r->stats.Z);
}
