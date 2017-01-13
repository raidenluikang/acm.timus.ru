// 1170. Desert


#include <cstdio>
#include <cmath>

void judge_assert(bool b){ if (!b)printf("%d\n",1/b);}

const char* o;
char in[65536*2];

int readInt()
{
    int u = 0;
    while(*o && *o <= 32)++o;
    while(* o >='0' && *o<='9') u = (u << 3) + (u << 1) + (*o++ - '0');
    return u;
}
struct pt
{
    double x,y;
    pt():x(),y(){}
    pt(double x, double y):x(x),y(y){}
};
bool operator < (pt const& a, pt const& b){ return a.x < b.x || (a.x == b.x && a.y < b.y); }
pt operator - (pt const& a, pt const& b)
{
    pt c; // = {a.x - b.x, a.y - b.y};
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return c;
}

double dist(pt p)
{
    using std::sqrt;
    
    double x2 =  (p.x * p.x);
    double y2 =  (p.y * p.y);
    
    return sqrt(x2 + y2);
}

struct rect
{
    pt a;
    pt b;
    double lazy;
};

bool operator < (rect const& l, rect const& r){ return l.a < r.a; }


int n;
double  lazy_0, len;
rect  r[512];
pt p_ans;
double ans;
bool ans_changed;

static const double EPS = 1.0E-12;

void solve(pt p)
{
    pt qa, qb;
    double tt = 0, l_0 = len;
    double coef = p.x / p.y;
    double coef_inv = p.y / p.x; 
    
    for (unsigned i = 0; i < n; ++ i)
    {
        
        double TX1 =  r[i].a.y * coef; //p. x * r[i]. a. y / p. y;
        double TY1 =  r[i].a.x * coef_inv;//p. y * r[i]. a. x / p. x;
        double TX2 =  r[i].b.y * coef;//p. x * r[i]. b. y / p. y;
        double TY2 =  r[i].b.x * coef_inv;//p. y * r[i]. b. x / p. x;

        if (TY1 < r[i]. a. y )
        {
            qa. x = TX1;
            qa. y = r[i] . a. y;
        }
        else {
            qa. x = r[i]. a. x;
            qa. y = TY1;
        }
        if (TY2 < r[i]. b. y  )
        {
            qb. x = r[i]. b. x;
            qb. y = TY2;
        }
        else {
            qb. x = TX2;
            qb. y = r[i]. b. y;
        }
        
        if (qa. x < qb. x )
        {
            double dp =  dist(qa - qb);
            tt  += dp * r[ i ]. lazy;
            l_0 -= dp;
        }
    }

    tt += l_0 * lazy_0;

    if (tt < ans )
    {
        ans = tt;
        p_ans = p;
        
        ans_changed = true;
    }
}


int main()
{
    
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif 
    
    o = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    
    n = readInt();
    for(int i = 0; i != n; ++i)
    {
        r[i].a.x = readInt();
        r[i].a.y = readInt();
        
        r[i].b.x = readInt();
        r[i].b.y = readInt();
        
        r[i].lazy = readInt();
    }
    
    lazy_0 = readInt();
    len = readInt();
    
    p_ans .x = 0;
    p_ans .y = len;
    ans = len * lazy_0;
    ans_changed = false;
    for(int i = 0; i != n; ++i)
    {
        pt p;
        solve( r[i].a );
        solve( r[i].b );
        
        p.x = r[i].a.x;
        p.y = r[i].b.y;
        
        solve(p);
        
        p.x = r[i].b.x;
        p.y = r[i].a.y;
        
        solve(p);
    }
    
    {
        if (ans_changed)
        {
            double dp = dist( p_ans );
            p_ans.x *= len / dp;
            p_ans.y *= len / dp;
        }
        else 
        {
            // x = 1   y   1+y^2 = L^2 --> 
            
            p_ans.x = 0.003;
            p_ans.y = sqrt(len * len - p_ans.x * p_ans.x);
        }
        
        printf("%.6f\n%.6f %.6f\n",ans,p_ans.x, p_ans.y);
    }
}
 
