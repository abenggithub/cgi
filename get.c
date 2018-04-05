#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *data;
    char a[10], b[10];
    printf("<!DOCTYPE HTML>\n\n");
    printf("<HTML>\n");
    printf("<HEAD>\n");
    printf("<title>GET Method</title>\n");
    printf("</HEAD>\n");

    printf("<div style=\"font-size:12px\">\n");
    data = getenv("QUERY_STRING");
    if (sscanf(data, "a=%[^&]&b=%s", a, b) != 2) {
        printf("<div style=\"color:red\">Error paramenters should be entered!</div>\n");
    }
    else {
        printf("<div style=\"color:green; font-size:15px; font-weight=bold\">a + b = %d<div>\n", atoi(a) + atoi(b));
    }

    printf("<hr color=\"blue\" align=\"left\" width=\"100\">");
    printf("<p> ------------------TEST---------------</p>\n");
    printf("<\"input type=\"button\" value=\"Back CGI\" onclick=\"javascript:window.location='../cgi.html'\">");
    printf("</div>\n");
    printf("</body>\n");
    printf("</html>\n");
    return 0;
}