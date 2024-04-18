
#include "libft.h"

#include <ctype.h>
#include <string.h>
#include <assert.h>

// isalpha
void test00()
{
    for (char c = 'a';c <= 'z';c++)
    {
        assert(isalpha(c)==ft_isalpha(c));
    }
    for (char c = 'A';c <= 'Z';c++)
    {
        assert(isalpha(c)==ft_isalpha(c));
    }
    for (char c = '0';c <= '9';c++)
    {
        assert(isalpha(c)==ft_isalpha(c));
    }
    printf("test00 done\n");
}

// isdigit
void test01()
{
    for (char c = 'a';c <= 'z';c++)
    {
        assert(isdigit(c)==ft_isdigit(c));
    }
    for (char c = 'A';c <= 'Z';c++)
    {
        assert(isdigit(c)==ft_isdigit(c));
    }
    for (char c = '0';c <= '9';c++)
    {
        assert(isdigit(c)==ft_isdigit(c));
    }
    printf("test01 done\n");
}

// isalnum
void test02()
{
    for (char c = 'a';c <= 'z';c++)
    {
        assert(isalnum(c)==ft_isalnum(c));
    }
    for (char c = 'A';c <= 'Z';c++)
    {
        assert(isalnum(c)==ft_isalnum(c));
    }
    for (char c = '0';c <= '9';c++)
    {
        assert(isalnum(c)==ft_isalnum(c));
    }
    printf("test02 done\n");
}

// isascii
void test03()
{
    for (int c = 0;c <= 127;c++)
    {
        assert(isascii(c)==ft_isascii(c));
    }
    printf("test03 done\n");
}

// isprint
void test04()
{
    for (int c = 0;c <= 127;c++)
    {
        assert(isprint(c)==ft_isprint(c));
    }
    printf("test04 done\n");
}

// strlen
void test05()
{
    char *a = "";
    char *b = "a";
    char *c = "ab";
    char *d = "abc";
    assert(strlen(a)==ft_strlen(a));
    assert(strlen(b)==ft_strlen(b));
    assert(strlen(c)==ft_strlen(c));
    assert(strlen(d)==ft_strlen(d));
    printf("test05 done\n");
}

// memset
void test06()
{
	char or_buf[] = "ABCDEFGHIJK\0";
	char ft_buf[] = "ABCDEFGHIJK\0";
	//先頭から2バイト進めた位置に「１」を3バイト書き込む
    char *a = memset(or_buf+2,'1',3);
    char *b = ft_memset(ft_buf+2,'1',3);
	for (int i = 0;i < 13;i++)
    {
        assert(or_buf[i] == ft_buf[i]);
    }
	printf("or_buf文字列→%s\n", a);
	printf("ft_buf文字列→%s\n", b);
    printf("test06 done\n");
}

// bzero
void test07()
{
    char or_buf[5] = "hello";
    char ft_buf[5] = "hello";
    bzero   (or_buf,5);
    ft_bzero(ft_buf,5);
    for (int i = 0;i < 5;i++)
    {
        assert(or_buf[i] == ft_buf[i]);
    }
    printf("test07 done\n");
}

// memcpy
void test08()
{
    char or_str1[128] = {1,1,1,1,1,1,1};
    char or_str2[] = "ab\0cde";        /* 途中に空文字のある文字列 */
    char ft_str1[128] = {1,1,1,1,1,1,1};
    char ft_str2[] = "ab\0cde";        /* 途中に空文字のある文字列 */
    int i;
    // for (i=0; i<7; i++){
    //     printf("%#x ",or_str1[i]);
    // }
    ft_memcpy(or_str1, or_str2, 5);
    memcpy   (ft_str1, ft_str2, 5);
    for (i = 0; i < 7; i++){
        // printf("%#x ",or_str1[i]);
        assert(or_str1[i] == ft_str1[i]);
    }
    printf("test08 done\n");
}

