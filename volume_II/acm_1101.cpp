#include <stdio.h>
#include <string.h>

static 
bool letter(char x){ return x >='A' && x <= 'Z';}

static 
bool digit(char x){ return x == '1' || x == '0';}

static 
bool op(char x){ return x == '!' || x == '&' || x == '|' ;}

static
bool  qt(char x){ return x == '(' || x == ')'; }

unsigned int reg = 0;

int reform(char *line)
{
    int i = 0;
    char *p = 0;

    for(i = 0, p = line; *p != 0; p++)
    {
            if( p[0] == 'N' && p[1] == 'O' &&  p[2] == 'T')
            {
                     //p[0] = '!';  p[1] = ' ';  p[2]  = ' ';
                    line[i++] = '!';
                    p += 2;
            }
            else if( p[0] == 'A' &&  p[1] == 'N' &&  p[2] == 'D')
            {
                    //*p = '&'; *(p+1) = ' '; *(p+2) = ' ';
                    line[i++] = '&';
                    p += 2;
            }
            else if( p[0] == 'O' &&  p[1] == 'R')
            {
                    //*p = '|'; *(p+1) = ' '; *(p+2) = ' ';
                    line[i++] = '|';
                    p += 1;
            }
            else if( p[0] == 'T' &&  p[1] == 'R' &&  p[2] == 'U' &&  p[3] == 'E')
            {
                    //*p = '1'; *(p+1) = ' '; *(p+2) = ' '; *(p+3) = ' ';
                    line[i++] = '1';
                    p += 3;
            }
            else if( p[0] == 'F' &&  p[1] == 'A' &&  p[2] == 'L' &&  p[3] == 'S' &&  p[4] == 'E')
            {
                    //*p = '0'; *(p+1) = ' '; *(p+2) = ' '; *(p+3) = ' '; *(p+4) = ' ';
                    line[i++] = '0';
                    p += 4;
            } 
            else if ( *p !=' ')
            {
                line[i++] = *p;
            }
    }
    line[ i ] = 0;
    //printf("line: %s\n",line);
    return i;
}

char exp[200], szexp ;
char o[200];
void construct(char *line)
{
    char *p = 0, pos = 0;

    for(p = line; *p != 0; p++)
    {
        
        if( op( * p ) ) // &, !, |
        {
                while(pos > 0)
                {
                        if( !qt( o [ pos - 1 ] ) && o[ pos - 1 ] < *p) 
                            exp[ szexp++ ] = o[ --pos ];
                        else 
                            break;
                }
                o[pos++] = *p;
        }
        else if(digit(*p) || letter( *p ) )
        {
            exp[ szexp++] = *p;
        
        }
        else if(*p == '(')
        {
            o[pos++] = *p;
        }
        else if(*p == ')')
        {
            while(o[pos-1] != '(' )	
                    exp[szexp++] = o[--pos];
                pos--;
        }
    }
    while(pos > 0) exp[szexp++] = o[--pos];
}

int get_reg(int a)
{
	return (reg & (1u << a)) > 0 ? 1 : 0;
}

void reverse_reg(int a)
{
	//if((reg & (1 << a)) == 0) reg |= (1 << a);
	//else reg &= ~(1 << a);
    reg ^= 1u << a;
}


int eval()
{
    static
    int x[200];
    char *p ;
    int pos = 0;
    for(p = exp + szexp - 1; p >= exp; p--)
    {
        if(p >= exp)
        {
            if(op(*p)) x[pos++] = *p;
            else if(letter(*p)) x[pos++] = get_reg(*p - 0x40);
            else if(digit(*p)) x[pos++] = *p - 0x30;
        }

        while(pos > 1)
        {
            if(op(x[pos-1])) break;

            if(x[pos-2] == '!')
            {
                x[pos-2] = !x[pos-1];//(x[pos-1] == 0) ? 1 : 0;
                pos -= 1;
                continue;
            }

            if(pos < 3) break;

            if( op(x[pos-3]) && !op(x[pos-2]) && !op( x[ pos - 1 ] ) )
            {
                if(x[pos-3] == '&') 
                    x[pos-3] = x[pos-2] & x[pos-1];
                else if(x[pos-3] == '|') 
                    x[pos-3] = x[pos-2] | x[pos-1];
                //x[pos-3] = (x[pos-3] > 0) ? 1 : 0;
                pos -= 2;
                continue;
            }
            break;
        }
        if(p < exp && pos == 1) break;
    }

    return !!x[0];
}

