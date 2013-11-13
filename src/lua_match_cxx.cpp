// =====================================================================================
//
//       Filename:  lua_match.cpp
//         Author:  LeeoNix
//        Created:  2013-11-13 11:10:30
//
//    Description:
//
// =====================================================================================

#include "lua_match_cxx.hpp"

int match_to_string_list(string_list &strlist,
                         const std::string &from,
                         const std::string pattern,
                         int start/* = 0 */)
{
    strlist.clear();
    capture_t cap;
    int r = str_find(&cap, from.c_str(), from.size(), pattern.c_str(), pattern.size(), start);
    if (MATCH_SUCCESS == r)
    {
        for (int i = 0; i < cap.count; ++i)
        {
            strlist.push_back(std::string(cap.capture[i].init, cap.capture[i].len));
        }
    }
    return r;
}

