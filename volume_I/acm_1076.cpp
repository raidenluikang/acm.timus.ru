

// acm.timus.ru 1076. Trash.

#include <cstdio>
#include <cstring>
#include <algorithm>

static const unsigned N = 156;

static const unsigned INF= 1000000000;
static const unsigned char MASK[2] = { 0, 255 };
static const unsigned BIT_MASK[32] =
{
    (1u << 0 ), (1u << 1 ), (1u << 2 ), (1u << 3 ),
    (1u << 4 ), (1u << 5 ), (1u << 6 ), (1u << 7 ),
    (1u << 8 ), (1u << 9 ), (1u << 10), (1u << 11),
    (1u << 12), (1u << 13), (1u << 14), (1u << 15),
    (1u << 16), (1u << 17), (1u << 18), (1u << 19),
    (1u << 20), (1u << 21), (1u << 22), (1u << 23),
    (1u << 24), (1u << 25), (1u << 26), (1u << 27),
    (1u << 28), (1u << 29), (1u << 30), (1u << 31)
};

#ifdef SET_BIT
#undef SET_BIT
#endif
#ifdef TEST_BIT
#undef TEST_BIT
#endif

#define SET_BIT(B,i)  B[(i) >> 5] |= BIT_MASK[(i) & 31]
#define TEST_BIT(B,i) (B[(i)>>5] & BIT_MASK[(i) & 31] )


#ifdef _MSC_VER
#define JUDGE_ALIGN   __declspec(align(128))
#else 
#define JUDGE_ALIGN 
#endif

// N * N = 150 * 150 = 22 500 , 22 500 * 4 = 10^5
JUDGE_ALIGN
char in[ 1 << 17 ];// enough, i thing.

JUDGE_ALIGN
const char* o;

typedef  short int_type;

JUDGE_ALIGN
unsigned char cost[N][N]; // cost matrix

JUDGE_ALIGN
int n, max_match;  // n workers and n jobs

JUDGE_ALIGN
unsigned char lx[N], ly[N]; // labels of X and Y parts

JUDGE_ALIGN
unsigned char xy[N];        // xy[x] - vertex that is matched with x.

JUDGE_ALIGN
unsigned char yx[N];        // yx[y] - vertex that is matched with y.

JUDGE_ALIGN
unsigned S[5], T[5];   // sets S and T in algorithm.


JUDGE_ALIGN
unsigned char slack[N]; // as in the algorithm description

JUDGE_ALIGN
unsigned char slackx[N]; // slackx[y] = such a vertex , that l(slackx[y] + l(y) - w(slackx[y],y) = slack[y])

JUDGE_ALIGN
unsigned char prev[N]; // array for memorizing alternating paths

JUDGE_ALIGN
unsigned char q[N];


JUDGE_ALIGN
int total_sum;

static  unsigned char readInt();	
static void readData();
static void update_labels();
static void add_to_tree(int_type xy, int_type y);

static unsigned char readInt()
{
    unsigned char u = 0;
    while ( *o && *o <= 32 ) ++ o;
    while ( *o >= 48) u = ( u << 3 ) + ( u << 1 )  +  *o++ - 48;
    return u;
}

