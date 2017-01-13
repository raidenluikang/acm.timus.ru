
#include <cstdio>

int solve()
{
    unsigned n = 0;
    scanf("%u",&n); 
   // F[1] = 2
    // F[2] = 2
    // F[3] = 010   101  021  120 : 4
    // F[4] = 0101  1010  0210  1201  0120  1021  : 6
    // F[5] = 2 + 3*2 = 8
    // F[6] = 2 + 4*2 = 10
    // G[n][0] - oq bilan boshlanadiganlar soni
    // G[n][1] = qizil bilan boshlanadiganlar soni
    // G[n][0] = G[n-1][1] + G[n-2][1]
    // G[n][1] = G[n-1][0] + G[n-2][0] 

      // G[n][1] + G[n][0] = (G[n-1][1] + G[n-1][0]) + G[n-2][1] + G[n-2][0]
      // F[n] = F[n-1] + F[n-2]
      // F[1] = 2
      // F[2] = 2
      // F[3] = 4
      // F[5] = 6
      // F[6] = 10
      unsigned F[64];
      F[0] = 0;
      F[1] = 2;
      for(unsigned i = 2; i != 64; ++i)
        F[i] = F[i-1] + F[i-2];

      printf("%u\n",F[n]);    
     return 0;
}

int main(int argc, char * argv[]) 
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    
    solve();
    
    return 0;
}
