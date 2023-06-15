#ifndef ZERO_CLIP_H
#define ZERO_CLIP_H

static inline unsigned h3r_zero_clip(int x) { return x > 0 ? (unsigned)x : 0; }

#endif
