package main



import (

    "fmt"

)



type Treap struct {

    Key, Prior int 

    Size, Min int

    Left, Right *Treap

}



func min(a, b int) int {

    if a < b {

        return a

    }

    return b

}



func (t * Treap) Update() {

    if t != nil {

        t.Size = count_nodes(t.Left) + count_nodes(t.Right) + 1

        t.Min = min( min(MinInSubtree(t.Left), MinInSubtree(t.Right)) , t.Key)

    }   

}

func Create(data int) *Treap {

    t := &Treap{}

    t.Min = data

    t.Key = data

    t.Prior = get_random()

    t.Left = nil

    t.Right = nil

    t.Size = 1

    return t

}



func Merge(l , r *Treap) *Treap {

    var t *Treap = nil

     

    if l == nil {

       // fmt.Println("haha l is nil")

        t = r

    } else if r == nil {

        //fmt.Println("haha r is nil")

        t = l

    } else if l.Prior < r.Prior  {

        r.Left = Merge(l, r.Left)

        t = r

    } else {

        l.Right = Merge(l.Right, r)

        t = l

    }

    

    if t != nil {

        t.Update()

    }

    return t

}



func Insert (t *Treap, index, data int) *Treap{

    var L, R *Treap = nil, nil

    L, R = Split(t, L, R, index - 1, 0)

    L = Merge(L, Create(data))

    t = Merge(L, R)

    return t    

}







func Split(t, l, r *Treap, index, add int) (*Treap, *Treap){

    if t == nil {

        l = nil

        r = nil

    } else {

        var cur_index int = add + count_nodes(t.Left)

        if cur_index <= index {

            t.Right, r = Split(t.Right, t.Right, r, index, add + count_nodes(t.Left) + 1)

            l = t

        }else {

            l, t.Left = Split(t.Left, l, t.Left, index, add)

            r = t

        }

        t.Update()

    }

    return l, r 

}



//const inf = 1e9



func output(t *Treap) {

    if (t != nil) {

        output(t.Left)

        fmt.Print(t.Key, " ")

        output(t.Right)

    }

}



func count_nodes (t *Treap) int {

    if t == nil {

        return 0

    } else {

        return t.Size

    }

}



func MinInSubtree(t *Treap) int {

    if t == nil {

        return 10000000

    } else {

        return t.Min

    }

}







func GetMin(t *Treap, l , r int) int{

    var L, R, M *Treap = nil, nil, nil

    

    L, R = Split(t, L, R, l - 1, 0)

    M, R = Split(R, M, R, r - l, 0)

    

    var ret int = MinInSubtree(M);  

    

    L = Merge(L, M)

    t = Merge(L, R)

    

    return ret

}





func get_random() int {

    return  0

}



func main (){

    var Array *Treap = nil

    

    

    

    var n int;

    fmt.Scan(&n);

    for i := 0 ; i < n ; i ++ {

        var c string

                        

        fmt.Scan(&c)

        // fmt.Println("c = " , c)

        

        if c == "+" {

            var ind, x int 

            fmt.Scan(&ind, &x)

            Array = Insert(Array, ind, x)

            //fmt.Println("Ind, x = ",ind, x)

            

        } else {

            var l, r int

            fmt.Scan(&l, &r)

            l --

            r --

            fmt.Println(GetMin(Array, l, r))

        }

        

    }

    

}
