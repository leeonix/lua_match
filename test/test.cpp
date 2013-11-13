// =====================================================================================
//
//       Filename:  test.c
//         Author:  LeeoNix
//        Created:  2013-11-13 7:35:32
//
//    Description:
//
// =====================================================================================

#include <cstdio>
#include <cstdlib>
#include "lua_match_cxx.hpp"

const char *src = "123456789abcdefgh03212345ijklmn";
const char *sub = "abc";
const char *err_reg = "(%d*).-(%d*)[abc";
const char *right_reg = "(%d+).-(%d+)";
const char *no_reg = "@@@@";


int main(int argc, char *argv[])
{
    size_t i;
    string_list strlist;

    printf("error pattern\n");
    printf("----------------------------------------\n");
    switch (match_to_string_list(strlist, src, err_reg))
    {
    case MATCH_SUCCESS:
        for (i = 0; i < strlist.size(); ++i)
        {
            printf("str(%s) len(%d)\n", strlist[i].c_str(), strlist[i].size());
        }
        break;
    case MATCH_FAILURE:
        break;
    case MATCH_SYNTAX_ERROR:
        printf(get_error_str());
        break;
    }

    printf("\n\nright pattern\n");
    printf("----------------------------------------\n");
    switch (match_to_string_list(strlist, src, right_reg))
    {
    case MATCH_SUCCESS:
        for (i = 0; i < strlist.size(); ++i)
        {
            printf("str(%s) len(%d)\n", strlist[i].c_str(), strlist[i].size());
        }
        break;
    case MATCH_FAILURE:
        break;
    case MATCH_SYNTAX_ERROR:
        printf(get_error_str());
        break;
    }

    printf("\n\nno pattern\n");
    printf("----------------------------------------\n");
    switch (match_to_string_list(strlist, src, no_reg))
    {
    case MATCH_SUCCESS:
        for (i = 0; i < strlist.size(); ++i)
        {
            printf("str(%s) len(%d)\n", strlist[i].c_str(), strlist[i].size());
        }
        break;
    case MATCH_FAILURE:
        printf("not find\n");
        break;
    case MATCH_SYNTAX_ERROR:
        printf(get_error_str());
        break;
    }
    return EXIT_SUCCESS;
}               // ----------  end of function main  ---------- 

