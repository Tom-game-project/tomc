
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
	char buf[] = "ABCDEFGHIJK";
	//先頭から2バイト進めた位置に「１」を3バイト書き込む
	assert(memset(buf+2,'1',3)==ft_memset(buf+2,'1',3));
	printf("buf文字列→%s\n",buf);
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

}

// strlcpy
void test10()
{
	// char a[6] = "hello\0";
	// char c[6] = "hello\0";

	// int ar = strlcpy(a,"abc",3);
	// int cr = strlcpy(c,"a"  ,1);
	// test(a, 6);
	// test(c, 6);
	// printf("ar %d\n",ar);
	// printf("cr %d\n",cr);

	// char ft_a[6] = "hello\0";
	// char ft_c[6] = "hello\0";
	// int ft_ar = strlcpy(ft_a,"abc",3);
	// int ft_cr = strlcpy(ft_c,"a"  ,1);
	// test(ft_a, 6);
	// test(ft_c, 6);
	// printf("ar %d\n",ft_ar);
	// printf("cr %d\n",ft_cr);	
    //return (0);
}

int main ()
{
    test00();
    test01();
    test02();
    test03();
    test04();
    test05();
    test06();
    test07();
    test08();
    return (0);
}