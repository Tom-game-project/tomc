
#include "libft.h"

#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

// part 1

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

// strlcpy
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

// strlcat
void test11()
{
    char or_dst00[6] = "hello\0";
    char or_src00[6] = "world\0";
    int or_return00 = strlcat(or_dst00,or_src00,sizeof(or_dst00));
    printf("result a:%s :%d\n",or_dst00,or_return00);

    char ft_dst00[6] = "hello\0";
    char ft_src00[6] = "world\0";
    int ft_return00 = ft_strlcat(ft_dst00,ft_src00,sizeof(ft_dst00));
    printf("result a:%s :%d\n",ft_dst00,ft_return00);

	for (int i = 0;i < 6;i++)
    {
        assert(or_dst00[i]==ft_dst00[i]);
    }
    assert(or_return00 == ft_return00);

    char or_dst01[11] = "hello\0";
    char or_src01[6] = "world\0";
    int or_return01 = strlcat(or_dst01,or_src01,sizeof(or_dst01));
    printf("result c:%s :%d\n",or_dst01,or_return01);

    char ft_dst01[11] = "hello\0";
    char ft_src01[6] = "world\0";
    int ft_return01 = ft_strlcat(ft_dst01,ft_src01,sizeof(ft_dst01));

	for (int i = 0;i < 11;i++)
    {
        assert(or_dst01[i]==ft_dst01[i]);
    }
    assert(or_return01== ft_return01);
    printf("result c:%s :%d\n",ft_dst01,ft_return01);
    printf("test11 done\n");
}

// toupper
void test12()
{
    for (int c = 'a';c < 'z';c++){
        assert(ft_toupper(c)==toupper(c));
    }
    for (int c = 'A';c < 'Z';c++){
        assert(ft_toupper(c)==toupper(c));
    }
    printf("test12 done\n");
}

// tolower
void test13()
{

    for (int c = 'a';c < 'z';c++){
        assert(ft_tolower(c)==tolower(c));
    }
    for (int c = 'A';c < 'Z';c++){
        assert(ft_tolower(c)==tolower(c));
    }
    printf("test13 done\n");
}

// strchr
void test14()
{
    char *a = "hello world";
    char *b = "hello";
    char c[] = "\0aaa";
    assert(ft_strchr(a,'o')==strchr(a,'o'));
    assert(ft_strchr(b,'w')==strchr(b,'w'));
    assert(ft_strchr(c,'\0')==strchr(c,'\0'));
    printf("test14 done\n");
}

// strrchr
void test15(){
    char *a = "hello world";
    char *b = "hello";
    char c[] = "\0aaa";
    char d[] = "\0aaadd\0ddd\0";
    assert(ft_strrchr(a,'o')==strrchr(a,'o'));
    assert(ft_strrchr(b,'w')==strrchr(b,'w'));
    assert(ft_strrchr(c,'\0')==strrchr(c,'\0'));
    assert(ft_strrchr(d,'\0')==strrchr(d,'\0'));
    printf("test15 done\n");
}

// strlcmp
void test16()
{
    char *a0 = "hello world";
    char *a1 = "hellO world";
    printf("diff %d %d\n",strncmp(a0,a1,5),ft_strncmp(a0,a1,5));
    assert(strncmp(a0,a1,5)==ft_strncmp(a0,a1,5));
    char *b0 = "hello worldw";
    char *b1 = "hello world";
    printf("diff %d\n",strncmp(b0,b1,20));
    assert(strncmp(b0,b1,20)==ft_strncmp(b0,b1,20));
    char c0[] = "hello\0worlD\0";
    char c1[] = "hello\0world\0";
    printf("diff %d\n",strncmp(c0,c1,10));
    assert(strncmp(c0,c1,10)==ft_strncmp(c0,c1,10));
    printf("test16 done\n");
}

// memchr
void test17()
{
    char *a = "hello world";
    char *b = "hello";
    char c[] = "\0aaa";
    char d[] = "\0aaadd\0ddd\0";
    assert(ft_memchr(a,'o',11)== memchr(a,'o',11));
    assert(ft_memchr(b,'w',5)== memchr(b,'w',5));
    assert(ft_memchr(c,'\0',sizeof(c))==memchr(c,'\0',sizeof(c)));
    assert(ft_memchr(d,'\0',sizeof(d))==memchr(d,'\0',sizeof(d)));
    printf("test17 done\n");
}

// memcmp
void test18()
{
    char *a0 = "hello world";
    char *a1 = "hellO world";
    printf("diff %d %d\n",ft_memcmp(a0,a1,5),memcmp(a0,a1,5));
    assert(ft_memcmp(a0,a1,5)==memcmp(a0,a1,5));
    char *b0 = "hello worldw";
    char *b1 = "hello world";
    printf("diff %d\n",ft_memcmp(b0,b1,20));
    assert(ft_memcmp(b0,b1,20)==memcmp(b0,b1,20));
    char c0[] = "hello\0worlD\0";
    char c1[] = "hello\0world\0";
    printf("diff %d\n",ft_memcmp(c0,c1,sizeof(c0)));
    assert(ft_memcmp(c0,c1,10)==memcmp(c0,c1,sizeof(c0)));
    printf("test18 done\n");
}

