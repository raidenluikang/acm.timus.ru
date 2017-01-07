


#include <cstdio>
#include <cmath>

typedef unsigned int uint;

uint fact[20] = {};
uint f[20][20] = {};
uint a[20] = {};

#if 0
function g(x,k:longint):comp;
var i:longint; q:comp;
begin
    q:=1;
    for i:=1 to k do q:=q*i;
        g:=q*x;
end;
var
f:array[0..20,0..20] of longint;
a:array[0..20] of comp;
    i,j,n,k:longint;
begin
for i:=0 to 10 do begin f[i,1]:=1; f[i,i]:=1; end;
f[0,1]:=0;
for i:=1 to 10 do
    for j:=2 to i-1 do f[i,j]:=f[i-1,j-1]+f[i-1,j]*j;
for i:=2 to 10 do
    for j:=1 to 10 do a[i]:=a[i]+g(f[i,j],j);
readln(n);
    while n>0 do
        begin
        writeln(a[n]:0:0);
        readln(n);
        end;
end.
#endif 

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif 
    fact[0] = 1;
    
    for(int i= 1; i <= 12; ++i)
        fact[i] = fact[i-1] * i;
    
    for(int i = 0; i <= 12; ++i)
    {
       f[i][1] = 1;
       f[i][i] = 1;
    }  
    
    f[0][1] =0;
    
    for(int i = 1; i <= 12; ++i)
        for(int j = 2; j < i; ++j) 
            f[ i ][ j ] = f[i-1][j-1] + f[i-1][j] * j;
    
    for(int i = 2; i <= 12; ++i)
        for(int j = 1; j <= 12; ++j)
            a[ i ] += fact[ j ] * f[ i ][ j ];
    
    int n  = 0;
    while(1==scanf("%d",&n))
    {
        if (n < 0)break;
        printf("%u\n",a[n]);
    }
    return 0;
}
