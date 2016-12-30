

// 1075. Thread in a Space
// A , B, and C , R 
// find shortest path from A to B, no intersect with sphera with center C, radius R.
#include <cstdio>
#include <cmath>

char in[1024];
char const* o;
void init_in()
{
    o = in;
    in[fread(in,1,sizeof(in)-4, stdin)] = 0;
}
int readInt()
{
    unsigned u = 0, s= 0;
    while(*o && *o <= 32)++o;
    if (*o == '-') s = ~0, ++o; else if (*o == '+')++o;
    while(*o >= 48 && *o <= 57) u = (u << 3) + (u << 1) + (*o++ - 48);
    return static_cast<int>((u ^ s) + !!s);
}

struct point
{
    double x, y, z;
};
static 
double dist(point a, point b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double dz = a.z - b.z;
    
    return sqrt(fabs(dx*dx + dy*dy+dz*dz));
}




int main()
{
    
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    init_in();
    point a,b,c;
    double radius;
    int ax,ay,az,bx,by,bz,cx,cy,cz,r;
    ax = readInt();
    ay = readInt();
    az = readInt();
    
    bx = readInt();
    by = readInt();
    bz = readInt();
    
    cx = readInt();
    cy = readInt();
    cz = readInt();
    
    r = readInt();
    
    //scanf("%d%d%d%d%d%d%d%d%d%d",&ax,&ay,&az,&bx,&by,&bz,&cx,&cy,&cz,&r);
    a.x = ax;
    a.y = ay;
    a.z = az;
    
    b.x = bx;
    b.y = by;
    b.z = bz;
    
    c.x = cx;
    c.y = cy;
    c.z = cz;
    
    radius = r;
    double answer ;
    double AB = dist(a,b);
    double AC = dist(a,c);
    double BC = dist(b,c);
    double alpha = acos((AC*AC + BC*BC - AB*AB)/(2*AC*BC)) - acos(radius/AC) - acos(radius/BC);
    if ( alpha < 0)
    {
        answer = AB;
        //printf("%.2f\n",AB);
    }
    else
    {
        answer = 
                sqrt(AC*AC - radius*radius)
                +sqrt(BC*BC - radius * radius)
                +radius * (alpha);
    }
    
    //write answer
    {
        unsigned u;
        char *w = in + 1024;
        *--w = '\n';
        answer += 0.005;
        
        u = (answer * 100);
        
        *--w = u % 10 + '0'; u/=10;
        *--w = u % 10 + '0'; u/=10;
        *--w = '.';
        do *--w = u % 10 + '0'; while(u/=10);
        
        fwrite(w, 1, in + 1024 - w, stdout);
    }
    
    return 0;
}
