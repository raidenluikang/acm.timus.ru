#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <vector>
#include <array>
#include <algorithm>
#include <cassert>

char in[ 1 << 14 ]; 
const char* oo;
char * ww;
void init_in(){
    in[fread(in,1,sizeof(in)-4, stdin)] = 0;
    oo = in;
    ww = in;
}
int read_int(){
    int x = 0;
    while(*oo && *oo <= 32) ++oo;
    while(*oo >= '0' && *oo <= '9' ) x = x * 10 + (*oo ++ ) - '0';
    return x;
}
void write_int(int x, char e)
{
    static char buf[16];
    static int i;
    i = 16;
    buf[--i] = e;
    do{
        buf[--i] = x % 10  + 48;
        x /= 10;
    }while(x>0);
    
    for( ; i != 16; ++i){
        *ww++ = buf[i];
    }
}


static const int P[24][4] = 
{
 { 0 , 1, 2, 3 }, { 0 , 1, 3, 2 }, { 0 , 2, 1, 3 },  { 0 , 2, 3, 1 },
 { 0 , 3, 1, 2 }, { 0 , 3, 2, 1 }, { 1 , 0, 2, 3 },  { 1 , 0, 3, 2 },
 { 1 , 2, 0, 3 }, { 1 , 2, 3, 0 }, { 1 , 3, 0, 2 },  { 1 , 3, 2, 0 },
 { 2 , 0, 1, 3 }, { 2 , 0, 3, 1 }, { 2 , 1, 0, 3 },  { 2 , 1, 3, 0 },
 { 2 , 3, 0, 1 }, { 2 , 3, 1, 0 }, { 3 , 0, 1, 2 },  { 3 , 0, 2, 1 },
 { 3 , 1, 0, 2 }, { 3 , 1, 2, 0 }, { 3 , 2, 0, 1 },  { 3 , 2, 1, 0 },
};
static const int PR[24][4] = {
{ 0, 1, 2, 3 }, { 0, 1, 3, 2 }, { 0, 2, 1, 3 }, { 0, 3, 1, 2 }, 
{ 0, 2, 3, 1 }, { 0, 3, 2, 1 }, { 1, 0, 2, 3 }, { 1, 0, 3, 2 }, 
{ 2, 0, 1, 3 }, { 3, 0, 1, 2 }, { 2, 0, 3, 1 }, { 3, 0, 2, 1 }, 
{ 1, 2, 0, 3 }, { 1, 3, 0, 2 }, { 2, 1, 0, 3 }, { 3, 1, 0, 2 }, 
{ 2, 3, 0, 1 }, { 3, 2, 0, 1 }, { 1, 2, 3, 0 }, { 1, 3, 2, 0 }, 
{ 2, 1, 3, 0 }, { 3, 1, 2, 0 }, { 2, 3, 1, 0 }, { 3, 2, 1, 0 }, 
};
static int add_a[128] = {};
static int add_b[128] = {};

int game[4][4];
bool pass[4][4];
bool can[24];

typedef std::pair<int, int > pii ;
typedef std::array< pii, 4 > pii4;




 void play(int a, int b, int d , pii4& ball_o)
{
     ball_o[a].first += add_a[d + 64];
     ball_o[a].second += d;
     
     ball_o[b].first += add_b[d + 64 ] ;
     ball_o[b].second -= d ;
     
}
 
 

void print_ans(  )
{
    int m = 0 ;
    for(int i = 0; i < 24; ++i) {
        if (can[i] ) {
            ++m;
        }
    }
  
     write_int(m, '\n');
    for(int i= 0; i < 24; ++i)
    {
        if(can[i] ) {
            write_int(1+P[i][0], ' ');
            write_int(1+P[i][1], ' ');
            write_int(1+P[i][2], ' ' );
            write_int(1+P[i][3], '\n');
        }
    }
    fwrite(in, 1, ww - in, stdout); 
}


bool check(int id, const pii4 & b){
    return  b[P[id][0]] >= b[P[id][1]] &&
            b[P[id][1]] >= b[P[id][2]] &&
            b[P[id][2]] >= b[P[id][3]] ;
}

