#ifndef EXPECT_H
#define EXPECT_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct lip_file;

bool h3r_expect_key(struct lip_file *f, char const *key);
bool h3r_expect_array_size(struct lip_file *f, unsigned size);
bool h3r_expect_map_size(struct lip_file *f, unsigned size);
int h3r_read_string(struct lip_file *f, char **str);

#endif
