#include <stdio.h>
#include <stdlib.h>

int main (void) 
{
    int len;
    char *lenstr, poststr[20];
    long m = 0;
    long n = 0;
    printf("<!DOCTYPE HTML>\n");
    printf("<html>\n");
    printf("<HEAD>\n");
    printf("<TITLE>post Method</TITLE>");
    printf("</head>\n");
    printf("<body>\n");
    lenstr=getenv("CONTENT_LENGTH");
    if (lenstr == NULL) {
        printf("<div style=\"color:red;\">Error parameters should be entered!</div>\n");
    }
    else {
        len = atoi(lenstr);
        fgets(poststr, len + 1, stdin);
        if (sscanf(poststr, "m=%ld&n=%ld", &m, &n) != 2) {
            printf("<div style=\"color:red;\">Error: Paramenters are not night!</div>\n");
        }
        else {
            printf("<div style=\"color:green; font-size:15px; font-weight:bold\">%ld * %ld = %ld</div>\n", m, n, m*n);            
        }
    }
    printf("<HR COLOR=\"blue\" align=\"left\" width=\"100\">");
    printf("<input type=\"button\" value=\"Back CGI\" onclick=\"javascript:window.location='../cgi.html'\">");
    printf("</div>\n");
    printf("</BODY>\n");
    printf("</HTML>\n");
    fflush(stdout);
    return 0;   
}