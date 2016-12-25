//0 8 1 2 1 1
// forward : 0
// backward: 8
// top     : 1
// right   : 2
// bottom  : 1
// left    : 1

// e2 --> e3 
// 5 e2 d2 d1 e1 e2 e3
// 1. e2 : cost = 1
// 2. d2 : cost = 1 
// 3. d1 : cost = 0
// 4. e1 : cost = 1
// 5. e2 : cost = 1
// 6. e3 : cost = 1
//acm.timus.ru 1016. Cube on the Walk
//
//   a b c d e f g h
// 8
// 7
// 6             ^ backward 
// 5             |
// 4     <--left | --> right
// 3             |
// 2             v
// 1             forward
//---------------------------------------

#include <cstdio> // fread/fwrite  printf scanf
#include <cstring> // memset, memcpy
#include <set>

struct box
{
    unsigned char sides[ 6 ];
};

enum Side
{
    s_forward  = 0,
    s_backward = 1,
    s_top      = 2,
    s_right    = 3,
    s_bottom   = 4,
    s_left     = 5
};

box rot_left(box const& x)
{
   box r;
   r.sides[ s_forward ] = x.sides[s_forward  ];
   r.sides[ s_backward] = x.sides[s_backward ];
   r.sides[ s_top     ] = x.sides[s_right    ];
   r.sides[ s_right   ] = x.sides[s_bottom   ];
   r.sides[ s_bottom  ] = x.sides[s_left     ];
   r.sides[ s_left    ] = x.sides[s_top      ];
   return r;
}
box rot_right(box const& x)
{
    box r;
    r.sides[s_forward] = x.sides[s_forward];
    r.sides[s_backward] = x.sides[s_backward];
    r.sides[s_top] = x.sides[s_left];
    r.sides[s_right] = x.sides[s_top];
    r.sides[s_bottom] = x.sides[s_right];
    r.sides[s_left] = x.sides[s_bottom];
    return r;
}

box rot_backward(box const& x)
{
    box r;
    r.sides[s_forward] = x.sides[s_bottom];
    r.sides[s_backward] = x.sides[s_top];
    r.sides[s_top] = x.sides[s_forward];
    r.sides[s_right] = x.sides[s_right];
    r.sides[s_bottom] = x.sides[s_backward];
    r.sides[s_left] = x.sides[s_left];
    return r;
}

box rot_forward(box const& x)
{
    box r;
    r.sides[s_forward] = x.sides[s_top];
    r.sides[s_backward] = x.sides[s_bottom];
    r.sides[s_top] = x.sides[s_backward];
    r.sides[s_right] = x.sides[s_right];
    r.sides[s_bottom] = x.sides[s_forward];
    r.sides[s_left] = x.sides[s_left];
    return r;
}


static const int DX[] = {1, 0, -1, 0};
static const int DY[] = {0, 1, 0, -1};

box rot_direction(box const& x, int direction)
{
    // direction 0 :  x -> x + 1   rot_right 
    // direction 1 :  y -> y + 1   rot_backward
    // direction 2 :  x -> x - 1   rot_left
    // direction 3 :  y -> y - 1   rot_forward
    typedef box (* rot_func)(const box&);

    static const rot_func r[ 4 ] = {rot_right, rot_backward, rot_left, rot_forward};

    return r[direction]( x );
}

int cell[ 8 ][ 8 ][ 6 ][ 6 ];

struct q_node
{
    box b;
    int x, y;
    int cost;// max value: 1000* 64 = 64 000 < 2^16

    int code()const
    {
        return (x << 0) | ( y << 4) | (b.sides[s_forward] << 8) | (b.sides[s_bottom] << 12) | (cost << 16); 
    }
};

q_node prev[8][8][6][6] = {};
int path_x[8*8*6*6];
int path_y[8*8*6*6];

bool operator < (q_node const& lhs, q_node const& rhs)
{
    return lhs.code() < rhs.code() ;
}

char in[65536];

