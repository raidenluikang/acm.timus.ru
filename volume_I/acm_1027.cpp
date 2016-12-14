

// 	ACM.TIMUS.RU 1027 D++.
#include <cstdio>

typedef const char* pchar;

bool correct(pchar s, unsigned n)
{
	//we assume that  last symbols is not ')' and '(' and '*)' and '*('.
	unsigned i = 0, o;
	while (i < n )
	{
		while (i < n && s[i] != '(' && s[i] != ')')
		   ++i;
		
		if (i == n)return true;
		
		if (s[i] == ')')
		   return false;
		
		if (s[i+1] == '*') // comment
		{
			i+= 2; // skip '(' and '*'.
			
			while ( i < n && !(s[i] == '*' && s[i+1] == ')'))
			  ++i;
			
			if (i == n)return false;
			
			i+=2;
			
			continue;
		}
		
		//arithmetic expression
		i++; // skip '('.
		o = 1; //  o - number of opened brackets.
		while( i < n && o != 0 )
		{
			switch(s[i])
			{
				case '*': case '=': case '+': case '-': case '/': 
				case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
				case '\n': break;
				case '(' : 
				{
					if (s[i+1] == '*')//comment
					{
						i += 2; // skip '(' and '*'.
					    while ( i < n && !(s[i] == '*' && s[i+1] == ')'))
					         ++i;
					         
					    if (i == n)return false;
					    
					    i += 1;
					}
					else
					{
						++o;
					}
				}
				break;
				
				case ')': --o; break;
				
				default: return false;
			}
			++i;
		} 
		
		if (o != 0)
		  return false;  
	}
	return true;
}
int solve()
{
	char s[16384] ;
	unsigned n = 0;
	for(int c = std::getc(stdin); c != EOF; c = std::getc(stdin))
	   s[n++] = c;
	s[n++] = '0';
	s[n++] = '1';
	s[n++] = '2';
	s[n] = '\0';
	if (correct(s,  n) )
	{
		puts("YES");
	}
	else
	{
		puts("NO");
	}
	return 0;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r", stdin);
    freopen("output.txt","w",stdout);
#endif

    solve();
    
    return 0;
}  
