

// acm.timus.ru 1122. Game

#include <cstdio>
#include <cstring>

static const int BIT_CNT[16] = 
{
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4
};

bool s[ 4  ][ 4 ];
bool p[ 8  ][ 8 ];
bool t[ 3  ][ 3  ];

unsigned char dp[ 65536 ];

// 0 <= n < 256
int bits(int n){
    return BIT_CNT[n >> 4] + BIT_CNT[n & 15];
}

int readData()
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
    
    return 0;
}

int writeAns(int ans)
{

    if (ans == 100)
        puts("Impossible");
    else
        printf("%d\n",ans);
    return 0;
}

int convertInt()
{
    int code = 0;
    
    for(int i = 0; i != 16; ++i)  
    {
        int x = 2 + ( i >> 2 );
        int y = 2 + ( i & 3 );// +2 - is offset
        code = (code << 1) + (int)p[x][y];
    }
    return code;
}

int flip(int x, int y)
{
    p[x-1][y-1] ^= t[0][0];
    p[x-1][y  ] ^= t[0][1];
    p[x-1][y+1] ^= t[0][2];
    
    p[x][y-1] ^= t[1][0];
    p[x][y  ] ^= t[1][1];
    p[x][y+1] ^= t[1][2];
    
    p[x+1][y-1] ^= t[2][0];
    p[x+1][y  ] ^= t[2][1];
    p[x+1][y+1] ^= t[2][2];
    
    return 0;
}

int solve()
{
    readData();
    
    int ans = 100;
    
    memset(dp, 0xFF, sizeof(dp));
    
    for(int i= 0; i< 256; ++i)
    {
        int n_i = bits( i ); 
        int code;
        
        //copy low
        for(int x = 0; x != 4; ++x)
            for(int y = 0; y != 4; ++y)
                p[x+2][y+2] = s[x][y] && (x < 2);
        
        
        
        for(int h = 0; h != 16; ++h)
        {
            if (i & (1 << h) )
            {
                int x = 2 + ( h >> 2 );
                int y = 2 + ( h &  3 );
                
                flip(x, y);
            }
        }
        
        code = convertInt(); // convert p[][] to int
       
        if (dp[code] > n_i)
            dp[ code ] = n_i;// +1 offset
    }

    
    for(int i = 0; i < 256; ++i)
    {
        int n_i = bits( i );
        int code;
        
        for(int x = 0; x != 4; ++x)
            for(int y = 0; y != 4; ++y)
                p[x+2][y+2] = s[x][y] && (x >= 2);
        
        for(int h = 0; h != 16; ++h)
        {
            if ( ( i << 8 ) & (1 << h))
            {
                int x = 2 + (h >> 2);
                int y = 2 + (h & 3 );
                
                flip(x, y);
            }
        }
        
        code = convertInt();
        
        // x XOR code == 0 --> x = code
        // x XOR code == 65535 --> x = 65535 XOR code
        int lx = dp[code] + n_i;
        int ly = dp[code ^ 0xFFFF] + n_i;
        if (lx < ans)
            ans = lx;
        if (ly < ans)
            ans = ly;
    }
    
    writeAns(ans);
    
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
