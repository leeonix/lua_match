// =====================================================================================
//
//       Filename:  lua_buffer.h
//         Author:  LeeoNix
//        Created:  2013-11-12 19:45:03
//
//    Description:
//
// =====================================================================================

#ifndef  ___lua_buffer_INC___
#define  ___lua_buffer_INC___

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct buffer_t buffer_t;

#define DEFAULT_BUFSIZ 128

struct buffer_t
{
    char *buf;
    int pos;
    int str_size;
    int buf_size;
};


extern int       buffer_init(buffer_t *b, int l);
extern void      close_buffer(buffer_t *b);
extern buffer_t *new_buffer();
extern buffer_t *copy_to_buffer_len(const char *c, int l);
extern void      free_buffer(buffer_t *b);
extern int       buffer_add_char(buffer_t *b, const char c);
extern int       buffer_add_str(buffer_t *b, const char *c, int l);

#define copy_to_buffer(c) copy_to_buffer_len(c, strlen(c))

#if defined(__cplusplus)
}
#endif
#endif   // ----- #ifndef ___lua_buffer_INC___  ----- 

