// =====================================================================================
//
//       Filename:  test.c
//         Author:  LeeoNix
//        Created:  2013-11-13 7:35:32
//
//    Description:
//
// =====================================================================================

#include <stdio.h>
#include <stdlib.h>
#include "lua_match.h"

const char *src = "123456789abcdefgh12345ijklmn";
const char *sub = "abc";
const char *reg = "(%d+).-(%d+)";

//#define STR_SRC "1  33.34%  4   m\n2  50.00%  5   m"
#define STR_SRC "1  33.34%  4   m 2  50.00%  5   m"
#define STR_PATTERN "(%d+)%s+(%d+%.%d+)%D+(%d+)%s+(%S+).-(%d+%.%d+)"

int main(int argc, char *argv[])
{
    int i;
    capture_t caps;
    if (MATCH_SUCCESS == s_find(&caps, src, sub))
    {
        printf("pos(%d/%d)\n", caps.start_pos, caps.end_pos);
        printf("start %s | end %s\n", src + caps.start_pos, src + caps.end_pos);
        printf("init(%s) len(%d)\n", caps.capture[0].init, caps.capture[0].len);
    }

    printf("-----\n");

    switch (str_match(&caps, src, strlen(src), reg, strlen(reg), 0))
    {
    case MATCH_SUCCESS:
        for (i = 0; i < caps.count; ++i)
        {
            printf("init(%s) len(%d)\n", caps.capture[i].init, caps.capture[i].len);
        }
        break;
    case MATCH_FAILURE:
        break;
    case MATCH_SYNTAX_ERROR:
        printf(get_error_str());
        break;
    }

    printf("-----\n");

    switch (str_find(&caps, STR_SRC, sizeof(STR_SRC) - 1, STR_PATTERN, sizeof(STR_PATTERN) - 1, 0))
    {
    case MATCH_SUCCESS:
        printf("pos(%d/%d)\n", caps.start_pos, caps.end_pos);
        printf("start:%s | end:%s\n", STR_SRC + caps.start_pos, STR_SRC + caps.end_pos);
        for (i = 0; i < caps.count; ++i)
        {
            printf("init(%s) len(%d)\n", caps.capture[i].init, caps.capture[i].len);
        }
        break;
    case MATCH_SYNTAX_ERROR:
        printf(get_error_str());
        break;
    }

    printf("-----\n");

    switch (s_find(&caps, src, "@@@"))
    {
    case MATCH_SUCCESS:
        printf("find!\n");
        break;
    case MATCH_FAILURE:
        printf("not find!\n");
        break;
    }

    {
        buffer_t *b = simple_str_gsub(src, "123", "@@@123@@@");
        if (b)
        {
            printf(b->buf);
        }
        free_buffer(b);
    }

    return EXIT_SUCCESS;
}               // ----------  end of function main  ----------

