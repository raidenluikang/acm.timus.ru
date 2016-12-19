

// acm.timus.ru 1015. Test the Difference.

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

#ifdef _MSC_VER  // Visual Studio C/C++

#define JUDGE_ALIGNED_PREF  __declspec(align(128))
#define JUDGE_ALIGNED_SUFF  

#else 
 
#define JUDGE_ALIGNED_PREF   
#define JUDGE_ALIGNED_SUFF  __attribute__((aligned(128)))

#endif

//crash divide to zero.
void judge_assert(bool b){ if (!b)printf("%d",1/b);}

struct box
{
    unsigned char a[ 6 ];
};

enum BoxSides
{
  BS_LEFT,    // 0
  BS_RIGHT,   // 1
  BS_TOP,     // 2
  BS_FORWARD, // 3
  BS_BOTTOM,  // 4
  BS_BACKWARD // 5
};

box rotateLeft(box const& b)
{
     box r;
     r.a[BS_LEFT    ]  = b.a[ BS_TOP      ];
     r.a[BS_RIGHT   ]  = b.a[ BS_BOTTOM   ];
     r.a[BS_TOP     ]  = b.a[ BS_RIGHT    ];
     r.a[BS_FORWARD ]  = b.a[ BS_FORWARD  ];
     r.a[BS_BOTTOM  ]  = b.a[ BS_LEFT     ];
     r.a[BS_BACKWARD]  = b.a[ BS_BACKWARD ];

     return r;
}

box rotateForward(box const& b)
{
    box r;
    r.a[BS_LEFT    ] = b.a[ BS_LEFT    ];
    r.a[BS_RIGHT   ] = b.a[ BS_RIGHT   ];
    r.a[BS_TOP     ] = b.a[ BS_BACKWARD];
    r.a[BS_FORWARD ] = b.a[ BS_TOP     ];
    r.a[BS_BOTTOM  ] = b.a[ BS_FORWARD ];
    r.a[BS_BACKWARD] = b.a[ BS_BOTTOM  ];
    return r;
}




// 1 2 3 4 5 [6] -> code   
// Note: code doesnt contain BACKWARD id, because its not useful. 
unsigned toCode(box const& bx)
{
    // 32 bit:  3 bit each number  * 6 number == 18 bit
    // 6 5 4 3 2 1 :  110 101 100 011 010 001 == 
    return ( (unsigned)(bx.a[ 0 ]) << 0 ) |
           ( (unsigned)(bx.a[ 1 ]) << 3 ) |
           ( (unsigned)(bx.a[ 2 ]) << 6 ) |
           ( (unsigned)(bx.a[ 3 ]) << 9 ) |
           ( (unsigned)(bx.a[ 4 ]) << 12) ;//|
           //( (unsigned)(bx.a[ 5 ]) << 15) ;
     
}

// 8..26 bits code, 0..7 - id
typedef unsigned box_code;

JUDGE_ALIGNED_PREF
unsigned char box_id[ 1 << 15 ] JUDGE_ALIGNED_SUFF; 
 
 //fills box_id array
void fill_box(box b, unsigned char id)
{
    for(unsigned i = 0; i != 4; ++i)
    {
        for(unsigned j = 0; j != 4; ++j)
        {
            box_id[toCode(b)] = id;
            b = rotateLeft(b);
        }
        b = rotateForward(b);
    }

    b = rotateLeft(b);
    b = rotateForward(b);
    for(unsigned j = 0; j != 4; ++j)
    {
        box_id[toCode(b)] = id;
        b = rotateLeft(b);
    }

    b = rotateForward(b);
    b = rotateForward(b);
    for(unsigned j = 0; j != 4; ++j)
    {
        box_id[toCode(b)] = id;
        b = rotateLeft(b);
    }
} 
void init()
{
    unsigned char id = 1;
    box b = {0,1,2,3,4,5};    
    fill_box(b, 1);

    while(std::next_permutation(b.a, b.a + 6))
    {
        unsigned x = box_id[ toCode ( b ) ];
        if (x == 0) // a new 
        {
            ++id;
            fill_box(b, id);
        }
    }
}

