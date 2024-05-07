
#include "../common.h"
vod_str_t* get_nginx_ext_string_by_index(int index) ;
char valid_nginx_ext_string_with_index(int index,u_char * name, int len);
char remake_ngx_http_vod_match_prefix_postfix(u_char* start, u_char* end,  vod_str_t *name );
vod_str_t* get_content_type_nginx_ext_string_with_index(int index);
#define MAX_EXT_NAME_LEN 6
#define EXT_LEN 7

