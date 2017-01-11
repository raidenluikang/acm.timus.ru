


#include <cstdio>

static const unsigned N = 250 * 1000;

char const* o;
unsigned dn;
unsigned m;

unsigned d[ N/2 + 4];


char in[1 << 18];


void load()
{
    o = in;
    m = fread(in,1,sizeof(in)-4, stdin);
    in[m] = 0;
    in[m+1] =1;
}

unsigned readIntImpl()
{
    unsigned u = *o++ - '0';
    while(*o >='0') u = (u << 3) + (u << 1) + (*o++ -'0');
    return ++o, u;
}

unsigned readInt()
{
    unsigned u = readIntImpl();
    if ( *o == 0 )
    {
        load();
    }
    else if (*o == 1)
    {
        load();
        while( *o >= '0' && *o <= '9') 
            u = (u << 3) + (u << 1) + ( *o++ - '0' );
        ++o;
    }
    return u;
}

void  pop()
{
    unsigned l = 1, r, t;
   
    d[1] = d[ dn-- ];
    
    while (l + l <  dn)
    {
        r = l + l;
        if (d[r] < d[r+1])r++;
        
        if (d[l] > d[r])
            break;
        t = d[l];
        d[l] = d[r];
        d[r] = t;
        
        l = r;
    }
    
    r = l + l;
    if (r <= dn && d[l] < d[r])
    {
        t = d[l];
        d[l] = d[r];
        d[r] = t;
        
    }
        
}

unsigned top()
{
    return d[ 1 ];
}

void push(unsigned x)
{
    unsigned l = ++dn ;
    unsigned t;
    while ( l > 1 && x > d[l >> 1])
    {
        d[ l ] = d[ l >> 1];
        l >>= 1;
    }
    d[l] = x;
}

int main()
{
    
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    unsigned n,a , n2;
    bool odd;
    
    load();
    n = readInt();
    //scanf("%d",&n);
    
    odd  = n & 1;
    
    n2 = n / 2 + 1;
    
    dn = 0; 
    
    for(int i = 0; i < n2; ++i)
    {
        //scanf("%u",&a);
        a = readInt();
                push( a );
    }
    
    for(int i = n2; i < n; ++i)
    {
        a = readInt();
        if (a < top())
        {
            push(a);
            pop();
        }
    }
    
    if (odd)
    {
        printf("%u\n",  top() );
    }
    else
    {
        a =  top();
       
        pop();
        
        if ( ( a & 1 ) ^ ( top() & 1 ) )
            printf("%u.5\n", (a  +  top()  )/2  );
        else
            printf("%u\n", (a + top() )/ 2);
    }
    return 0;
}
