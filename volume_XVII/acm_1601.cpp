 // 1601. AntiCAPS


#include <cstdio>


bool is_letter(char c)
{
    return (c >='A' && c <='Z');
}

char to_lower(char c)
{
    return c + 32;
}

char in[16384];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w", stdout);
#endif 
    int i , s;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    
    for( i = 0, s = 1; in[i] != 0; ++i)
    {
        if (is_letter(in[ i ] ) )
        {
            if (s == 1) // start a new sentence
                ;
            else
                in[i] += 32;
            s = 0;
        }
        else if (in[i] == '?' || in[i] == '!' || in[i] == '.' )
        {
            s = 1;//next letter will as uppercase
        }
        else 
        {
            //nothing do with other symbols
        }
    }
    fwrite(in,1,i,stdout);
}