int solve()
{
    //1. read informations
    int d[6] = {};
    int x_0, y_0;
    int x_1, y_1;

    //2. read 
    {
        int m;
        const char * o;
        m = fread(in, 1, sizeof(in) - 4, stdin);
        in[m] = '\0';
        o = in;
        
        //1. x_0 and y_0 
        while(*o && *o<=32)++o;
        x_0 = *o++ - 'a' ;
        y_0 = *o++ - '1' ;

        //2. x_1 and y_1
        while(*o && *o<=32)++o;
        x_1 = *o++ - 'a';
        y_1 = *o++ - '1';

        //3. d[0..5]
        for(int i= 0; i !=6; ++i)
        {
            d[i] = 0;
            while(*o && *o<=32)++o;
            while(*o>=48 && *o <= 57) d[i] = (d[i] << 3) + (d[i]<<1) + *o++ - 48;
        }
    } // end reading.

   //II. solve with BFS
    q_node q = { { 0, 1, 2, 3, 4, 5 }, x_0, y_0, d[s_bottom] };
    memset(cell, 0x7F, sizeof(cell));
  
    cell[ x_0 ][ y_0 ][  s_forward  ][  s_bottom  ] = d[ s_bottom ];
  
    prev[ x_0 ][ y_0 ][  s_forward  ][  s_bottom  ].x = -1;

    std::set< q_node > st;
    st.insert(q);

    while(!st.empty())
    {
        q = *st.begin();
        st.erase(st.begin());

#ifndef ONLINE_JUDGE
//debug
{
    typedef const char* pstr;
    static const pstr side_names[6] = {"forward", "backward", "top", "right", "bottom", "left"};
   
    printf("q: pos:  %c%c  , cost : %d, box bottom:   %s ( cost:  %d )}  \n", 
    (char)(q.x + 'a'), (char)(q.y + '1'), q.cost,
        side_names[q.b.sides[s_bottom]], d[q.b.sides[s_bottom]]
    );
    
}
#endif

        for(int k= 0; k != 4; ++k)
        {
            int xn = q.x + DX[k], yn = q.y + DY[ k ];
            box b = rot_direction(q.b, k);

            int fw = b.sides[s_forward];
            int bt = b.sides[s_bottom];
            
            if (xn >= 0 && xn < 8 && yn >= 0 && yn < 8 && cell[ xn ][ yn ][ fw ][ bt ] > q.cost + d[ bt ])
            {
                
                 q_node qn;
                 qn.b = b;
                 qn.x = xn;
                 qn.y = yn;
                 qn.cost = cell[ xn ][ yn ][ fw ][ bt ];

                 //remove if already exists.
                 st.erase(qn);

                 qn.cost = q.cost + d [bt ];
                 
                 //update cell.
                 cell[xn][yn][fw][bt] = q.cost + d[ bt ];

                 //insert a new node
                 st.insert(qn);

                 prev[xn][yn][ fw ][ bt ] = q;
            }
        }
    }

    int min_cost = 0x7F7F7F7F;
    int min_x  = -1, min_y = -1;
    for(int x = 0; x < 6; ++x)
    {
        for(int y = 0; y < 6; ++y)
        {
            if (min_cost > cell[x_1][y_1][x][y])
            {
                min_cost = cell[x_1][y_1][x][y];
                min_x = x;
                min_y = y;
            }
        }
    }

    int np = 1;
    path_x[ 0 ]  = x_1;
    path_y[ 0 ]  = y_1;
    while( !( x_1 == x_0 && y_1 == y_0 && min_x == s_forward && min_y == s_bottom ) )
    {
        // go prev 
        //int x_2, y_2, mx_2, my_2;
        q = prev[x_1][y_1][min_x][min_y];
        x_1 = q.x;
        y_1 = q.y;
        min_x = q.b.sides[ s_forward ] ;
        min_y = q.b.sides[ s_bottom  ] ;
        path_x[ np ] = x_1;
        path_y[ np ] = y_1;
        ++np;
    } 
   
    //II. write result.

    //1. min_cost
    char* w = 0;
    w = in;
    {
        unsigned u = min_cost, v = min_cost, n = 0, m = 0;
        do n++; while(u/=10);
        m = n;
        while(n-->0)w[n] = v%10 + 48, v/=10;
        w += m;
        *w++ = ' ';
    }

    //2. path reverse order 
    while(np-->0)
    {
        int x = path_x[ np ];
        int y = path_y[ np ];

        *w++ = x + 'a';
        *w++ = y + '1';
        *w++ = ' ';
    }
    
    //3. replace last space to Line break. 
    w[-1] = '\n';

    //4. flush 
    fwrite(in, 1, w - in, stdout);

    //end :)
    return 0;
}


int main(int argc, char * argv[])
{
    #ifndef ONLINE_JUDGE
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
    #endif

    solve();

    return 0;
}
