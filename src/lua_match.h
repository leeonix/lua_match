// =====================================================================================
//
//       Filename:  lua_match.h
//         Author:  LeeoNix
//        Created:  2013-11-12 19:47:51
//
//    Description:
//
// =====================================================================================

#ifndef  ___lua_match_INC___
#define  ___lua_match_INC___

#include <string.h>
#include "lua_buffer.h"

#if defined(__cplusplus)
extern "C" {
#endif

enum result_code_t
{
    MATCH_SUCCESS,
    MATCH_FAILURE,
    MATCH_SYNTAX_ERROR,
};

extern const char *get_error_str();

#define MAX_CAPTURES        32

typedef struct capture_t
{
    int count;
    struct
    {
        const char *init;
        size_t len;
    } capture[MAX_CAPTURES];
    ptrdiff_t start_pos, end_pos;
} capture_t;


extern int str_find(capture_t *cap, const char *s, size_t ls, const char *p, size_t lp, int start);
extern int str_match(capture_t *cap, const char *s, size_t ls, const char *p, size_t lp, int start);

#define s_find(cap, s, p) str_find(cap, s, strlen(s), p, strlen(p), 0)
#define s_match(cap, s, p) str_match(cap, s, strlen(s), p, strlen(p), 0)

extern buffer_t * simple_str_gsub(const char *s, const char *p, const char *r);

#if defined(__cplusplus)
}
#endif
#endif   // ----- #ifndef ___lua_match_INC___  ----- 

