#ifndef ECHO_H
#define ECHO_H

#include <stdio.h>

void h3r_echo(FILE *, char const *, ...) __attribute__((format(printf, 2, 3)));

#endif