// n <= 10^5     "1 2 3 4 5 6\n" : 12 symbols: total symbols = 10^5*12 = 1.2*10^6.
JUDGE_ALIGNED_PREF
char in[ ( 1 << 20 ) + ( 1 << 18 ) ] JUDGE_ALIGNED_SUFF;

JUDGE_ALIGNED_PREF
const unsigned* o  JUDGE_ALIGNED_SUFF;

JUDGE_ALIGNED_PREF
char * w  JUDGE_ALIGNED_SUFF;

JUDGE_ALIGNED_PREF
unsigned id_visit[ 32     ]JUDGE_ALIGNED_SUFF;

JUDGE_ALIGNED_PREF
unsigned id_head [ 32     ]JUDGE_ALIGNED_SUFF;

JUDGE_ALIGNED_PREF
unsigned id_next [ 1 << 17]JUDGE_ALIGNED_SUFF;

void writeInt(unsigned u, char c)
{
    unsigned v = u, n = 0;
    do ++n; while(v/=10);
    v = n;
    while(v-->0)w[v] = u%10 + '0', u/=10;
    w += n;
    *w++ = c;
}

int solve()
{

    unsigned n;
    unsigned n_in;
    
    init();

    //1. read n
    {
        int c;
        //skip spaces
        while((c = getc(stdin)) <= 32) ;
        
        // read digits
        n = c - 48;
        while((c=getc(stdin)) >= 48) n = (n<<3) + (n<<1) + c - 48;
        
        //read until end of line.
        while(c != '\n') c = getc(stdin); 
    }

    //printf("\\n value: 0x%0x\n", (unsigned)'\n');

    for(unsigned i = 0; i != 32; ++i)
    {
        id_head[i]  = 0;
        id_visit[i] = 0;
    }

    n_in = fread(in, 1, sizeof(in) - 4, stdin);
    in[ n_in ] = '\0';
    o =(const unsigned*) in;
    w = in;
    
    
    for(unsigned i = 0; i != n; ++i)
    {
        // 1 2 3 4 5 6\n  : 12 symbols
        // c0 = '1 2 '
        // c1 = '3 4 '
        // c3 = '5 6 '
        
        unsigned c_0 = *o++ -  0x20312031;
        unsigned c_1 = *o++ -  0x20312031;
        unsigned c_2 = *o++ -  0x0A312031;
        unsigned code = ( ( (c_0 & 0xFF) | ( ( c_0 & 0xFF0000 ) >> 13 ) ) << 0 ) |
                        ( ( (c_1 & 0xFF) | ( ( c_1 & 0xFF0000 ) >> 13 ) ) << 6 )|
                        ( ( (c_2 & 0xFF) ) << 12 ) ;
       
       unsigned char id = box_id[ code ];

       id_next [ id_head[ id ] ] |= i + 1;
       id_next [ i + 1   ]   =  ( id << 24 );
       id_head [ id  ]       = i + 1;
    }
    
    unsigned n_codes = 0;
    for(unsigned i = 0; i != 32; ++i)
    {
        bool has = id_head[i] != 0;
        id_visit[ i ] = has;
        n_codes += has;
    }


    // now write they.
    w = in;
    writeInt(n_codes, '\n');
    for(unsigned i = 0; i != n; ++i)
    {
        unsigned char id = id_next[ i + 1 ] >> 24 ;
        if (id_visit[ id ] )
        {
            id_visit[ id ] = false;
            for(unsigned h = i + 1; h > 0; h = id_next[ h ] & 0xFFFFFF )
            {
                writeInt(h, ' ');
            }

            //change last space to '\n';
            w[-1] = '\n';
        }
    }

    fwrite(in, 1, w - in, stdout);
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