bool check_win(int id, int a, int b, pii4  ball )
{
    int a_pos = PR[id][a], b_pos = PR[id][b];
    
    ball[a].first  += 3;

    
    bool ch = ball[P[id][0]].first >= ball[P[id][1]].first && 
              ball[P[id][1]].first >= ball[P[id][2]].first && 
              ball[P[id][2]].first >= ball[P[id][3]].first ;
    
    if(!ch) return false;
    
    int a_min = 1, a_max = 100, b_min  = 1 , b_max = 100;
    
    
    if(a_pos > 0) 
    {
        int a_prev =  P[id][a_pos - 1 ]  ;
    
        if( ball[a_prev].first == ball[ a ].first ) 
        {
        
            if( ball[a_prev].second < ball[a].second) return false;
            
            int c_max = ball[a_prev].second - ball[a].second;
            
            if( a_prev  == b ) {
                // a + x <= b - x
                // x * 2 <= b - a = c_max
                // x <= c_max/2 
                c_max  = (c_max + 0)/2 ;
            }
            a_max = std::min(a_max, c_max);
        }
    }
    if(a_pos < 3 ) {
        int a_next =  P[id][a_pos + 1]   ;
        if( ball[ a_next ] .first == ball[a].first && ball[a_next].second > ball[a].second ) {
            int c_min = ball[ a_next] .second - ball[a].second;
            if( a_next == b ) {
                // a + x >= b - x
                c_min  = (c_min + 1)/2;
            }
            a_min = std::max(a_min, c_min);
        }
    }
    
    if(b_pos > 0 ) {
        int b_prev =  P[id][b_pos-1] ;
        if( ball[ b_prev ] .first == ball[b].first && ball[ b_prev ] .second < ball[b].second) {
            int c_min = ball[b].second - ball[b_prev].second;
            // bx - x <= cx + x
            if( b_prev == a) c_min = (1+c_min)/2;
            b_min =std::max(b_min, c_min);
        }
    }
    if(b_pos < 3 ) {
        int b_next =   P[id][b_pos + 1]  ;
        if( ball[ b_next ] .first == ball[b].first ) {
            if( ball[ b_next ] .second > ball[b].second) return false;
            int c_max =   ball[b].second - ball[ b_next ] .second;
            
            if( b_next == a) 
                c_max =( 0 + c_max ) / 2 ;
            
            b_max = std::min(b_max, c_max);
        }
    }
    
    int c_min = std::max(a_min, b_min), c_max = std::min(a_max, b_max);
    if(c_min > c_max) return false;
    
    int cc = c_min ;
    
    ball[a].second += cc ;
    ball[b].second -= cc ;
    
   // printf("id = %d  cc = %d\n", id, cc);
    return check(id, ball);
}

bool check_last(int id, int a, int b, pii4 & ball )
{
    //1. draw
    ball[a].first += 1;
    ball[b].first += 1;


    if( check(id, ball ) ) return true; 

    ball[a].first -= 1;
    ball[b].first -= 1;

    //2. a win
    if(check_win(id, a, b, ball ) )  return true; 

    //3. b win
    if(check_win(id, b, a, ball ) ) return true; 
    
    return false;
}

