
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
	char or_buf[] = "ABCDEFGH\0";
	char ft_buf[] = "ABCDEFGH\0";
	//bufの先頭から3バイト進めた位置にbufの先頭から3バイトコピー
    // srcがdstよりも前
	memmove(or_buf+2,or_buf,5);
	ft_memmove(ft_buf+2,ft_buf,5);
    printf("or_buf %s\n",or_buf);
    printf("ft_buf %s\n",ft_buf);
    for (int i = 0;i < 9;i++)
        assert(or_buf[i]==ft_buf[i]);
	//printf("コピー後のbuf文字列→%s\n",buf);
	char or_buf01[] = "ABCDEFGH\0";
	char ft_buf01[] = "ABCDEFGH\0";
    // srcがdstよりも後
	memmove(   or_buf01,or_buf01+3,5);
	ft_memmove(ft_buf01,ft_buf01+3,5);
    printf("or_buf01 %s\n",or_buf01);
    printf("ft_buf01 %s\n",ft_buf01);
    //for (int i = 0;i < 10;i++)
    //    assert(or_buf01[i]==ft_buf01[i]);
    printf("test09 done\n");
}



#include <unistd.h>

void	ft_putchar(char a)
{
	write(1, &a, 1);
}

void test10_0(char *a, size_t size)
{
	for (size_t i = 0;i < size;i++)
	{
		if (a[i])
		{
			ft_putchar(a[i]);
		}
		else
		{
			ft_putchar('*');
		}
		ft_putchar(',');
	}
	ft_putchar('\n');
}

// strlcpy
void test10()
{
//test function
	char or_a[6] = "hello\0";
	char or_c[6] = "hello\0";

	int or_ar = strlcpy(or_a,"abc",3);
	int or_cr = strlcpy(or_c,"a"  ,1);
	test10_0(or_a, 6);
	test10_0(or_c, 6);

	char ft_a[6] = "hello\0";
	char ft_c[6] = "hello\0";
	int ft_ar = ft_strlcpy(ft_a,"abc",3);
	int ft_cr = ft_strlcpy(ft_c,"a"  ,1);
	test10_0(ft_a, 6);
	test10_0(ft_c, 6);
    for (int i = 0;i < 6;i++)
    {
        assert(or_a[i] == ft_a[i]);
        assert(or_c[i] == ft_c[i]);
    }
    assert(or_ar==ft_ar);
    assert(or_cr==ft_cr);
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