// strnstr
void test19()
{
    int *a = "hello world";
    int *b = "o ";
    printf("ft:%p\nor:%p\n",
    	ft_strnstr(a,b,10),
    	strnstr   (a,b,10)
    );
    assert(ft_strnstr(a,b,10)==strnstr(a,b,10));


    printf("ft:%p\nor:%p\n",
    	ft_strnstr(a,b,5),
    	strnstr   (a,b,5)
    );
    assert(ft_strnstr(a,b,5)==strnstr(a,b,5));
    printf("test19 done\n");
}

//atoi
void test20()
{
    char *a = "120"; //120
    char *b = "1982a11"; //1982
    char *c = "-235";// -235
    char *d = "-2 35";// -2
    char *e = "   \n	14";
    printf("%d %d\n",ft_atoi(a),atoi(a));
    printf("%d %d\n",ft_atoi(b),atoi(b));
    printf("%d %d\n",ft_atoi(c),atoi(c));
    printf("%d %d\n",ft_atoi(d),atoi(d));
    printf("%d %d\n",ft_atoi(e),atoi(e));
    assert(ft_atoi(a)==atoi(a));
    assert(ft_atoi(b)==atoi(b));
    assert(ft_atoi(c)==atoi(c));
    assert(ft_atoi(d)==atoi(d));
    assert(ft_atoi(e)==atoi(e));
}

// calloc
void test21()
{
	int *intbuf = ft_calloc(100, sizeof(int));
    for (int i = 0;i < 100;i++)
    {
        assert(intbuf[i] == 0);
    }
	char *charbuf = ft_calloc(100, sizeof(char));
    for (int i = 0;i < 100;i++)
    {
        assert(charbuf[i] == 0);
    }
    free(charbuf);
}

// strdup
void test22()
{
    // 引数にnull文字を入れるのはuserの義務
    char *a = "hello world";
    char *b = ft_strdup(a);
    printf("%s %s\n",a,b);
    free(b);
	for (int i = 0;i < 100000;i++)
	{
		char *c = "My name is Tom ! Happy 42 Life !";
		char *d = ft_strdup(c);
		//printf("%s %s\n",c,d);
		free(d);
	}
}

// part 2

void test23()
{
	char *a = "hello world";
	char *adst;
    char *aprd = "o w";

	adst = ft_substr(a,4,3);
    printf("%s\n",adst);
    assert(strcmp(adst,aprd) == 0);

	char *b = "hello world";
	char *bdst;
    char *bprd = " world";

	bdst = ft_substr(b,5,10);
    printf("%s\n", bdst);
    assert(strcmp(bdst, bprd) == 0);
    free(adst);
    free(bdst);
}

// strjoin
void test24()
{
	char *pred0 = "helloworld";
	char *pred1 = "hellohello";

    char *a = "hello";
    char *b = "world";
    char *dst0 = ft_strjoin(a, b);
    printf("result %s \n",dst0);
    assert(strcmp(dst0,pred0) == 0);
    free(dst0);
    char *dst1 = ft_strjoin(a, a);
    printf("result %s \n",dst1);
    assert(strcmp(dst1,pred1) == 0);
    free(dst1);
}

void test25()
{
	char *str0 = " 			 	  	hello  	";
	char *str1 = " 			 	  	hello";
	char *str2 = "hello 		 	 	 	 ";
    char *trimset = " 	";
    char *dst0 = ft_strtrim(str0, trimset);//malloc
    char *dst1 = ft_strtrim(str1, trimset);//malloc
    char *dst2 = ft_strtrim(str2, trimset);//malloc

	char *pred = "hello";
    printf("%s\n",dst0);
    printf("%s\n",dst1);
    printf("%s\n",dst2);
    assert(strcmp(dst0,pred) == 0);
    assert(strcmp(dst1,pred) == 0);
    assert(strcmp(dst2,pred) == 0);
    free(dst0);
    free(dst1);
    free(dst2);
    printf("test25 done\n");
}

void test26()
{
	char *a = "hello,world,Tom,still,alive";
	char **dst;
    printf("len %d\n",ft_strlen(a));
	dst = ft_split(a,',');//malloc 

	while(*dst)
	{
		printf("%s\n",*dst);
		dst++;
	}
    free(dst);
}

int main ()
{
    printf("---+ testを開始します +---\n");
    printf("part 1\n");
    test00();// isalpha
    test01();// isdigit
    test02();// isalnum
    test03();// isascii
    test04();// isprint
    test05();// strlen
    test06();// memset
    test07();// bzero
    test08();// memcpy
    test09();// memmove
    test10();// strlcpy
    test11();// strlcat
    test12();// toupper
    test13();// tolower
    test14();// strchr
    test15();// strrchr
    test16();// strncmp
    test17();// memchr
    test18();// memcmp
    test19();// strnstr
    test20();// atoi
    test21();// calloc
    test22();// strdup
    printf("part 1 OK\n");

    printf("part 2\n");
    test23();// substr
    test24();// strjoin
    test25();// ft_strtrim
    test26();// ft_split

    return (0);
}