int solve(  )
{
    for(int d = -63; d <  0; ++d) {
        add_a[d + 64] = 0;
        add_b[d + 64] = 3;
    }
    add_a[0 + 64] = 1;
    add_b[0 + 64] = 1;
    
    for(int d =1 ; d < 64; ++d ) {
        add_a[ d  + 64 ] = 3;
        add_b[d  +  64 ] = 0;
    }
    
    
    init_in();
    
    std::vector< pii > vec ;
    pii4 ball, ball_o ;

    memset(game, 0, sizeof(game));
    memset(pass, 0 ,sizeof(pass));
    memset(can, 0 ,sizeof(can));
 
    vec.clear();
    std::fill(ball.begin(), ball.end(), std::make_pair(0,0));
    ball_o = ball;

    int n ;
    
    //scanf("%d",&n);
    n = read_int();
   
    if (n <= 1)
    {
        std::fill(can, can + 24, true);
        print_ans( );
        return 0;
    }
    
    struct input_data{
        int a,b,c,d;
    }data[10] ;
    for(int i = 0; i < n; ++i){
        int a,b,c,d;
        
        //scanf("%d%d%d%d",&a,&b,&c,&d);
        a = read_int();
        b = read_int();
        c = read_int();
        d = read_int();
        
        data[i].a = a;
        data[i].b = b;
        data[i].c = c;
        data[i].d = d;
    }
  
    for(int i = 0; i < n; ++i){
        int mx = std::min(data[i].c,data[i].d);
        data[i].c -= mx;
        data[i].d -= mx;
        
         
    }
 

     
        //1 2 1 0
    for(int i = 0; i < n; ++i){    
        int a,b,c,d;
        a = data[i].a;
        b = data[i].b;
        c = data[i].c;
        d = data[i].d;
        
        --a,--b;
      
        
        game[a][b] = c    ;
        game[b][a] = d    ;
        
        pass[a][b] = true ;
        pass[b][a] = true ;
        
        if (c == d ) 
        {
            ball[a].first += 1;
            ball[b].first += 1;
        }
        else if (c>d)
        {
            ball[a].first += 3;
        } else {
            //c < d 
            ball[b].first += 3;
        }
        ball[a].second += c - d ;
        ball[b].second += d - c ;
    }
    
    const int M  = 50 ;
    
    if ( n == 6 ) 
    {
        for(int k = 0; k < 24; ++k) 
            can[k] = check(k, ball);
        
        print_ans( );
        return 0;
    }
     
    vec.clear();
    for(int i = 0; i < 4; ++i){
        for(int j = i + 1; j < 4; ++j){
            if (pass[i][j] ) continue;
             
            vec.push_back(std::make_pair(i,j));
        }
    }
   
  
    if( n == 5 ) 
    {
        int a =  vec[0].first, b = vec[0].second ;
        
        for(int k = 0; k < 24; ++k) 
        {
            can[k] = false;
        
            for(int d = -M; d <= M; ++d)
            {
                ball_o = ball;
                
                play( a, b, d , ball_o);
                if(check(k, ball_o)){
                    can[k] = true;
                    break;
                }
                
            }
            
           
        }
        
        print_ans();
        return 0;
         
    }
    
    if ( n == 4 ) 
    {

        for(int k = 0; k < 24; ++k)
        {
            can[k] = false;
            for(int d = -M; d <= M  ; ++d)
            {
                ball_o = ball;
                play(vec[0].first, vec[0].second , d , ball_o ) ;
                if (check_last(k, vec[1].first, vec[1].second, ball_o) ) {
                    can[k] = true;
                    break;
                }
            }
        }
        
        print_ans();
        return 0;
    }
    
    if (n == 3 ) 
    {
        int const M = 20;
        
        for(int k = 0; k < 24; ++k)
        {
            can[k] = false;
            
            int a = vec[2].first, b =vec[2].second;
            //1.  two are draw
            ball_o = ball;
            play(vec[0].first, vec[0].second, 0, ball_o);
            play(vec[1].first, vec[1].second, 0, ball_o);
            
            if (check_last(k, a, b, ball_o ) ) {
                can[k] = true;
                continue;
            }
            
            //2. one draw, second up
            for(int d = M; d >= 1; --d ) {
                ball_o = ball;
                play(vec[0].first, vec[0].second, 0, ball_o);
                play(vec[1].first, vec[1].second, d, ball_o);
                
                if (check_last(k, a,b, ball_o ) ){
                    can[k] = true;
                    break;
                }
                
                ball_o = ball;
                play(vec[0].first, vec[0].second, 0, ball_o);
                play(vec[1].second, vec[1].first, d, ball_o);
                
                if (check_last(k, a,b, ball_o ) ){
                    can[k] = true;
                    break;
                }
                
                //or second is draw
                ball_o = ball;
                play(vec[0].first, vec[0].second, d, ball_o);
                play(vec[1].first, vec[1].second, 0 , ball_o);
                
                 if (check_last(k, a,b, ball_o ) ){
                    can[k] = true;
                    break;
                }
                
                ball_o = ball;
                
                play(vec[0].second, vec[0].first, d, ball_o);
                play(vec[1].first, vec[1].second, 0 , ball_o);
                
                 if (check_last(k, a,b, ball_o ) ){
                    can[k] = true;
                    break;
                }
            }
            
            if (can[k]) continue;
            
            // both up
            for(int d1 = M; d1 >= 1; --d1){
                for(int d2 = M; d2 >= 1; --d2){
                    
                    ball_o = ball;
                
                    play(vec[0].first, vec[0].second, d1, ball_o);
                    play(vec[1].first, vec[1].second, d2 , ball_o);

                     if (check_last(k, a,b, ball_o ) ){
                        can[k] = true;
                        break;
                    }
                    
                    
                    ball_o = ball;
                
                    play(vec[0].second, vec[0].first, d1, ball_o);
                    play(vec[1].first, vec[1].second, d2 , ball_o);

                     if (check_last(k, a,b, ball_o ) ){
                        can[k] = true;
                        break;
                    }
                    
                    
                    
                    ball_o = ball;
                
                    play(vec[0].first, vec[0].second, d1, ball_o);
                    play(vec[1].second, vec[1].first, d2 , ball_o);

                     if (check_last(k, a,b, ball_o ) ){
                        can[k] = true;
                        break;
                    }
                    
                    
                    
                    ball_o = ball;
                
                    play(vec[0].second, vec[0].first, d1, ball_o);
                    play(vec[1].second, vec[1].first, d2 , ball_o);

                     if (check_last(k, a,b, ball_o ) ){
                        can[k] = true;
                        break;
                    }
                    
                    
                }
            }
            
         }//end for k = 0..24
         
        // fprintf(stderr, "loop = %d\n", loop ) ;
         print_ans();   
         return 0;
    }
    
    
    if ( n == 2 ) 
    {
   
        int max_pass = 0;
        for(int i= 0; i < 4; ++i){
            int ps = 0;
            for(int j = 0; j < 4; ++j){
                if ( i != j && pass[i][j] ) {
                    ++ps;
                } 
            }
            if(ps > max_pass)
                max_pass = ps;
        }
        
        if (  max_pass < 2 ) {
            
            bool has_draw = false;
            for(int i = 0; i < 4; ++i){
                for(int j = 0; j < 4; ++j){
                    if (i != j && pass[i][j] ) {
                        if (game[i][j]==game[j][i]) has_draw = true;
                    }
                }
            }
            
            if (  has_draw ) {
                std::fill(can, can + 24, true);
                print_ans( );
                return 0;
            }
            
            int p[4] = {0,1,2,3};
            //sort
            
            for(int i = 0; i < 4; ++i){
                for(int j = i + 1; j < 4; ++j){
                    if (ball[ p[i] ] < ball[ p[j] ]   ){
                        std::swap(p[i], p[j]);
                    }
                }
            }

            if(ball[p[0]].second != ball[p[1]].second ) {
                // last is p[0]  previous is p[1] 
                int p_a =  -1;//(pass[p[0]][p[2]]) ? p[2] : p[3];
                int p_b =  -1;//(pass[p[1]][p[2]]) ? p[2] : p[3];
                for(int j = 0; j < 4; ++j){
                    if(j != p[0] && pass[p[0]][j] ) p_a = j;
                    if (j!=p[1] && pass[p[1]][j] ) p_b = j;
                }
                std::fill(can,can+24,true);
                for(int k = 0; k < 24; ++k){
                    if (P[k][0] == p_a && P[k][1] == p_b && P[k][3] == p[0] && P[k][2] == p[1] ) 
                        can[k] = false;
                }
            }else {
                std::fill(can,can+24,true);
            }
            print_ans( );
            return 0;
        }
        
        
       
        int free_id = -1;
        for(int i = 0; i < 4; ++i){
            int ps = 0;
            for(int j = 0; j< 4; ++j){
                if (i != j && pass[i][j]) ++ps;
            }
            if ( ps == 0  ) free_id = i;
        }
        
        
        for(int i = 0; i < 4; ++i)
        {
            int ps = 0;
            for(int j = 0; j < 4; ++j) if (i != j && pass[i][j] ) ++ps; 
            if (ps != 2 ) continue;
            
            bool all_win = true;
            bool all_lost = true;
            for(int j = 0; j <4; ++j) if(i != j && pass[i][j] ) {
                all_win = all_win && game[i][j] > game[j][i];
                all_lost = all_lost && game[i][j] < game[j][i];
            }
            
            if( all_win ) 
            {
                for(int k = 0; k < 24; ++k){
                    can[k] = true;
                    if (P[k][3] == i || (P[k][2] == i && P[k][3] == free_id ) )
                    {
                        can[k] = false;
                    }
                }
                
                print_ans( );
                return 0;
            }
            
            if ( all_lost ) 
            {
                for(int k = 0; k < 24; ++k)
                {
                    can[k] = true;
                    if (P[k][0] == i || (P[k][1] == i && P[k][0] == free_id ) ) 
                    {
                        can[k] = false;
                    }
                }
                
                print_ans( );
                return 0;
            }

             
          
            std::fill(can, can + 24, true);
            print_ans( );
            return 0;

        }
         
    }
     
    return 0;
}
 
int main(int argc, char* argv[])
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif //ONLINE_JUDGE
     solve();
    
}
