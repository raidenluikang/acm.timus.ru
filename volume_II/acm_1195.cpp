

// 1195. Ouths and Crosses

#include <cstdio>

static const int PLAYER[2] = {'X', 'O'};

int s[ 9 ];

int readData()
{
    int l = 0;
    int c;
    for(int i = 0; i != 3; ++i)
    {
        for(int j= 0; j != 3; ++j)
        {
            c = fgetc(stdin);
            
            s[l++] = c;
        }
        
        while( i < 2 && fgetc(stdin) != '\n');
    }
    return 0;
}

bool winPlayer(const int a[ 9 ], int player)
{
    // 0 1 2
    // 3 4 5
    // 6 7 8
    
    //1. horizontal
    if (a[0] == player && a[1] == player && a[2] == player)
        return true;
    if (a[3] == player && a[4] == player && a[5] == player)
        return true;
    if (a[6] == player && a[7] == player && a[8] == player)
        return true;
    
    //2. vertical
    if (a[0] == player && a[3] == player && a[6] == player)
        return true;
    if (a[1] == player && a[4] == player && a[7] == player)
        return true;
    if (a[2] == player && a[5] == player && a[8] == player)
        return true;
    
    //3. dioganals
    if (a[0] == player && a[4] == player && a[8] == player)
        return true;
    
    if (a[2] == player && a[4] == player && a[6] == player)
        return true;
    
    return false;
}

int print_char(int c, int level)
{
    while(level > 0)
    {
        putc(' ', stdout);
        putc(' ', stdout);
        --level;
    }
    putc(c, stdout);
    return 0;
}
int print_s(const int a[9], int level)
{
    print_char(a[0], level); putc(a[1], stdout);putc(a[2], stdout);
    putc('\n', stdout);
    print_char(a[3], level); putc(a[4], stdout);putc(a[5], stdout);
    putc('\n', stdout);
    print_char(a[6], level); putc(a[7], stdout); putc(a[8], stdout);
    putc('\n', stdout);
}
int whoWin(int player, int level )
{
    int win = 0;
    int lost = 0;
    int draw = 0;
    int anemy = player == 'X' ? 'O' : 'X';
    int t;
    
    if ( winPlayer( s,  player  ) )
        return player;
    
    if ( winPlayer(s, anemy ) )
        return anemy;
    
    for(int i = 0 ; i != 9; ++i)
    {
        if (s[i] == '#')
        {
            s[i] = player;
            
            t = whoWin(anemy, level + 1);
            
            if (t == anemy)
                ++lost;
            else 
            if (t == player)
                ++win;
            else 
                draw++;
            
            s[i] = '#';
        }
    }
   
    if (win)
        return player;
    
    if (draw)
        return 0;
    
    if (lost)
        return anemy;
    
    return 0;//draw
}

int solve()
{
    readData();
    
    int w = whoWin('X', 0);
    if (w == 'X')
        puts("Crosses win");
    else if (w == 'O')
        puts("Ouths win");
    else 
        puts("Draw");
    return 0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
    solve();
    
    return 0;
}
