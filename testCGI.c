#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *param = NULL;
    long int a = 0;
    long int b = 0;
    printf("<!DOCTYPE HTML>\n");
    printf("<html>\n");
    printf("<meta charset=\"utf-8\">\n");
    printf("<head><title>CGI 调用测试页</title><head>\n");
    printf("<body>\n");
    param = getenv("QUERY_STRING");
    if (param == NULL) {
        printf("<p>error! Not param!</p>");
    }
    else if (sscanf(param, "a=%ld&b=%ld", &a, &b) != 2) {
        printf("<p>error! Input data must be integer!</p>");
    }
    else {
        printf("<p>%ld + %ld = %ld</p>", a, b, a + b);
    }
    printf("CGI调用成功!\n");
    printf("</body>\n");
    printf("</html>\n");
    return 0;
}