// memmove
void test09()
{
    // srcがdstよりも前
	char or_buf[] = "ABCDEFGH\0";
	char ft_buf[] = "ABCDEFGH\0";
	//bufの先頭から3バイト進めた位置にbufの先頭から3バイトコピー
	memmove(or_buf+2,or_buf,5);
	ft_memmove(ft_buf+2,ft_buf,5);
    printf("or_buf %s\n",or_buf);
    printf("ft_buf %s\n",ft_buf);
    for (int i = 0;i < 9;i++)
        assert(or_buf[i]==ft_buf[i]);

    // srcがdstよりも後
	char or_buf01[] = "ABCDEFGH\0";
	char ft_buf01[] = "ABCDEFGH\0";
	memmove(   or_buf01,or_buf01+3,5);
	ft_memmove(ft_buf01,ft_buf01+3,5);
    printf("or_buf01 %s\n",or_buf01);
    printf("ft_buf01 %s\n",ft_buf01);
    for (int i = 0;i < 10;i++)
       assert(or_buf01[i]==ft_buf01[i]);

    // 同じ場所にコピー
	char or_buf02[] = "ABCDEFGH\0";
	char ft_buf02[] = "ABCDEFGH\0";
	memmove(   or_buf02,or_buf02,5);
	ft_memmove(ft_buf02,ft_buf02,5);
    printf("or_buf02 %s\n",or_buf02);
    printf("ft_buf02 %s\n",ft_buf02);
    for (int i = 0;i < 10;i++)
       assert(or_buf02[i]==ft_buf02[i]);


    // まったく関係のない場所
	char or_dst[20];
	char ft_dst[20];
	char or_buf03[] = "ABCDEFGH\0";
	char ft_buf03[] = "ABCDEFGH\0";
	memmove(   or_dst,or_buf03,5);
	ft_memmove(ft_dst,ft_buf03,5);
    printf("or_dst %s\n",or_dst);
    printf("ft_dst %s\n",ft_dst);
    for (int i = 0;i < 10;i++)
       assert(or_dst[i]==ft_dst[i]);
    printf("test09 done\n");
}

void test10()
{
    // 00
    char or_dst[6] = "hello\0";
    char or_src[8] = "1234567\0";
    char ft_dst[6] = "hello\0";
    char ft_src[8] = "1234567\0";

	size_t or_r = strlcpy(or_dst, or_src, sizeof(or_dst));
	size_t ft_r = ft_strlcpy(ft_dst, ft_src, sizeof(ft_dst));

    for (int i = 0; i < 6;i++)
    {
        assert(or_dst[i]==ft_dst[i]);
        //assert(or_dst[i]==ft_dst[i]);
    }

    // 01
    char or_dst01[6] = "hello\0";
    char or_src01[2] = "1";
    char ft_dst01[6] = "hello\0";
    char ft_src01[2] = "1";

	size_t or_r01 = strlcpy(or_dst01, or_src01, sizeof(or_dst01));
	size_t ft_r01 = ft_strlcpy(ft_dst01, ft_src01, sizeof(ft_dst01));

    printf("or %s %lu\n", or_dst01, or_r01);
    printf("ft %s %lu\n", ft_dst01, ft_r01);

    for (int i = 0; i < 6;i++)
    {
        assert(or_dst01[i]==ft_dst01[i]);
    }

    // 02
    char or_dst02[6] = "hello\0";
    char or_src02[8] = "123\0abc\0";
    char ft_dst02[6] = "hello\0";
    char ft_src02[8] = "123\0abc\0";

	size_t or_r02 = strlcpy   (or_dst02, or_src02, sizeof(or_dst02));
	size_t ft_r02 = ft_strlcpy(ft_dst02, ft_src02, sizeof(ft_dst02));

    printf("or_dst:%s %lu\n", or_dst02, or_r02);
    printf("ft_dst:%s %lu\n", ft_dst02, ft_r02);

    for (int i = 0; i < 6;i++)
    {
        //printf("%c %c\n",or_dst02[i],ft_dst02[i]);
        assert(or_dst02[i]==ft_dst02[i]);
        //assert(or_dst[i]==ft_dst[i]);
    }

    printf("test10 done\n");
}

int main ()
{
    printf("---+ testを開始します +---\n");
    test00();//isalpha
    test01();//isdigit
    test02();//isalnum
    test03();//isascii
    test04();//isprint
    test05();//strlen
    test06();//memset
    test07();//bzero
    test08();//memcpy
    test09();//memmove
    test10();//strlcpy
    return (0);
}