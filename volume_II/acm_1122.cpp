

// acm.timus.ru 1122. Game

#include <cstdio>

static const int BIT_CNT[16] = 
{
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4
};

bool s[ 4  ][ 4 ];
bool p[ 12 ][ 12 ];
bool t[ 3  ][ 3  ];


int solve()
{
    for(int i = 0; i != 4; ++i)
    {
        for(int j= 0; j!=4;++j)
        {
            s[i][j] = getc(stdin) == 'B' ; // black - true, white - false
        }
        while(getc(stdin) != '\n');//skip '\n'
    }
    
    for(int i = 0; i != 3; ++i)
    {
        for(int j = 0; j != 3; ++j)
        {
            t[i][j] = getc(stdin) == '1'; // 1-turn , 0 - non turn
        }
        
        while ( i < 2 && getc(stdin) != '\n');
    }
    
    int ans = 100;
    for(int i = 0; i <  65536; ++i)
    {
        for(int x = 0; x != 4; ++x)
            for(int y = 0; y != 4; ++y)
                p[ 4 + x][ 4 + y ] = s[ x ][ y ];
        
        int l = BIT_CNT[i >> 12 ] + BIT_CNT[(i>>8)&15] + BIT_CNT[(i>>4)&15] + BIT_CNT[i&15];
        
        if (l >= ans)continue;
        
        for(int h = 0; h < 16; ++h)
        {
            if (i & (1 << h))
            {
                int x = 4 + ( h >> 2 ) ;
                int y = 4 + ( h  & 3 ) ;
                // t[3][3] : 
                //   0   1  2
                // 0 00 01 02
                // 1 10 11 12
                // 2 20 21 22
                
                //p[x][y] ^= t[1][1];
                p[x-1][y-1] ^= t[0][0];
                p[x-1][y] ^= t[0][1];
                p[x-1][y+1] ^= t[0][2];
                
                p[x][y-1] ^= t[1][0];
                p[x][y] ^= t[1][1];
                p[x][y+1] ^= t[1][2];
                
                p[x+1][y-1] ^= t[2][0];
                p[x+1][y]   ^= t[2][1];
                p[x+1][y+1] ^= t[2][2];
            }
        }
        
        bool b = true;
        bool o = p[4][4];
        
        for(int x = 4; x < 8; ++x)
            for(int y = 4; y < 8; ++y)
                b = b && p[x][y] == o;
    
        if (b )
            ans = l;
        
    }
    
    if (ans == 100)
        puts("Impossible");
    else
        printf("%d\n",ans);
    
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
