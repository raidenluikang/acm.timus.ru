//onst a:array['0'..'9'] of longint=(0,1,2,3,2,1,2,3,4,2);

#include <cstdio>
static const int a[10] = {0,1,2,3,2,1,2,3,4,2};

char s[2048];
int solve()
{
    int n, ans = 0;
    n = fread(s,1,sizeof(s)-4,stdin);
    for(int i = 0; i < n && s[i]>='0' && s[i]<='9'; ++i)
        ans += a[s[i] - '0'];
    printf("%d\n",ans);
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
