#include <stdio.h>
#include <string.h>
#include "remake.h"

//fix build - GNU 
#define ngx_http_vod_match_prefix_postfix(start_pos, end_pos, prefix, postfix)				\
	((end_pos) - (start_pos) >= (int)(prefix)->len + (int)sizeof(postfix) - 1 &&			\
	ngx_memcmp((end_pos) - (sizeof(postfix) - 1), (postfix), sizeof(postfix) - 1) == 0 &&	\
	ngx_memcmp((start_pos), (prefix)->data, (prefix)->len) == 0)

static const u_char _txt_file_ext[] = ".txt";
static const u_char _jpg_file_ext[] = ".jpg";
static const u_char _png_file_ext[] = ".png";
static const u_char _js_file_ext[] = ".js";
static const u_char _webp_file_ext[] = ".webp";
static const u_char _css_file_ext[] = ".css";
static const u_char _ico_file_ext[] = ".ico";


static vod_str_t _jpg_suffix = vod_string(".jpg\n");
static vod_str_t _png_suffix = vod_string(".png\n");
static vod_str_t _js_suffix = vod_string(".js\n");
static vod_str_t _webp_suffix = vod_string(".webp\n");
static vod_str_t _css_suffix = vod_string(".css\n");
static vod_str_t _txt_suffix = vod_string(".txt\n");
static vod_str_t _ico_suffix = vod_string(".ico\n");
vod_str_t* nginx_strings[EXT_LEN] = {&_jpg_suffix, &_png_suffix, &_js_suffix, &_webp_suffix, &_css_suffix, &_txt_suffix, &_ico_suffix};


vod_str_t* get_nginx_ext_string_by_index(int index) {
    vod_str_t* random = nginx_strings[index % EXT_LEN];
    return random;
}

char valid_nginx_ext_string_with_index(int index,u_char * name, int len) {
 
    vod_str_t* index_string = nginx_strings[index % EXT_LEN];
    char ext[MAX_EXT_NAME_LEN];
    memset(ext, 0,MAX_EXT_NAME_LEN);
    memcpy(ext,index_string->data,index_string->len -1 );
    if ((int)(index_string->len -1 )!= len && len > 0) {
        return 0;
    }
    if (memcmp(ext,name,len ) == 0) {
        return 1;
    }
     return 0;
}

char remake_ngx_http_vod_match_prefix_postfix( u_char* start,  u_char* end, vod_str_t* name) {
    if ( ngx_http_vod_match_prefix_postfix(start, end, name, _jpg_file_ext) ||  
    ngx_http_vod_match_prefix_postfix(start, end, name, _png_file_ext) || 
    ngx_http_vod_match_prefix_postfix(start, end, name, _ico_file_ext) || 
    ngx_http_vod_match_prefix_postfix(start, end, name, _txt_file_ext) || 
    ngx_http_vod_match_prefix_postfix(start, end, name, _css_file_ext)) {
        return 4;
    }
    if ( ngx_http_vod_match_prefix_postfix(start, end, name, _js_file_ext)  ) {
        return 3;
    }
     
    if (  ngx_http_vod_match_prefix_postfix(start, end, name, _webp_file_ext)  ) {
        return 5;
    }
    
    return 0;
}