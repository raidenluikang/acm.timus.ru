// acm.timus.ru 1102. Strange Dialog

#include <cstdio>
#include <cstring>

void judge_assert(bool b)
{
    if (!b)
        printf("%d\n",1/b);
}

static const unsigned char
               //a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
   code[ 26 ] = {7, 7, 7, 7, 0, 7, 7, 7, 1, 7, 7, 7, 7, 2, 3, 4, 7, 7, 7, 5, 6, 7, 7, 7, 7, 7 };

#if 1
static const unsigned char next[17][26] = 
{
{ 15, 15, 15, 15, 15, 15, 15, 15, 1, 15, 15, 15, 15, 15, 2, 3, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  },
{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 4, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  },
{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 15, 15, 15, 15, 15, 15, 9, 15, 15, 15, 15, 15,  },
{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 12, 15, 15, 15, 15, 15,  },
{ 15, 15, 15, 15, 15, 15, 15, 15, 1, 15, 15, 15, 15, 15, 2, 5, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  },
{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 6, 15, 15, 15, 15, 15,  },
{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 15, 15, 15, 15, 15, 15,  },
{ 15, 15, 15, 15, 15, 15, 15, 15, 1, 15, 15, 15, 15, 15, 8, 3, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  },
{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 10, 15, 15, 15, 15, 15, 15, 9, 15, 15, 15, 15, 15,  },
{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 11, 15, 15, 15, 15, 15, 15,  },
{ 15, 15, 15, 15, 0, 15, 15, 15, 1, 15, 15, 15, 15, 15, 2, 3, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  },
{ 15, 15, 15, 15, 15, 15, 15, 15, 1, 15, 15, 15, 15, 15, 2, 5, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  },
{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 13, 15, 15, 15, 15, 15, 15,  },
{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  },
{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  },
{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  },
{ 15, 15, 15, 15, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  }

};
#endif 
#if 0
static const unsigned char next[17][ 8 ] =  
{
   // a  b  c  d  e  f  g  h i j k l m n o p q r s t u v w x y z
    //e   i   n   o   p   t   u   other
    {15, 1,  15, 2,  3,  15, 15, 15,}, //0
    {15, 15, 4,  15, 15, 15, 15, 15}, //1
    {15, 15, 16, 15, 15, 15, 9,  15}, //2
    {15, 15, 15, 15, 15, 15, 12, 15}, //3
    {15, 1,  15, 2,  5,  15, 15, 15},  //4
    {15, 15, 15, 15, 15, 15, 6,  15}, //5
    {15, 15, 15, 15, 15, 7,  15, 15}, //6
    {15, 1 , 15, 8,  3,  15, 15, 15}, //7
    {15, 15, 10, 15, 15, 15, 9,  15}, //8
    {15, 15, 15, 15, 15, 11, 15, 15}, //9
    {0,  1,  15, 2,  3,  15, 15, 15},  //10
    {15, 1,  15, 2,  5,  15, 15, 15},// 11
    {15, 15, 15, 15, 15, 13, 15, 15}, // 12
    {15, 15, 15, 14, 15, 15, 15, 15}, // 13
    {15, 15, 0,  15, 15, 15, 15, 15}, // 14
    {15, 15, 15, 15, 15, 15, 15, 15}, // 15
    {0,  15, 15, 15, 15, 15, 15, 15}  // 16
};
	
#endif 
static const bool answer [ 17] = 
{
    true, false, false, false, true, false, false, true, false , false, true, true, false, false, false, false, false
};

char in [ 8192 ];
char out[ 8192  ];

const char* o ;
char* w ;

unsigned n, m, e, d;

char nextChar()
{
    if (o  < in + m ||  e)
        return *o++ ;
    
    m = fread(in, 1, sizeof(in) - 4, stdin);
    e = m < sizeof(in) - 4;// e - true - end file
    o = in;
    if (e)//end
        in[ m ] = '\n', in[m+1] = '\0';
    return *o++ ;
}

void writeYes()
{
    *w++ = 'Y';*w++ ='E';*w++ = 'S'; *w++ = '\n';
}

void writeNo()
{
    *w++ = 'N'; *w++ = 'O'; *w++ = '\n';
}

void init()
{
    o = in;
    w = out;
    
    m = fread(in,1,sizeof(in)-4,stdin);
    e = m < sizeof(in) - 4;
    if ( e )
        in[ m ] = '\n', in[m+1] = '\0';
}
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r", stdin);
    freopen("output.txt","w",stdout);
#endif 
#if 0
    for(int i = 0; i < 17; ++i)
    {
        printf("{ ");
        for(int c = 'a'; c <= 'z'; ++c)
        {
            int j = c - 'a';
            int v = next[i][code[ j ]];
            
            printf("%d, ", v);
        }
        printf(" },\n");
    }
    return 0;
#endif     
    init();
    n = 0;
    char c;
    while((c = nextChar()) <= 32 && c != '\0');
    while(c >='0' && c <='9') n = n *10 + c - '0', c = nextChar();
    
    while ( c != '\n' && c != '\0')
        c = nextChar();
    
    //c == '\n'
    for(int i = 0; i != n; ++i)
    {
        unsigned char s = 0;
        while ( s != 15 && (c = nextChar()) != '\n')
            s = next[ s ][   c - 'a'   ];
        
        if (answer[s])
            writeYes();
        else
            writeNo();
        
        while (c != '\n' )
            c = nextChar();
    }
 
    
    if (w != out)
        fwrite(out, 1, w - out, stdout);
    return 0;
    
}
