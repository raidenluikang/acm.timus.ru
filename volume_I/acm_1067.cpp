/* 
 * File:   main.cpp
 * Author: asus
 *
 * Created on December 29, 2016, 8:36 PM
 * 
 * acm.timus.ru 
 * 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>

static const int N      = 500;
static const int LEN    = 84;
static const int ALPHA  = 128; // 0..128 alphabet size 



// 500 * 80 = 5000 * 8 = 40 000
char in[1<<20];
char const* o;
char * w;

#if 1
#ifdef _MSC_VER
__declspec(align(64))
   char buf[ 1 << 20 ];
#else 
   char buf[1<<20] __attribute__((aligned(8)));
#endif

char * pb;

template<typename T>
struct my_allocator  
{
typedef T        value_type;
       typedef T*       pointer;
       typedef const T* const_pointer;
       typedef T&       reference;
       typedef const T& const_reference;
       typedef std::size_t    size_type;
       typedef std::ptrdiff_t difference_type;
    
    template<typename U> struct rebind{ typedef my_allocator<U> other; };
    
    my_allocator()throw(){}
    
    my_allocator(my_allocator const& a)throw()  {}
    
    template<typename U>
    my_allocator(my_allocator<U> const& a)throw() {}
    
    ~my_allocator()throw(){}
    
    // return address of values
     pointer address (reference value) const {
         return &value;
     }
     const_pointer address (const_reference value) const {
         return &value;
     }
    // return maximum number of elements that can be allocated
    size_type max_size () const throw() {
        return sizeof(buf)/sizeof(T);
    }
    pointer allocate(std::size_t n, const void* hint = 0)
    {
        pointer result =  reinterpret_cast< pointer >( pb );
        pb += sizeof(T);
        return result;
    }
    
     void construct (pointer p, const T& value) {
           // initialize memory with placement new
           new((void*)p)T(value);
       }
    
    void destroy(T* p)
    {
        p->~T();
    }
    
    void deallocate(pointer , std::size_t){}
    
    
    
};
   template <class T1, class T2>
   bool operator== (const my_allocator<T1>&,
                    const my_allocator<T2>&) throw() {
       return true;
   }
   template <class T1, class T2>
   bool operator!= (const my_allocator<T1>&,
                    const my_allocator<T2>&) throw() {
       return false;
   }
#endif
   
#if 1
struct word
{
    char s[ 8 ];
};
bool operator < (word const& lhs, word const& rhs) 
    {
        return memcmp(lhs.s, rhs.s, 8) < 0;
    }
struct word_less
{
    bool operator()(word const& lhs, word const& rhs)const
    {
        return memcmp(lhs.s, rhs.s, 8) < 0;
    }
};
#endif
//typedef std::string word;

int n;
struct file_tree
{
    typedef std::map< word, file_tree, word_less, my_allocator< std::pair<const word, file_tree> > > map_type;
    //typedef std::map< word, file_tree> map_type;
    
    map_type t;
    
    //added to current tree and return a new or existing tree
    file_tree & add_word(word const& w)
    {
        return t[ w ];
    }
    
    void print_all(int tab)
    {
        typedef map_type::iterator it;
        for(it b = t.begin(), e = t.end(); b != e; ++b)
        {
            word d = (*b).first;
            
            
            for(int i= 0;i != tab; ++i)
            // printf(" ");//  
            *w++ = ' ';
            
            //printf("%s\n",d.c_str());
            for(int i= 0; i != 8 && d.s[i] != 0 ; ++i)
                *w++ = d.s[ i ];
            *w++ = '\n';
            
            (*b).second.print_all( tab + 1 );
        }
    }
}ft;



int solve()
{
    pb = buf;
     o = w = in;
    in[fread(in,1,sizeof(in)-4,stdin)] = 0;
    
    n = 0;
    //scanf("%d\n",&n);
    while(*o && *o <= 32)++o;
    while(*o >= 48 && *o <= 57) n = (n << 3) + (n << 1) + (*o++ - 48);
    
    while(*o && *o != '\n')++o;
    ++o;
    
    for( int i = 0; i != n; ++i)
    {
        file_tree* root = &ft;
        word d = {};
        int k = 0;
        for( ; *o != '\n'; )
        {
            if (*o != '\\')d.s[k++] += *o++;
            else {
                if (k != 0)root = &(root->add_word(d));
                d.s[0] = d.s[1] = d.s[2] = d.s[3] = d.s[4] = d.s[5] = d.s[6] = d.s[7] = 0;
                k = 0;
                ++o;
            }
        }
        //scanf("%s\n",lw);
       // for(int k= 0; lw[k]; ++k)
       // {
        //    if (lw[k] != '\\')d+=lw[k];
        //    else {
        //        if (!d.empty())root = &(root->add_word(d));
        //        d.clear();
        //    }
       // }
        if (k != 0)root->add_word(d);
       ++o;
    }
    
    ft.print_all(0);
    
    fwrite(in, 1, w - in, stdout);
    return 0;
}


int main(int argc, char** argv) {

#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    solve();
    return 0;
}

