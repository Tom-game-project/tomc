#include <stdio.h>

int main ()
{
    // c言語を触っているときに偶然見つけた重要かもしれない性質
    // 宣言の微妙な違いによって、メモリにおけるデータの配置の仕方が異なったものとなる
    // 特に `char a[6] = "world";`のように宣言した場合、
    // null文字が入っていないので予期しない動作の原因になる

    char a[6] = "world\0";
    char b[5] = "hello";
    printf("%s\n",b);// helloworld
    printf("world p:%p\nhello p:%p\ndiff %ld\n",a,b,a-b);
    for (int i = 0;i < 11;i++)
    {
        if (b[i])
            printf("%c",b[i]);
        else
            printf("*");
    }

    // char *a ="world";
    // char *b ="hello";
    // printf("%s\n",b);
    // printf("world p:%p\nhello p:%p\ndiff %ld\n",a,b,a-b);
    // for (int i = 0;i < 11;i++)
    // {
    //     if (a[i])
    //         printf("%c",a[i]);
    //     else
    //         printf("*");
    // }

}