int n = 0, m = 0, k = 0, len = 0;
int dx = 0, dy = 0, tx = 0, ty = 0;
char line[300] = "", c = 0;
unsigned char rip[202][202];
int i = 0, x = 0, y = 0;

char in[65536];
void readData()
{
    const char*o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    i = 0;
    for( ; *o  != '\n'; ++i)
        line[i] = *o++;
    ++o;
    
    while(*o && *o <= 32)++o;
    while(*o >= '0' && *o <= '9') n = ( n << 3) + (n << 1) + (*o++ - 48);
    while(*o && *o <= 32)++o;
    while(*o >= '0' && *o <= '9') m = (m << 3) + ( m << 1) + (*o ++ - 48);
    while(*o && *o <= 32)++o;
    while(*o >= '0' && *o <= '9') k = (k << 3) + (k << 1 ) + (*o ++ - 48);
    
    for(i = 0; i < m; i++)
    {
           // scanf("%d %d\n", &x, &y);
        x = 0;
        y = 0;
        {
            unsigned u = 0, s = 0;
            while(*o && *o <= 32)++o;
            if (*o == '-')s = ~0, ++o; else if (*o == '+')++o;
            while(*o >='0' && *o <='9') u = (u << 3) + (u << 1) + (*o++ - 48);
            
            x = (u^s) + !!s;
            
            u = s = 0;
            while(*o && *o <= 32)++o;
            if (*o == '-')s = ~0, ++o; else if (*o == '+')++o;
            while(*o >='0' && *o <='9') u = (u << 3) + (u << 1) + (*o++ - 48);
            
            y = (u ^ s) + !!s;
        }
        x += n; y += n;
        rip[x][y] = 0xFF;
    }
    for(i = 0; i < k; i++)
    {
           // scanf("%d %d %c\n", &x, &y, &c);
        x = 0;
        y = 0;
        {
            unsigned u = 0, s = 0;
            while(*o && *o <= 32)++o;
            if (*o == '-')s = ~0, ++o; else if (*o == '+')++o;
            while(*o >='0' && *o <='9') u = (u << 3) + (u << 1) + (*o++ - 48);
            
            x = (u^s) + !!s;
            
            u = s = 0;
            while(*o && *o <= 32)++o;
            if (*o == '-')s = ~0, ++o; else if (*o == '+')++o;
            while(*o >='0' && *o <='9') u = (u << 3) + (u << 1) + (*o++ - 48);
            
            y = (u ^ s) + !!s;
            
            while(*o && *o <= 32)++o;
            
            c = *o++ ;
        }    
        
        x += n; y += n;
        rip[x][y] = c - 0x40;
    }
    
}

char* writeInt(char* w, int x)
{
    unsigned u,v,n=0;
    if (x < 0){
        *w++ = '-';
        x = -x;
    }
    u = x;
    do ++n; while(u/=10);
    v = x;
    u = n;
    while(u-->0)w[u] = v %10 + '0', v/=10;
    w += n;
    return w;
}
int main()
{
    char * w  = in;
    
    memset(rip, 0, sizeof(rip));

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    readData();
    //fgets(line, 256, stdin);
    len = reform(line);
    //printf("%sn", line);
    construct(line);
    //printf("%sn", exp);



    x = n; y = n;
    dx = 1; dy = 0;
    while(1)
    {
        if(x < 0 || x > 2*n || y < 0 || y > 2*n) break;
        //printf("%d %d\n", x-n, y-n);
        w = writeInt(w, x-n);
        *w++ = ' ';
        w = writeInt(w, y - n);
        *w++ = '\n';
        /* fork */
        if(rip[x][y] == 0xFF)
        {
            tx = dx; ty = dy;
            if(eval()){
                /* right */
                dx = (dx == 0) ? ty : 0;
                dy = (dy == 0) ? -1*tx : 0;
            } else {
                /* left */
                dx = (dx == 0) ? -1*ty : 0;
                dy = (dy == 0) ? tx : 0;
            }
        }
        /* rip */
        else if(rip[x][y] != 0) reverse_reg(rip[x][y]);

        x += dx; y += dy;
    }
    if(w != in)fwrite(in,1,w-in,stdout);
    return 0;
}
