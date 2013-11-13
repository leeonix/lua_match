// =====================================================================================
//
//       Filename:  lua_match.hpp
//         Author:  LeeoNix
//        Created:  2013-11-13 11:09:20
//
//    Description:
//
// =====================================================================================

#ifndef  ___lua_match_hpp_INC___
#define  ___lua_match_hpp_INC___

#include <vector>
#include <string>
#include "lua_match.h"

typedef std::vector<std::string> string_list;

extern int match_to_string_list(string_list &strlist,
                                const std::string &from,
                                const std::string pattern,
                                int start = 0);

#endif   // ----- #ifndef ___lua_match_hpp_INC___  -----

