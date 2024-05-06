#include <stdio.h>
#include <string.h>
#include "remake.h"
#include "../../ngx_http_vod_request_parse.h"


static const u_char _jpg_file_ext[] = ".jgp";
static const u_char _png_file_ext[] = ".png";
static const u_char _js_file_ext[] = ".js";
static const u_char _webp_file_ext[] = ".webp";
static const u_char _css_file_ext[] = ".css";


static vod_str_t _jpg_suffix = vod_string(".jpg \n");
static vod_str_t _png_suffix = vod_string(".png \n");
static vod_str_t _js_suffix = vod_string(".js  \n");
static vod_str_t _webp_suffix = vod_string(".webp\n");
static vod_str_t _css_suffix = vod_string(".css \n");
vod_str_t* nginx_strings[MAX_EXT_NAME_LEN] = {&_jpg_suffix, &_png_suffix, &_js_suffix, &_webp_suffix, &_css_suffix};


vod_str_t* get_nginx_ext_string_by_index(int index) {
    vod_str_t* random = nginx_strings[index % EXT_LEN];
    return random;
}

char valid_nginx_ext_string_with_index(int index, char*name) {
    return 1;
}

char remake_ngx_http_vod_match_prefix_postfix( u_char* start,  u_char* end, vod_str_t* name) {
    if ( ngx_http_vod_match_prefix_postfix(start, end, name, _jpg_file_ext) ||  
    ngx_http_vod_match_prefix_postfix(start, end, name, _png_file_ext) || 
    ngx_http_vod_match_prefix_postfix(start, end, name, _css_file_ext)) {
        return 4;
    }
    if (  ngx_http_vod_match_prefix_postfix(start, end, name, _js_file_ext)  ) {
        return 3;
    }
     
    if (  ngx_http_vod_match_prefix_postfix(start, end, name, _webp_file_ext)  ) {
        return 5;
    }
    return 0;
}