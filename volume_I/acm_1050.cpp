

// acm.timus.ru 1050. Preparing an Article

#include <cstdio>

static const unsigned N_LINES   = 250;
static const unsigned N_SYMBOLS = 80;

char in[65536]; // N_LINES* N_SYMBOLS  = 250 * 80 = 20000 < 2^16
char out[65536];
const char*o;
char *w; 

void init_in()
{
    w = out;
    o = in;

    in[ fread(in,1,sizeof(in)-4, stdin)] = 0;
}

char peekChar(){return *o;}
char nextChar(){return *o++;}
bool is_alpha(char c){ return (c >= 'a' && c <= 'z') || (c >= 'A' && c <='Z') ; }

int solve()
{
    init_in();
    const char* p = o;
    bool open = false;
    for( ; *o ; ++o)
    {
        char c = *o;
        switch(c)
        {
            case '\"': 
            {
                if (!open)
                {
                    while(p < o) *w++ = *p++;
                    open = true;
                }
                else 
                {
                    // p = indicated opened quot 
                    *w++ = '`';
                    *w++ = '`';
                    ++p; // skip quot 
                    while(p < o)*w++ = *p++;
                    ++p; 
                    *w++ = '\'';
                    *w++ = '\'';

                    open = false;
                } 
            }
            break;
            case '\\': 
            {
                // skip next symbol 
                ++o;

                //check if this command \par or not 
                if (o[0] == 'p' && o[1] == 'a' && o[2] == 'r' && !is_alpha(o[3]))
                {
                    o += 2;
                    if (*p == '\"' && open)
                    {
                         ++p; // skip quate symbol.
                    }
                    open = false;
                    while(p < o) *w++ = *p++;
                }
            }
            break;
            case '\n': // line break
            {
                if ( o[ 1 ] == '\n') //end paragraph
                {
                    o++; // skip first line break.
                    
                    if (*p == '\"' && open )
                        ++p; // skip it 
                    open = false;
                    while(p < o) 
                        *w++ = *p++;
                }
            }
            break;
        }
    }

    if (*p == '\"' && open) ++p, open =false;
    while( p < o ) 
        *w++ = *p++;
    
    fwrite(out, 1, w - out, stdout);

    return 0;
}

int main(int argc, char* argv[])
{
 #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w", stdout);
 #endif

    solve();
    
    return 0;
}
