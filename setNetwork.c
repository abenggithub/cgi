#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN (200)
#define EXTRA (100)
#define MAXINPUT (MAXLEN + EXTRA + 2)
#define DATAFILE "/home/root/wifi_conf.json"

void unencode(char *src, char *last, char *dest)
{
 for(; src != last; src++, dest++)
   if(*src == '+')
     *dest = ' ';
   else if (*src == '%') {
     int code;
     if (sscanf(src+1, "%2x", &code) != 1) code = '?';
     *dest = code;
     src +=2; }     
   else
     *dest = *src;
 *dest = '\n';
 *++dest = '\0';
}

void unencode_2(char *src, char *last, char *dest)
{
 for(; src != last; src++, dest++)
   if(*src == '+')
     *dest = ' ';
   else if (*src == '%') {
     int code;
     if (sscanf(src+1, "%2x", &code) != 1) code = '?';
     *dest++ = '\\';
     *dest = code;
     src +=2; }     
   else
     *dest = *src;
 *dest = '\n';
 *++dest = '\0';
}

int save_network_conf_to_file(const char *filename, char* ssid, char *pw)
{
    if (!filename) {
        printf("<p>[%s: %d]没有指定文件名</p>\n", __func__, __LINE__);
        return -1;
    }

    FILE *fp = NULL;
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("<p>对不起，无法保存数据</p>\n");
    }
    else {
        /*write json file*/
        fwrite(ssid, strlen(ssid), 1, fp);
        fputc('\n', fp);
        fwrite(pw, strlen(pw), 1, fp);
        fputc('\n', fp);
    }
    fclose(fp);
    return 0;
}

#define MAP_SIZE (256)
#define FORM_BUF_SIZE (4096)

char form_buf[FORM_BUF_SIZE] = {0,};
char buf[FORM_BUF_SIZE] = {0, };

int get_form_data()
{
    char *post_len_ptr = NULL;
    char *get_data_ptr = NULL;
    long len = 0;

    memset(form_buf, 0, FORM_BUF_SIZE);
    memset(buf, 0, FORM_BUF_SIZE);
    
    if (NULL != (post_len_ptr = getenv("CONTENT_LENGTH"))
        && sscanf(post_len_ptr, "%ld", &len) == 1 
        && 0 < len && len < FORM_BUF_SIZE) {
            
        printf("<p>Recv post form:%s.</p>\n", post_len_ptr);
        fgets(form_buf, len + 1, stdin);
    }
    else if (get_data_ptr = getenv("QUERY_STRING")) {
        printf("<p>Recv get form:%s.</p>\n", get_data_ptr);
        len = strlen(get_data_ptr);
        strncpy(form_buf, get_data_ptr, len);
    }
    else {
        printf("<p>Recv form data failed!</p>\n");
        return -1;
    }
    unencode(form_buf, form_buf + len, buf);

    return 0;
} 

int main(int argc, char *argv[])
{
    char *lenstr = NULL;
    char input[MAXINPUT] = {0,}, data[MAXINPUT] = {0,};
    long len = 0;
    char ssid[20] = {0, };
    char pw[20] = {0, };
    printf("Content-Type:text/html;charset=utf-8\r\n\n");
    printf("<html>");
    printf("<title>Response</title>");
    printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"./css/main.css\">");
    printf("<body>\n");
    printf("<div class=\"info\">\n");
#if 0
    get_form_data();   
#endif
    
    lenstr = getenv("CONTENT_LENGTH");
    if (lenstr == NULL || sscanf(lenstr,"%ld", &len) != 1 || len > MAXINPUT) {
        printf("<p>表单填写错误</p>");
    }
    else {
        fgets(input, len + 1, stdin);
        unencode_2(input,input+len, data);
        sscanf(data, "ssid=%[^&]&pw=%s", ssid, pw);

        save_network_conf_to_file(DATAFILE, ssid, pw);
        
        printf("<p>SSID & 密码已经保存到：%s</p>\n", DATAFILE);
    }
    printf("</body>\n");
    printf("</html>\n");
    fflush(stdout);
    return 0;
}