static void readData()
{
    unsigned m;
    m = fread(in, 1 , sizeof( in ) - 4, stdin );
    in [ m ] = '\0';
    o = in;

    n = readInt();
    memset(lx, 100, sizeof(lx));
    memset(ly, 0, sizeof(ly));
    
    total_sum = 0;
    for(int x = 0; x != n; ++x)
    {
        for(int y = 0; y != n; ++y) 
        {
             cost[ x ][ y ] = readInt();
             total_sum += cost[x][y];
        }
    }
}

	
//step 1 
static void augment()
{
     for(int i = 0; i != n; ++i)
     {        
        int x, y, root = -1;
        int wr = 0, rd = 0;
        
        memset(S, 0, sizeof(S));
        memset(T, 0, sizeof(T));
        memset(prev, 0xFF, sizeof(prev));
        
        
        for (x = 0; x < n; x ++)
        {
            if (xy[ x ] == 0xFF)
            {
                q[wr++] = root = x;
                prev[ x ] = 0xFE;
                SET_BIT(S,x);//S[ x >> 5 ] |= BIT_MASK[x&31];
                break;
            }
        }
        
        for (y = 0; y < n; y++)
        {
            slack[ y ] = lx[ root ] + ly[ y ] - cost[ root ][ y ];
            slackx[y] = root;
        }
        
        
        // second part augment function
        
        while(true)
        {
            
            while(rd < wr)
            {
                x = q[rd++];
                for (y = 0; y < n; y++)
                {
                    if ( ! TEST_BIT(T,y) )//(T[y>>5] & BIT_MASK[ y & 31 ]) )
                    if (cost[x][y] == lx[x] + ly[y])
                    {
                        if (yx[y]==0xFF)break;
                        SET_BIT(T,y);//T[y >> 5] |= BIT_MASK[y&31];
                        q[wr++] = yx[y];
                        add_to_tree(yx[y], x);
                    }
                }
                if (y < n)break;
            }
            if (y < n)break;
            
            update_labels();
            
            wr = rd = 0;
            for (y = 0; y< n; y++)
            {

                //if (!(T[ y >> 5] & BIT_MASK[y&31]) && slack[y]==0)
                if (! TEST_BIT(T,y) && !slack[y] )
                {
                    if (yx[y] == 0xFF)
                    {
                        x = slackx[y];
                        break;
                    }else
                    {
                        SET_BIT(T,y);
                        //T[y>>5] |= BIT_MASK[ y & 31];
                        if (! TEST_BIT(S,yx[y]) ) //( S[ yx[y] >> 5 ] & BIT_MASK[yx[y] & 31] ) )
                        {
                            q[wr++] = yx[y];
                            
                            add_to_tree(yx[y], slackx[y]);
                        }
                    }
                }	
            }
            if (y<n)break;
        }
        
        max_match++;
        
        for (int_type cx = x, cy = y, ty; cx != 0xFE; cx = prev[cx], cy = ty)
        {
            ty = xy[cx];
            yx[cy] = cx;
            xy[cx] = cy;
        }
        
    } // end while(true)
    
}//end of augment() function
	
	
//step 2 update

static void update_labels(){
    int_type x, y;
    unsigned char delta  = 255;

    for (y = 0; y < n; y++)
    {
        if ( ! TEST_BIT(T,y) )//( ( T[ y >> 5] & BIT_MASK[y & 31]) ) )
        {
            delta = ::std::min( delta, slack[ y ] ) ;
        }
    }

   // a = true -> 0xFFFFFFFF,   false => 0 
    for (y = 0; y < n;y++)
    {
        lx[ y ]  -= delta & MASK[ !!TEST_BIT(S, y)] ; //(S[ y >> 5 ] >> (y&31) ) & 1 ];
        ly[ y ]  += delta & MASK[ !!TEST_BIT(T, y)] ; //(T[ y >> 5 ] >> (y&31) ) & 1 ];
        slack[y] -= delta & MASK[ ! TEST_BIT(T, y)] ; //( ( T[y >> 5 ] >> (y&31) ) & 1) ];
        
    }
}
	
	
//step 3

//1 Here's the function that adds new edges to the alternating tree:
static void add_to_tree(int_type x, int_type prevx){
    //x - current vertex, prevx - veertex from X before x int the alternating path
    //so we add edges (prevx, xy[x]), (xy[x], x)
    
    SET_BIT(S,x);//S[ x >> 5 ] |= BIT_MASK[  x &  31];   //add x to S
    prev[ x ] = prevx; //we need this when augmenting
    for (int_type y = 0; y < n; y++)
    {
        if (lx[x] + ly[y] - cost[x][y] < slack[y])
        {
            slack[y] = lx[x] + ly[y] - cost[x][y];
            slackx[y] = x;
        }
    } 
}
	
//2 And now, the end of the augment() function:
	
	
	
//second part of augment() function
//hungarian() funciton
static int hungarian()
{
    int ret  =  0;
    max_match = 0;
    memset(xy, 0xFF, sizeof(xy));
    memset(yx, 0xFF, sizeof(yx));
    augment();
    for (int_type x = 0; x < n; x ++){
        ret += cost[ x ][ xy[ x ] ];
    }
    return total_sum - ret;

}


int solve()
{
    readData();
    int r = hungarian();
    printf("%d\n",r);
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
