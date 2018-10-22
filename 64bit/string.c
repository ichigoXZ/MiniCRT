char* itoa(long n, char* str, long radix)
{
	char digit[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char* p = str;
	char* head = str;

	if(!p || radix < 2 || radix > 36)
		return p;
	if(radix != 10 && n <0)
		return p;
	if(n == 0)
	{
		*p++ = '0';	// *,++优先级相同，结合方向右到左
		*p = 0;   // 相当于用'\0'结束
		return p;
	}
	if(radix == 10 && n < 0)
	{
		*p++ = '-';
		n = -n;
	}

	while(n)
	{
		*p++ = digit[n % radix];
		n /= radix;
	}
	*p = 0;
	// reverse
	for(--p; head < p; ++head, --p)
	{
		char temp = *head;
		*head = *p;
		*p = temp;
	}
	return str;
}

long strcmp(const char* src, const char* dst)
{
	long ret = 0;
	unsigned char* p1 = (unsigned char*)src;
	unsigned char* p2 = (unsigned char*)dst;
	while(!(ret = *p1 - *p2) && *p2)
		++p1, ++p2;

	if(ret < 0)
		ret = -1;
	else if(ret > 0)
		return 1;
	return ret;
}

char* strcpy(char* dst, const char* src)
{
	char* ret = dst;
	while(*src)
		*dst++ = *src++;
	*dst = '\0';
	return ret;
}

unsigned long strlen(const char* str)
{
	long cnt = 0;
	if(!str)
		return 0;
	for(; *str != '\0'; ++str)
		++cnt;
	return cnt;
}
