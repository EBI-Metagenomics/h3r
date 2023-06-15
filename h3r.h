#ifndef H3R_H3R_H
#define H3R_H3R_H

#ifdef __cplusplus
extern "C" {
#endif

#include "export.h"
#include "strerror.h"
#include <stdio.h>

struct h3r;

H3R_API struct h3r *h3r_new(void);
H3R_API void h3r_del(struct h3r const *);

H3R_API int h3r_pack(struct h3r const *, FILE *);
H3R_API int h3r_unpack(struct h3r *, FILE *);

H3R_API int h3r_errnum(struct h3r const *);
H3R_API char const *h3r_errstr(struct h3r const *);

H3R_API void h3r_print_targets(struct h3r const *, FILE *);
H3R_API void h3r_print_domains(struct h3r const *, FILE *);

H3R_API void h3r_print_targets_table(struct h3r const *, FILE *);
H3R_API void h3r_print_domains_table(struct h3r const *, FILE *);

H3R_API unsigned h3r_nhits(struct h3r const *);
H3R_API char const *h3r_hit_name(struct h3r const *, unsigned idx);
H3R_API char const *h3r_hit_acc(struct h3r const *, unsigned idx);
H3R_API double h3r_hit_evalue_ln(struct h3r const *, unsigned idx);

#ifdef __cplusplus
}
#endif

#endif
