// =====================================================================================
//
//       Filename:  lua_match.c
//         Author:  LeeoNix
//        Created:  2013-11-12 19:47:41
//
//    Description:
//
// =====================================================================================

#include <setjmp.h>
#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lua_match.h"

// define error_str function and exception macro

static char error_str[BUFSIZ];

#if defined(__cplusplus)
#define __MATCH_THROW()    throw(1)
#define __MATCH_TRY        error_str[0] = '\0'; try
#define __MATCH_CATCH      catch(...)
#else
static jmp_buf __jb;
#define __MATCH_THROW()    longjmp(__jb, 1)
#define __MATCH_TRY        error_str[0] = '\0'; if (setjmp(__jb) == 0)
#define __MATCH_CATCH      else
#endif

const char * get_error_str()
{
    return error_str;
}

static void set_error(const char *s)
{
    strcpy(error_str, s);
    __MATCH_THROW();
}

// fake some lua type

#define LUA_MAXCAPTURES		MAX_CAPTURES
#define lua_State int

static int luaL_error(lua_State *L, const char *fmt, ...)
{
    va_list argp;

    (void)L;
    va_start(argp, fmt);
    _vsnprintf(error_str, BUFSIZ - 1, fmt, argp);
    va_end(argp);
    __MATCH_THROW();
    return 0;
}

#include "lua_pattern_matching.i"

////////////////////////////////////////////////////////////////////////////////


static void copy_captures(MatchState *ms, capture_t *cap)
{
    int i;
    for (i = 0; i < ms->level; ++i)
    {
        ptrdiff_t l = ms->capture[i].len;
        if (l == CAP_UNFINISHED)
            set_error("unfinished capture");
        cap->capture[i].init = ms->capture[i].init;
        cap->capture[i].len  = (size_t) ms->capture[i].len;
    }
    cap->count = ms->level;
}

static int internal_match(capture_t *cap, const char *s, size_t ls, const char *p, size_t lp, size_t init)
{
    MatchState ms;
    const char *s1 = s + init;
    int anchor = (*p == '^');
    if (anchor)
    {
        p++;
        lp--;  /* skip anchor character */
    }
    ms.matchdepth = MAXCCALLS;
    ms.src_init = s;
    ms.src_end = s + ls;
    ms.p_end = p + lp;
    do
    {
        const char *res;
        ms.level = 0;
        assert(ms.matchdepth == MAXCCALLS);
        if ((res = match(&ms, s1, p)) != NULL)
        {
            cap->start_pos = s1 - s;
            cap->end_pos = res - s - 1;
            copy_captures(&ms, cap);
            return MATCH_SUCCESS;
        }
    }
    while (s1++ < ms.src_end && !anchor);
    return MATCH_FAILURE;
}

int str_find(capture_t *cap, const char *s, size_t ls, const char *p, size_t lp, int start)
{
    __MATCH_TRY
    {
        size_t init = posrelat(start, ls);
        if (init > ls)
            return 0;
        if (nospecials(p, lp))
        {
            const char *res = lmemfind(s + init, ls - init, p, lp);
            if (res)
            {
                cap->capture[0].init = res;
                cap->capture[0].len = lp;
                cap->start_pos = res - s;
                cap->end_pos = cap->start_pos + lp - 1;
                return MATCH_SUCCESS;
            }
            return MATCH_FAILURE;
        }
        else
            return internal_match(cap, s, ls, p, lp, init);
    }
    __MATCH_CATCH
    {
        return MATCH_SYNTAX_ERROR;
    }
}

int str_match(capture_t *cap, const char *s, size_t ls, const char *p, size_t lp, int start)
{
    __MATCH_TRY
    {
        size_t init = posrelat(start, ls);
        if (init > ls)
            return MATCH_FAILURE;
        return internal_match(cap, s, ls, p, lp, init);
    }
    __MATCH_CATCH
    {
        return MATCH_SYNTAX_ERROR;
    }
}


buffer_t * simple_str_gsub(const char *s, const char *p, const char *r)
{
    buffer_t *b = new_buffer();
    if (b != NULL)
    {
        const char *wild;
        size_t l = strlen(p);
        size_t rl = strlen(r);
        while ((wild = strstr(s, p)) != NULL)
        {
            buffer_add_str(b, s, wild - s);
            buffer_add_str(b, r, rl);
            s = wild + l;
        }
        buffer_add_str(b, s, strlen(s) + 1);
    }
    return b;
}

