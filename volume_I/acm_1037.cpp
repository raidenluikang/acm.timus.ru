

// author: c_pp
// acm.timus.ru 1037. Memory Management

// memory block 1..N   N = 30 000
// timeout T = 10 minutes = 600 seconds.
// Time <= 65 000 
// number of queries <= 80 000

// <Time> +   -- allocate a memory least number free block. 
// <Time> . <block number>  -- access to block 

#include <cstdio>

static const unsigned N        = 32768;
static const unsigned TimeOut  = 600;
static const unsigned MaxTime  = 65000 + TimeOut + 8; // +8 for extra time 
static const unsigned MaxQuery = 80008;

char in[ (1 << 20) + (1 << 19) ]; // MaxQuery * line_symbols , line_symbols = 5 + 4 + 5 = 14.  80 000 * 14 = 1 120 000 

const char* o;
char * w;

void init_in()
{
    unsigned n;
    o = w = in + (1<<18);
    n = fread(w, 1, sizeof( in ) - ( 1 << 18) - 4, stdin);
    w[n] = '\0';

    w = in;//write from in 
    // read from in[1<<18].
}

void writeChar(char c)
{ 
    *w++ = c;
}

void writeInt(unsigned u)
{
    unsigned v = u, n = 0;
    do n++; while(v/=10);
    v = n;
    while(v-->0)w[v] = u%10 + '0', u/=10;
    w += n;
}

struct request 
{
    unsigned int t;//time 
    unsigned int b; // block number 
    unsigned int type;//type of request : 1 - <Time> + --> allocated , 2  - <Time> . <blockNum> --> access request
};

bool readRequest(request& q)
{
    q.t = 0;
    q.b = 0;
    q.type = 0;
    
    while(*o && *o <= 32)++o;

    if (*o >= 48)
    {
        q.t = *o++ - 48;
        while(*o >= 48) q.t = (q.t << 3) + (q.t << 1) + *o ++ - 48;

        ++q.t; // increase time by one, means that the time starts from 1. 
    
        ++o; // skip whitespace 
        q.type = (*o == '+') ? 1 : (*o == '.') ? 2 : 0;
        ++o;//skip '+' or '.' symbol
        if (q.type == 2)
        {
            ++o; // skip whitespace
            while(*o >= 48) q.b = (q.b << 3) + (q.b << 1) + *o ++ - 48;
        }
        if (*o == '\n')++o;//skip line break.
        return true;
    }
    else
    {
        return false;
    }
}


struct block
{
    unsigned int timeout ; // timeout  when it will be freed.
    unsigned int id_task ; // id time task , id_task >= 1, valid value.  id_task = 0 - there no task.
};

struct time_task
{
    unsigned int timeout ; // time out when it will be freed.
    unsigned int id_block; // block id 
};

unsigned int busy_blocks[ N + N ] = {};
block blocks[ N ] = {};
time_task tasks[ MaxQuery ] = {};
unsigned int task_head, task_tail;

void add_task(unsigned int b_id)
{
    ++task_tail;
    
    blocks[ b_id ].id_task = task_tail;

    tasks[ task_tail ].timeout = blocks[b_id].timeout;
    
    tasks[ task_tail ].id_block = b_id;
}

void free_tasks(unsigned int curr_time)
{
    while(task_head < task_tail && tasks[task_head + 1].timeout <= curr_time )
    {
        ++task_head;

        // Note that: id_block = 0 --> means that this task was invalidated.
        if (const unsigned int id = tasks[ task_head ].id_block )
        {
            blocks[ id ].id_task = 0; // freed.
            for(unsigned int p = id + N; p > 0; p >>= 1)
            {
                busy_blocks[ p ]--;
            }
        }
    } 
}

unsigned int allocate_block(unsigned int curr_time)
{
    free_tasks(curr_time);
    unsigned int p = 1 + N;
    unsigned int h = 1;
    while(p > 0 && busy_blocks[p] == h )
    {
        p >>= 1;
        h <<= 1;
    }

    // busy_blocks[p] < h     
    while(p < N )
    {
        p <<= 1;
        h >>= 1;
        if (busy_blocks[ p ] == h)
        {
             ++p;
        }
    }
    unsigned int result = p - N;
 
    blocks[ result ].timeout = curr_time + TimeOut;
 
    add_task(result);
    
    for( ; p > 0; p >>= 1) 
        busy_blocks[ p ] ++;
    
    return result;
}

bool access_block(unsigned int block_id, unsigned int curr_time)
{
    free_tasks( curr_time );

    if (unsigned int id = blocks[ block_id ].id_task)
    {
        tasks[ id ].id_block = 0; // invalidated it.
        
        // add a new task 
        blocks[ block_id ].timeout = curr_time + TimeOut;
        
        add_task( block_id ); 

        return true;
    }
     
    return false ;
}

int solve()
{
    init_in();
    request q;
    task_head = task_tail = 0;
    

    // 0 - block always busy.
    for(unsigned int p = N + 0; p > 0; p>>=1)
       busy_blocks[ p ]++;

    while(readRequest(q))
    {
        if (q.type == 1) // allocate 
        {
            unsigned int block_id = allocate_block( q.t );
            writeInt(block_id);
            writeChar('\n');
        }
        else 
        {
            bool b = access_block(q.b, q.t);
            writeChar( "-+"[ b ] );
            writeChar( '\n' );
        }
    }

    //flush output
    fwrite(in, 1, w - in, stdout);
    return 0;
}

int main(int argc, char* argv[])
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    solve();
    return 0;
}
