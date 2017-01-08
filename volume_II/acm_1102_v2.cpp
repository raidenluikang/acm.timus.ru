// 1102. Strange Dialog

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool check(const char* & s) // read until '\n'
{
    while(*s != '\n' )
    {
        if (memcmp(s, "puton",5) == 0)
            s += 5;
        else if (memcmp(s,"one",3) == 0)
            s += 3;
        else if (memcmp(s,"outputone",9)==0)
            s += 9;
        else if (memcmp(s,"outputon",8) == 0)
            s += 8;
        else if (memcmp(s,"output",6) == 0)
            s += 6;
        else if (memcmp(s,"out",3) == 0)
            s += 3;
        else if (memcmp(s,"inputone",8) == 0)
            s += 8;
        else if (memcmp(s,"inputon",7) == 0)
            s += 7;
        else if (memcmp(s,"input",5) == 0)
            s += 5;
        else if (memcmp(s,"in",2) == 0)
            s+=2;
        else
            return false;
    }
    return true;
}
//1. in  
//2. input
//3. inputon 
//4. inputone

//1. out
//2. output
//3. outputon
//4. outputone

//1. puton
//2. one

char in[10000000 + 512];
int n,i;
char const* o;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
    in[fread(in,1,sizeof(in)-4,stdin)] = '\n';
    n= 0;
    o = in;
    while(*o == ' ' || *o == '\t')
        ++o;
    while(*o >='0' && *o <='9') n = (n << 3) + (n << 1) + (*o++ - '0');
    
    //skip '\n'
     while( *o != '\n')++o;
     ++o;
     
     for(i = 0; i != n; ++i)
     {
         if ( check( o ) )
         {
             puts("YES");
         }
         else
         {
             puts("NO");
             
             //skip until '\n';
             while(*o != '\n')++o;
         }
         ++o;
     }
    
    return 0;
}
