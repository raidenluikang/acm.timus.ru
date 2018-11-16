#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cassert>


#define eps  1.0E-12

typedef long long ll;
 
struct block
{
    int type;
    int ix, iz,    iy    ;
    double wx, wz, wy    ;
    bool   bx, bz, by    ;
}blocks[40];


int n, que[ 1208 ];

void no_solution(){
    printf("No solution\n");
    exit(0);
}

int main(int argc, char* argv[] )
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif //ONLINE_JUDGE
    
    memset(blocks,0,sizeof(blocks));
    
    scanf("%d",&n);
    for(int i= 1; i<= n; ++i)
    {
        
        scanf("%d%d%d%d", &blocks[i].type, &blocks[i].ix, &blocks[i].iz, &blocks[i].iy ) ;
    }
    
    int t=0;
    
    for(int i=  1; i <= n; ++i)
    {
        if (blocks[i].type == 1 )
        {
            assert(blocks[i].iy != -1);
            
            if (blocks[i].ix == -1 ) 
            {
                blocks[i].wx = 1.0;
                blocks[i].bx = true;
                que[t++] = ( i << 2 ) | 1 ;
            } 
            else if (blocks[i].iz == -1 ) 
            {
                blocks[i].wz = 1.0;
                blocks[i].bz = true;
                que[t++] = (i<<2) | 2;
            }
        } 
        else 
        {
            if (blocks[i].iy == -1 ) 
            {
                blocks[i].wy = 1.0;
                blocks[i].by = true;
                que[t++] = (i<<2) | 3;
            }
        }
    }
    
    double ans = 0.0;
    bool ans_fnd = false;
    
    for(int h = 0; h < t; ++h)
    {
        int i = que[ h ] >> 2 ;
        int which = que[ h ] & 3 ;
        
        
        if ( which == 1 ) 
        {
            //ix initialized
            if (blocks[i].ix == -2 ) {
                ans = blocks[i].wx ;
                ans_fnd = true;
            }
            
            
            if (blocks[i].bz == false ) 
            {
                blocks[i].wz = blocks[i].wx ;
                blocks[i].bz = true;
                que[t++] = ( i << 2  ) |2 ;
            } 
            else 
            {
                if ( fabs( blocks[ i ].wx - blocks[ i ].wz ) > eps  )
                {
                    no_solution();
                }
            }
            
            if (blocks[i].by == false) 
            {
                blocks[i].wy = 2 * blocks[ i ].wx ;
                blocks[i].by = true;
                que[ t++ ] = ( i << 2 ) | 3 ;
            } 
            else 
            {
                if ( fabs( blocks[i].wx * 2 - blocks[i].wy ) > eps )
                {    
                    no_solution();
                }
            }
            
            
            if (blocks[i].ix > 0 ) 
            {
                int j = blocks[i].ix;
                
                if (blocks[j].ix == i ) 
                {
                    if (blocks[i].type == blocks[j].type ) {
                        no_solution();
                    }
                    
                    if (blocks[j].bx == false ) 
                    {
                        blocks[j].bx = true;
                        blocks[j].wx = blocks[i].wx ;
                        que[t++] = ( j << 2 ) | 1 ;
                    } 
                    else 
                    {
                        if (fabs(blocks[j].wx - blocks[i].wx) > eps ) 
                        {
                            no_solution();
                        }
                    }
                } 
                else if (blocks[j].iz == i ) 
                {
                    if (blocks[i].type == blocks[j].type ) {
                        no_solution();
                    }
                    
                    if (blocks[j].bz == false ) 
                    {
                        blocks[j].bz = true;
                        blocks[j].wz = blocks[i].wx;
                        que[t++] = ( j << 2 ) | 2 ;
                    } 
                    else 
                    {
                        if (fabs( blocks[i].wx - blocks[j].wz ) > eps ) 
                        {
                            no_solution();
                        }
                    }
                } 
                else if (blocks[j].iy == i ) 
                {
                   // if(blocks[i].type != blocks[j].type ) {
                   //     no_solution();
                   // }
                    
                    if (blocks[j].by == false ) {
                        blocks[j].by = true;
                        blocks[j].wy = blocks[i].wx;
                        que[t++] = (j<<2) | 3;
                    } else {
                        if (fabs(blocks[i].wx - blocks[j].wy ) > eps){
                            no_solution();
                        }
                    }
                } else {
                    assert(false);
                }
            } // end if blocks[i].ix > 0 
        } // end if which == 1
        else if (which == 2 ) 
        {
            //iz initialized
            if (blocks[i].iz == -2 )
            {
                ans = blocks[i].wz ;
                ans_fnd = true;
            }
            
            if (blocks[i].bx == false ) 
            {
                blocks[i].bx = true;
                blocks[i].wx = blocks[i].wz ;
                que[t++] = (i<<2) | 1;
            } else {
                if (fabs(blocks[i].wx - blocks[i].wz) > eps ) {
                    no_solution();
                }
            }
            
            if (blocks[i].by == false ) 
            {
                blocks[i].by = true;
                blocks[i].wy = 2 * blocks[i].wz ;
                que[t++] = (i<<2) | 3;
            } else {
                if (fabs(blocks[i].wz*2 - blocks[i].wy  ) > eps ) {
                    no_solution();
                }
            }
            
            if (blocks[i].iz >  0 ) 
            {
                int j = blocks[i].iz ;
                
                
                
                if (blocks[j].ix == i ) {
                    if (blocks[i].type == blocks[j].type ) no_solution();
                    if (blocks[j].bx == false ) {
                        blocks[j].bx = true;
                        blocks[j].wx = blocks[i].wz ;
                        que[t++] = (j<<2)|1;
                    }  else if (fabs(blocks[j].wx - blocks[i].wz)  >  eps ) no_solution();
                } else if (blocks[j].iz == i ) {
                    if (blocks[i].type == blocks[j].type ) no_solution();
                    if (blocks[j].bz == false){
                        blocks[j].bz = true;
                        blocks[j].wz = blocks[i].wz;
                        que[t++] = (j<<2)|2;
                    } else if ( fabs(blocks[j].wz - blocks[i].wz) > eps ) no_solution();
                } else if (blocks[j].iy == i ) {
                    //if (blocks[i].type == blocks[j].type ) no_solution();
                    if (blocks[j].by == false){
                        blocks[j].wy = blocks[i].wz;
                        blocks[j].by = true;
                        que[t++] = (j<<2)|3;
                    } else if (fabs(blocks[j].wy - blocks[i].wz) > eps ) no_solution();
                } else {
                    assert(false);
                }
            }
            
        } // end if which == 2 
        else if (which == 3 )
        {
            if (blocks[i].iy == -2) {
                assert(blocks[i].type == 2 ) ;
                ans = blocks[i].wy ;
                ans_fnd = true;
            } 
            
            if (blocks[i].bx == false ) {
                blocks[i].wx = blocks[i].wy * 0.5 ;
                blocks[i].bx = true;
                que[t++] = (i<<2)|1;
            } else if (fabs(blocks[i].wx*2 - blocks[i].wy) > eps ) no_solution();
            
            
            if (blocks[i].bz == false ) {
                blocks[i].wz = blocks[i].wy * 0.5 ;
                blocks[i].bz = true;
                que[t++] = (i<<2)|2;
            } else if ( fabs(blocks[i].wz * 2 - blocks[i].wy ) > eps ) no_solution();
            
            if (blocks[i].iy > 0 ) {
                int j = blocks[i].iy;
                
                if (blocks[j].iy == i ) {
                    if (blocks[i].type == blocks[j].type ) no_solution();
                    if (blocks[j].by == false ) {
                        blocks[j].by = true;
                        blocks[j].wy = blocks[i].wy ;
                        que[t++] = (j<<2) | 3 ;
                    } else if ( fabs(blocks[i].wy - blocks[j].wy ) > eps ) no_solution();
                } else if (blocks[j].ix == i ) {
                    if (blocks[j].bx == false ) {
                        blocks[j].bx = true;
                        blocks[j].wx = blocks[i].wy ;
                        que[t++] = (j<<2) | 1;
                    } else if (fabs(blocks[i].wy - blocks[j].wx ) > eps ) no_solution();
                } else if (blocks[j].iz == i ){
                    if(blocks[j].bz == false ) {
                        blocks[j].wz = blocks[i].wy ;
                        blocks[j].bz = true;
                        que[t++]  = (j<<2) | 2;
                    } else if (fabs(blocks[i].wy - blocks[j].wz ) > eps ) no_solution();
                } else {
                    assert(false);
                }
            }
        } // end if which == 3
        else
        {
            assert(false);
        }
    } // end while(!que.empty())
    
    
    
    if (!ans_fnd){
        printf("Any\n");
    } else {
        printf("%.4f\n", ans);
    }
    
    
}
