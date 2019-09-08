//
// Created by kiosk on 19-9-3.
//
#include "skiplist.h"
#include <vector>
#include "random.h"

// create node
template <typename  Key>
typename skiplist<Key>::node* skiplist<Key>::newnode(const Key& key,int height){
    char * memory = prena_->defalutallocate(sizeof(struct node) + height * sizeof(struct node *) );
    return new (memory) node(key);
}

template  <typename  Key>
skiplist<Key>::skiplist(Prena *prena)  : prena_(prena),head_(newnode(0,MaxHeight)),max_height_(1){
    for(size_t i = 0 ; i < MaxHeight ;++i)
    {
        printf("i = %d\n",i);
        head_->setnext(i, nullptr);
    }
    printf("do \n");
}

template <typename Key>
void skiplist<Key>::Insert(const Key &key) {
    //在这里我们构建跳跃表的前驱结点和后继结点
    //我们在这里设置跳跃表最大的层数 //以前驱结点来进行使用
    //跳跃表从最高的链表来进行比较之后再进行下一层的比较
    //跳跃表从大往小进行排列 // 如果我们没有找到比key小的那么直接插到末尾
    //设置
    int level = GetMaxheight() - 1;
    node * prev[MaxHeight];
    node * temp = Findlessthan(key);
    int height = random_unint();
    if(height > GetMaxheight()) // 大于最大的层数，则把之前的所有前驱结点
    {
        //都设置为head
        for(size_t  i = level ;i<= height;++i)
        {
            prev[i] = head_;
        }
        //把最高的max更新为它
        max_height_.store(height,std::memory_order_relaxed);
        // 设置为最常用的模型
    }
    temp = newnode(key,height); // 多height
    for( size_t  i = 0 ; i < height ; ++i)
    {
        temp->setnext(i,prev[i]->next(i));
        prev[i]->setnext(i,temp);
    }
    temp->setheight(height);
}

template <typename  Key>
bool skiplist<Key>::Delete(const Key &key) {
     // 删除一个结点
     node * temp = find(key);
     node * tempb = Findlessthan(key);
     if(temp == nullptr)
     {
         return false;
     }
     for(int i = 0 ;i <= tempb->getheight() ;++i)
     {
       tempb->setnext(i,temp->next(i));
     }
     temp->clear();
     return true;
}



template <typename  Key>
typename skiplist<Key>::node * skiplist<Key>::Findlessthan(const Key &key) const
{
    //找到小于key的结点
    node * temp = head_;
    int level = GetMaxheight() - 1;
    //从最上面往下面进行遍历
    //链表循环，如果最高一层没有找到的话 ,level 进行减少往下一次寻找
    //这里从上到下来进行查找的话，尽可能的减少查找的效率
    while(true) {
        node * next = temp->next(level);
        //在这里需要判断它的next值存在不存在如果不存在的话，则为nullptr
        if (next == nullptr || (next->key >= key)) {
            if (level == 0) {
               return temp;
            } else {
                level--;
            }
        }
        else{
            temp = next; // 直到level为0为止
        }
    }
}

template  <typename  Key>
typename  skiplist<Key>::node * skiplist<Key>::find(const Key &key) const
{
    node * temp = head_;
    int level = GetMaxheight() - 1;
    while(true) {
        node *next = temp->next(level);
        //在这里需要判断它的next值存在不存在如果不存在的话，则为nullptr
        if (next == nullptr || (next->key == key)) {
            if (level == 0) {
                return temp;
            } else {
                level--;
            }
        }
        else{
            temp = next;
        }
    }
}






