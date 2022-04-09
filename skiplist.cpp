#include<iostream>
#include<stdlib.h>
#include<vector>

using namespace std;

class Skiplist {
public:
    static const int SKIPLIST_P_VAL = RAND_MAX/2, MAX_LEVEL = 16;

    struct Node{
        int val;
        vector<Node*> next;
        Node(int val, int size = MAX_LEVEL): val(val), next(size){}
    };

    Node head;
    int maxlevel = 1;

    Skiplist() :head(INT_MIN, MAX_LEVEL) {}
    
    // 随机层数
    static int random_level(){
        int level = 1;
        while(rand() < SKIPLIST_P_VAL && level < MAX_LEVEL){
            level++;
        }
        return level;
    }
    // 此函数是跳表的核心，实现的功能是，寻找key所经历的路径。返回路径上的前置节点
    vector<Node*> _search(int key){
        Node* cur = &head;
        vector<Node* >prevs(MAX_LEVEL);
        for(int i = maxlevel-1; i>=0; i--){
            // 从顶层开始
            while(cur->next[i] && cur->next[i]->val < key){
                cur = cur->next[i];
            }
            prevs[i] = cur;
        }
        return prevs;
    }

    bool search(int target) {
        auto prevs = _search(target);
        return prevs[0]->next[0] && prevs[0]->next[0]->val == target;
    }
    
    void add(int num) {
        auto prevs = _search(num);
        int level = random_level();

        // level超出当前最大高度maxlevel 更新
        if(level > maxlevel){
            for(int i = maxlevel; i<level; i++){
                prevs[i] = &head;
            }
            maxlevel = level;
        }

        // 创建当前节点
        Node* cur = new Node(num, level);

        for(int i = level-1; i>=0; i--){
            cur->next[i] = prevs[i]->next[i];
            prevs[i]->next[i] = cur;
        }
    }
    
    bool erase(int num) {
        auto prevs = _search(num);

        // 如果num不存在跳表中
        if(!prevs[0]->next[0] || prevs[0]->next[0]->val != num)
            return false;

        Node* del = prevs[0]->next[0];
        // 删除prevs后的节点
        for(int i = 0; i<maxlevel; i++){
            if(prevs[i]->next[i] == del){
                prevs[i]->next[i] = del->next[i];
            }
        }

        delete del;

        // 更新maxlevel
        while(maxlevel > 1 && !head.next[maxlevel - 1]){
            maxlevel--;
        }
        return true;
    }
};

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */