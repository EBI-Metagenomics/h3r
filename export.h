#ifndef H3R_API_H
#define H3R_API_H

/* clang-format off */
#ifdef H3R_STATIC_DEFINE
#  define H3R_API
#else
#  ifdef imm_EXPORTS /* We are building this library */
#    ifdef _WIN32
#      define H3R_API __declspec(dllexport)
#    else
#      define H3R_API __attribute__((visibility("default")))
#    endif
#  else /* We are using this library */
#    ifdef _WIN32
#      define H3R_API __declspec(dllimport)
#    else
#      define H3R_API __attribute__((visibility("default")))
#    endif
#  endif
#endif
/* clang-format on */

#endif
