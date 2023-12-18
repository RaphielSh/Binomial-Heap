#include <iostream>
#include <list>
#include <time.h>
#include <memory>

struct node{
    node(int);
    int val;
    std::list<node*>list;
    int getHeight();
    static bool Compare(node*, node*);
    static node* Merge(node*, node*);
    void n_print(int shift);
    typedef std::list<node*>::iterator it;
};

class BinHeap{
protected:
    std::list<node*>list;
    void Insert(node*);
public:
    // ~BinHeap();
    void Insert(int val);
    bool isEmpty();
    int Pop();
    void HeapPrint();
    typedef std::list<node*>::iterator it;
};


//node definition
node::node(int value){val = value;}


//get node hight
inline int node::getHeight(){return list.size();}


//compare if nodes are equal
bool node::Compare(node* node_1, node* node_2){return node_1->getHeight() == node_2->getHeight();}


//merge 2 nodes
node* node::Merge(node* node_1, node* node_2){
    node* node;
    ((node_1->val) < (node_2->val)) ? (node = node_1, node->list.push_back(node_2)):(node = node_2, node->list.push_back(node_1));
    return node;
}


//beautiful tree-like heap output
void node::n_print(int shift){
    for(int i = 0; i < shift; ++i) putchar(' ');
    std::cout << val << std::endl;
    for(node::it it = list.begin(); it != list.end(); ++it) 
        (*it)->n_print(shift+2);   //+2 spaces every tree level
}


//insert value and make it node
void BinHeap::Insert(int val){Insert(new node(val));}


//insert node
void BinHeap::Insert(node* node){
    BinHeap::it it;
    while(true){
        for(it = list.begin(); it != list.end(); ++it)
            if(node::Compare(node, *it)) break; //if node and iterator are equal we push it back
        if(it == list.end())break;  //push back if iterator is end of the list
        node = node::Merge(node, *it);  //merge node and iterator
        list.erase(it);
    }
    list.push_back(node);
}

int BinHeap::Pop(){
    int min;
    node::it it_1, it_2;
    min = list.front()->val;
    for(it_1 = list.begin(); it_1 != list.end(); ++it_1)
        if(min>=(*it_1)->val)  //if iterator is smaller than min, it becomes the min of the tree
            it_2 = it_1, min = (*it_1)->val;
    node* node = *it_2; 
    list.erase(it_2);
    for(it_1 = node->list.begin(); it_1 != node->list.end(); ++it_1)
        Insert(*it_1); 
    delete node;
    
    return min;
}

bool BinHeap::isEmpty(){return list.empty();}

void BinHeap::HeapPrint(){
    // std::cout << "[n_print]" << std::endl;
    for(node::it it = list.begin(); it != list.end(); ++it)
        (*it)->n_print(0);//0 is shift
}

int main(){
    BinHeap heap;
    for(int i = 0; i < 50; ++i)
        heap.Insert(rand()%200);    //50 random nums from 0 to 200
    heap.HeapPrint();
    // std::cout << "End of n_print" << std::endl;
    while(!heap.isEmpty())
        std::cout << heap.Pop() << ' ';
    return 0;
}