
// acm.timus.ru 1003 Parity. DSU algo.
 
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>

#ifdef _MSC_VER

#define JUDGE_ALIGN64_OFFSET  __declspec(align(64))
#define JUDGE_ALIGN64_SUFFIX     

#else

#define JUDGE_ALIGN64_OFFSET   
#define JUDGE_ALIGN64_SUFFIX  __attribute__((aligned(8)))

#endif 


JUDGE_ALIGN64_OFFSET
char buffer[ 1 << 19] JUDGE_ALIGN64_SUFFIX;
char const*o;
char * w;

struct DSU
{
	unsigned p[10005];
	unsigned rank[10005];
	bool d[10005];
	
	void add_(unsigned x)
	{
		p[x] = x;
		rank[x] = 0;
		d[x] = false;
	} 
    unsigned find_(unsigned x)
    {
		if (p[x] != x)
		{
			unsigned t= p[x];
			p[x] = find_(t);
			d[x] ^= d[t];
		}
		return p[x];
	}
	
	void union_(unsigned u, unsigned v, bool odd)
	{
		unsigned pu = find_(u), pv = find_(v);
		
		if (rank[pu] < rank[pv])
		{
			p[pu] = pv;
			d[pu] = odd ^  d[u]  ^  d[v] ;
		}
		else
		{
			p[pv] = pu;
			d[pv] = odd ^ d[u] ^ d[v];
			if (rank[u] == rank[v])++rank[u];
		}
	}
	
	 	
};



DSU dsu;
 
int solve()
{
	typedef std::map<unsigned, unsigned> map_type;
	typedef map_type::const_iterator citerator;
	unsigned n, len, l, r;
	map_type id; 
	//1. read whole file
	n = fread(buffer, 1, sizeof(buffer)-1, stdin);
	buffer[n]  = '\0';
	
	o = w = buffer;
	
	while(true)
	{
		//1. read length of sequence.
		len = 0;
		while(*o && *o <= 32)++o;
		
		// reach end, break
		if (o[0] == '-' || o[0] == 0)
		  break;
		
		while(*o>='0') len = (len << 3) + (len << 1) + *o++ -'0';
		
		//2. read number of queries.
		n = 0;
		while(*o && *o <= 32)++o;
		while(*o >='0') n = (n<<3) + (n<<1) + *o ++  -'0';
		
		//3. read queries
		unsigned ans = 0, cont = 0;
		bool valid = true;
		
		id.clear();
		for(unsigned i = 0; i != n; ++i)
		{
			//3.1  left position
			l = 0;
			while(*o && *o <= 32)++o;
			while(*o >='0') l = (l<<3) + (l<<1) + *o++ -'0';
			
			//3.2  right position
			r = 0;
			while(*o && *o <= 32)++o;
			while(*o >= '0') r = (r<<3) + (r<<1) + *o++ -'0';
			
			//3.3 odd | even
			bool odd;
			while(*o <= 32)++o;
			odd = o[0] == 'o';
			while(*o >= 'a')++o;
			
			if (!valid)continue;
			
			unsigned u = l-1, v = r;
			
			citerator u_it = id.find(u);
			if(u_it == id.end())
			{
				//++cont;
				dsu.add_( cont );
				id.insert( std::make_pair(u, cont ) );
				u = cont++;
			}
			else
			{
				u = (*u_it).second;
			}
			
			
			citerator v_it = id.find(v);		
			if(v_it == id.end())
			{
				//++cont;
				dsu.add_(cont);
				id.insert( std::make_pair(v, cont));
				v = cont++;
			}
			else
			{
				v = (*v_it).second;
			}
			
			
			unsigned pu = dsu.find_(u); 
			unsigned pv = dsu.find_(v);
			
			if(pu == pv && ( dsu.d[u]  ^ dsu.d[ v ] ^ odd ) ) valid = false;
			else if(pu != pv) dsu.union_( u, v, odd);
			
			if(valid) ++ans;
		}
		
		//if (!ok)//satisfy all queries
		{
			unsigned u = ans, v = ans, vn = 0;
			do vn++; while(v/=10);
			v = vn;
			while(vn-->0)w[vn] = u%10 + '0', u/=10;
			w += v;
			*w++ = '\n';
		}
	}
	
	if (w != buffer)
	{
		fwrite(buffer, 1, w - buffer, stdout);
	}
	
	return 0;
}

int main()
{
	
 #ifndef ONLINE_JUDGE
      freopen("input.txt","r",stdin);
      freopen("output.txt","w",stdout);
 #endif 
 
   solve();
   return 0;
}  
