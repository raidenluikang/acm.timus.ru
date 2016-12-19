

// acm.timus.ru 1008. Coding Image.

#include <stdio.h>
#include <string.h>
#include <math.h>

//crash divide to zero.
void judge_assert(bool b){ if (!b)printf("%d",1/b);}

char in[65536];
char out[65536];
const char* o;
char* w;

char table[16][16] = {};
unsigned n_blacks, x_left, y_down;

unsigned qx[128], qy[128], h,t;

int solve()
{
   //read input
   unsigned n_in;
   unsigned a,b;
   n_in = fread(in, 1, sizeof(in) - 4, stdin);
   in[n_in] = '\0';
   
   o = in;
   w = out;

   //determine what is type of image coding
   a = 0;
   while(*o && *o <= 32 && (*o != '\n') ) ++ o;

   judge_assert(*o >='0' && *o <='9');
   a = 0;
   while(*o >='0') a = (a<<3) + (a<<1) + *o++  - '0';

   while(*o && *o <= 32 && (*o != '\n')) ++ o;

   judge_assert(*o != '\0');

   if (*o == '\n') // so first image coding
   {
       n_blacks = a;
       ///////////////////////////////////////////
       for(unsigned i = 0; i != n_blacks; ++i)
       {
           while(*o  && *o <= 32)++o;
           a = 0;
           while(*o >= '0') a = (a<<3) + (a<<1) + *o++ - '0';

           b = 0;
           while(*o && *o <= 32)++o;
           while(*o >='0') b = (b << 3) + (b<<1) + *o++ -'0';
           judge_assert(a>= 1 && a<=10 && b>=1 && b<=10);
           table[a][b] = 1;
       }


       //to convert second image coding

       //1. find left down black cell
       x_left = 0;
       y_down = 0;
       for(unsigned x = 1; x <= 10; ++x)
       {
           for(unsigned y = 1; y <= 10; ++y)
           {
               if (table[ x ][ y ])
               {
                   if ( x_left == 0 || x_left > x || (x_left == x && y_down > y))
                   {
                       x_left = x;
                       y_down = y;
                   }
               }
           }
       }

       //2. put x_left y_down to out
       {
           unsigned u = x_left, n = 0, m;
           do n++; while(u/=10);
           m = n;
           u = x_left;
           while(m-->0)w[m] =u%10 + '0', u/=10;
           w += n;
           *w++ = ' '; 
       }

       {
           unsigned u = y_down, n = 0, m;
           do n++; while(u/=10);
           m  = n ;
           u = y_down;
           while(m-->0)w[m] = u%10 + '0', u/=10;
           w += n;
           //*w++ = '\n';
       }

       qx[0] = x_left;
       qy[0] = y_down;
       table[x_left][y_down] = 0;
       h = 0;
       t = 1;
       while( h < t)
       {
           unsigned x,y;
           x = qx[h];
           y = qy[h];
           ++h;

           *w++ = '\n';//a new black cell.
           // right
           if (table[x+1][y])
           {
               qx[t] = x+1;
               qy[t] = y;
               ++t;
               table[x+1][y] = 0;

               *w++ = 'R';
           }

           //up
           if (table[x][y+1])
           {
               qx[t] = x;
               qy[t] = y + 1;
               ++t;
               table[x][y+1] = 0;

               *w++ = 'T';
           }

           //left
           if (table[x-1][y])
           {
               qx[t] = x-1;
               qy[t] = y;
               ++t;

               table[x-1][y] = 0;

               *w++ = 'L';
           }

           //down
           if (table[x][y-1])
           {
               qx[t] = x;
               qy[t] = y - 1;
               ++t;

               table[x][y-1] = 0;

               *w++ = 'B';
           }

           //end with ','
           *w++ = ',';
       }//end while(h < t)

       // last ends with '.'
       w[-1] = '.';
       *w++ = '\n';
   }
   else // second image coding
   {
       x_left = a;
       judge_assert(*o >= '0' && *o <= '9');
       b = 0;
       while(*o >= '0' ) b = (b << 3) + (b<<1) + *o++  - '0';
       y_down = b;
       
       while(*o && *o != '\n')++o;
       judge_assert(*o != '\0');
       ++o;
       /////////////////////////////////////////
       table[x_left][y_down] = 1;

       //printf("x_left = %u\ty_down = %u\n",x_left, y_down);
       qx[0] = x_left;
       qy[0] = y_down;
       h = 0;
       t = 1;
       while( h < t)
       {
           unsigned x,y;
           x = qx[h];
           y = qy[h];
           ++h;
           
           while(*o && *o != '\n')
           {
               switch(*o++)
               {
                   case 'R': // right
                   { 
                       table[x+1][y] = 1;
                       qx[t] = x + 1;
                       qy[t] = y;
                       ++t;
                   }
                   break;

                   case 'T': // top
                   {
                       table[x][y+1] = 1;
                       qx[t] = x;
                       qy[t] = y + 1;
                       ++t;
                   }
                   break;
                   case 'L': // left
                   {
                       table[x-1][y] = 1;
                       qx[t] = x-1;
                       qy[t] = y;
                       ++t;
                   }
                   break;
                   case 'B': // bottom
                   {
                       table[x][y-1] = 1;
                       qx[t] = x;
                       qy[t] = y - 1;
                       ++t;
                   }
                   break;
               } // end switch
           } // end read line 

          if (*o=='\n')++o;
       } // end while (h < t)

       a = 0;
       for(unsigned x = 1; x <= 10; ++x)
       {
           for(unsigned y = 1; y <= 10; ++y)
           {
               if(table[x][y])
                 ++a;
           }
       }

       // write a 
       {
           unsigned u = a, n = 0,m;
           do n++; while(u/=10);
           m = n;
           u = a;
           while(n-->0)w[n] = u % 10 + '0', u/=10;
           w += m;

           *w++ = '\n';
       }

       for(unsigned x = 1; x <= 10; ++x)
       {
           for(unsigned y = 1; y <= 10; ++y)
           {
               if (!table[x][y]) continue;
               // write x y
               if (x < 10) *w++ = x + 48 ; else 
               {*w++ = x/10 + '0'; *w++ = x%10 + '0';}

               *w++ = ' ';
               if (y < 10) *w++ = y + 48; else 
               {*w++ = y/10 + '0'; *w++ = y % 10 + '0';}
               *w++ = '\n';
           }
       }

   } // end image encoding 

    fwrite(out, 1, w - out, stdout);
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
