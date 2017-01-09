

// acm.timus.ru 1125. Hopscotch

#include <cstdio>

static const int N = 50;

struct pt{ int x,y;};

static const char COLOR[2] = { 'W', 'B' };

static const pt PF[ 52 ] = 
{
    {3,  4},  {4,   3}, {5,  12}, {6,   8}, {7,  24}, {8,   6}, {8, 15}, {9, 12}, {9, 40}, 
    {10, 24}, {12,  5}, {12,  9}, {12, 16}, {12, 35}, {14, 48}, {15, 8}, {15, 20}, 
    {15, 36}, {16, 12}, {16, 30}, {18, 24}, {20, 15}, {20, 21}, {20, 48}, {21, 20}, 
    {21, 28}, {24,  7}, {24, 10}, {24, 18}, {24, 32}, {24, 45}, {27, 36}, {28, 21},
    {28, 45}, {30, 16}, {30, 40}, {32, 24}, {33, 44}, {35, 12}, 
    {36, 15}, {36, 27}, {36, 48}, {40,  9}, {40, 30}, {40, 42}, {42, 40}, 
    {44, 33}, {45, 24}, {45, 28}, {48, 14}, {48, 20}, {48, 36}
};

char in[ 65536 ];

bool s[ N ][ N ] ;
bool d[ N ][ N ] ;
int n, m;
char const* o;
char * w;

void reverse(int x, int y)
{
    // reverse x-row
    for(int i = 0; i != m; ++i)
        s[x][i] ^= true;
    
    // reverse y-column
    for(int i = 0; i != n; ++i)
        s[i][y] ^= true;
    
    // reverse (x,y) cell
    s[ x ][ y ] ^= true;
    
    
    //reverse others
    for(int i = 0; i != 52; ++i)
    {
        
        int r = x + PF[ i ].x;
        int c = y + PF[ i ].y;
        
        if (r < n && c < m)
            s[r][c] ^= true;
        
        r = x + PF[i].x ;
        c = y - PF[i].y ;
        
        if (r < n && c >= 0)
            s[r][c] ^= true;
        
        r = x - PF[i].x;
        c = y + PF[i].y;
        
        if (r >= 0 && c < m)
            s[r][c] ^= true;
        
        r = x - PF[i].x;
        c = y - PF[i].y;
        
        if (r >= 0 && c >= 0)
            s[r][c] ^= true;
    }
}

bool readBool()
{
    while(*o && *o <= 32)++o;
    while(*o >= '0' && *o <='9') ++o;
    
    return o[-1] & 1;
}

int readInt()
{
    int u = 0;
    while(*o && *o <= 32)++o;
    while(*o >= '0' && *o <= '9') u = (u << 3) + (u << 1) + (*o++ - '0');
    return u;
}

int solve()
{
 
    o = in;
    w = in;
    
    in[fread(in,1,sizeof(in)-4,stdin)]  = '\0';
    
    n = readInt();
    m = readInt();
    while(*o++ != '\n'); // skip Line break
    
    for(int i= 0; i != n; ++i)
    {
        for(int j = 0; j != m; ++j)
        {
            s[i][j] = ( 'B' == *o++ ) ; // black true, white - false;
        }
        while(*o++ != '\n');//skip Line break
    }
    
    for(int x = 0; x < n; ++x)
    {
        for(int y = 0; y < m; ++y)
        {
            if (readBool())
                reverse( x, y );
        }
    }
    
    //print s[][]
    for(int i = 0; i != n; ++i)
    {
        for(int j = 0; j != m; ++j)
            *w++ = COLOR[s[i][j]];
        *w++ = '\n';
    }
    
    fwrite(in,1,w-in,stdout);
    return 0;
}

int main()
{
    
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w",stdout);
#endif 

    solve();
    
    return 0;
}
