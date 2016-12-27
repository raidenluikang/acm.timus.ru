

// acm.timus.ru 1060. Flip Game


#include <cstdio>

static const int mat[ 2 ][ 16 ] = 
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {19,39,78,140,305,626,1252,2248,4880,10016,20032,35968,12544,29184,58368,51200}
};

static const int bitcnt[16] = 
{
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4
};
static inline int bits(int n)
{
    return bitcnt[n&15] + bitcnt[(n>>4) & 15] + bitcnt[(n>>8)&15] + bitcnt[(n>>12) & 15];
}

int id[ 65536 ]={};

int main()
{

    #ifndef ONLINE_JUDGE

    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif 
    
    int white = 0;
    
    char in[64];
    
    in[fread(in, 1, sizeof(in)-4,stdin)] = 0;
    
    char const* o = in;
    
    for(int i = 0; i != 4; ++i)
    {
        for(int j = 0; j!= 4; ++j)
        {
             white |= ( o[0] == 'w' ? 1 : 0) << ( (i << 2) | j );
             ++o;
        }
        ++o;
        //getc(stdin) ; // break line or end of file )
   }

   for(int h = 0; h < 256; ++h)
   {
       int low = white & 0x00FF; // low 8 bits
       for(int i = 0; i < 8; ++i)
       {
           low ^= mat[ ( h >> i ) & 1][ i ];
       }
       id [ low ] = h + 1;
   }
   int rn = 100;
   
    // h = 417 = 256 * 1 + 44 + 117 = 256 + 161
   
   for(int h = 0; h < 256; ++h)
   {
       int high = white & 0xFF00;// high 8 bits
       //int hh = h << 8;
       for(int i = 0; i < 8; ++i)
       {
           high ^= mat[ ( h >> i ) & 1 ][ i + 8 ];
       }    
       // tmp = high 
       // low = x 
       // but, we know   high ^ low = 0   or  high ^ low = 0xFFFF
       // tmp ^ x = 0 --> x = tmp 
       // tmp ^ x = 0xFFFF --> x = tmp ^ 0xFFFF
       int wh = high;
       int bl = high ^ 0xFFFF;
       if (id[ wh ])
       {
           int hh = (id[ wh ] - 1) | ( h << 8 );
           int k = bits(hh);
           if (k < rn)rn = k; 
       }
       if (id[bl])
       {
           int hh = (id[bl] - 1) | (h << 8);
           int k = bits(hh);
           if (k < rn) rn = k;
       }
   }

   if (rn > 16)
   {
       puts("Impossible");
   }
   else
   {
       char in[12] = {};
       char * w = in + 12;
       *--w = '\n';
       do *--w = rn % 10 + '0'; while(rn/=10);
       fwrite(w, 1, in + 12 - w, stdout);
       //printf("%d\n",rn);
   }

   return 0;
}
