#include <time.h>
#include <algorithm>
#include <cstdio>


struct Treap{
       int Key , Prior;
       int Size , Min;
       Treap *Left , *Right;
};

typedef Treap * item;
const int inf = (int)1e9;

int count_nodes (item t){
    return t == NULL ? 0 : t->Size;
}

int MinInSubtree (item t){
    return t == NULL ? inf : t->Min;
}

void Update (item &t){
    if (t != NULL){
        t->Size = count_nodes (t->Left) + count_nodes (t->Right) + 1;
        t->Min = std::min( std::min(MinInSubtree (t->Left) , MinInSubtree (t->Right)) , t->Key );
    }
}

void Merge (item &t , item l , item r){
    if (l == NULL || r == NULL) 
        t = l == NULL ? r : l;
    else if (l->Prior < r->Prior) 
        Merge (r->Left , l , r->Left) , t = r;
    else 
        Merge (l->Right , l->Right , r) , t = l;
    Update (t);
}


void Split (item t , item &l , item &r , int index , int add = 0)
{
    if (t == NULL)
        l = r = NULL;
    else {
        int cur_index = add + count_nodes (t->Left);
        if (cur_index <= index)
            Split (t->Right , t->Right , r , index , add + count_nodes(t->Left) + 1) , l = t;
        else
            Split (t->Left , l , t->Left , index , add) , r = t;
        Update(t);
    }
}

int get_random() {
    return (rand () << 16 ) | rand ();
}

item Create (int data)
{
    item t = new Treap;
    
    t->Min = t->Key = data;
    t->Prior = get_random();
    t->Left = t->Right = NULL; 
    t->Size = 0;
    
    return t;
}

void Insert (item &t , int index , int data)
{
    item L = NULL , R = NULL;
    Split (t , L , R , index - 1);
    Merge (L , L , Create(data));
    Merge (t , L , R);
}

int GetMin (item t , int l , int r)
{
    item L , R , M;
        
    Split (t , L , R , l - 1);
    Split (R , M , R , r - l);  
    
    int ret = MinInSubtree (M);
        
    Merge (L , L , M);
    Merge (t , L , R);
    return ret;
}


int main (){
    srand( time(NULL) );
    item Array = NULL;
    
    int n;
    scanf ("%d" , &n);
    for (int i = 0 ; i < n ; i++)
    {
        char type;
        scanf(" %c ", &type);
        if (type == '+')
        {
            int ind , x;
            scanf("%d %d", &ind, &x);
            Insert (Array , ind , x);
        }

        else
        {
            int l , r;
            scanf("%d %d", &l, &r);
            
            -- l , -- r;
            
            printf("%d\n", GetMin(Array, l, r));
        }
    }


    return 0;
}


