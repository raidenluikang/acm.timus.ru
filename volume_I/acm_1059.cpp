

#include <cstdio>
#include <cstring>

 
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r", stdin);
    freopen("output.txt","w",stdout);
#endif
    char s[16384] = {};
    char* o = s;
    int n;
    scanf("%d",&n);
    // n = 1 :   0*x^1 + 1*x^0  --> 0 x * 1 +
    // n = 2 :   0*x^2 + 1*x^1 + 2 -->  0 x * 1 + x * 2 +
    // n = 3 :   0*x^3 + 1*x^2 + 2*x^1 + 3 = f(2)*x+3 = 0 x * 1 + x * 2 + x * 3 + 
    // 
    
    *o ++ = '0';
    *o ++ = '\n';
    
    for(int i =1, v, vn, wn; i<=n;++i)
    {
		// 'x'  '*'  i  '+'
		*o++ = 'X';
		*o++ = '\n';
		*o++ = '*';
		*o++ = '\n';
		v = i;
		vn = 0; do vn++ ; while(v/=10);
		wn = vn; v = i;
		while(vn-->0)o[vn] = v%10 + '0', v/=10;
		o += wn;
		*o ++ = '\n';
		*o ++ = '+';
		*o ++ ='\n';
	}
	--o;
	*o = '\0';
	puts(s);
	return 0;   
}  
