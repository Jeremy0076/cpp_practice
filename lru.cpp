#include<iostream>
#include<unordered_map>
using namespace std;

struct Node {
    int key;
    int val;
    Node* pre;
    Node* next;
    Node():key(0),val(0),pre(nullptr),next(nullptr){}
    Node(int key_, int val_):key(key_),val(val_),pre(nullptr),next(nullptr){}
};

class LRUCache {
public:
    Node* head;
    Node* tail;
    unordered_map<int, Node*> mp;
    int size;
    int capacity;

    LRUCache(int capacity) {
        this->capacity = capacity;
        size = 0;
        head = new Node();
        tail = new Node();
        head -> next = tail;
        tail -> pre = head;
    }
    
    int get(int key) {
        if(!mp.count(key))
            return -1;
        moveToHead(mp[key]);
        return mp[key]->val;
    }
    
    void put(int key, int value) {
        if(!mp.count(key)){
            Node *node = new Node(key, value);
            addToHead(node);
            mp[key] = node;
            size++;
            if(size > capacity){
                Node* delNode = tail->pre;
                mp.erase(delNode->key);
                delNode->pre->next = tail;
                tail->pre = delNode->pre;
                delete delNode;
                --size;
            }
        }else{
            moveToHead(mp[key]);
            mp[key]->val = value;
        }
    }

    void deleteNode(Node* node) {
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }

    void addToHead(Node* node) {
        node->next = head->next;
        node->pre = head;
        head->next->pre = node;
        head->next = node;
    }

    void moveToHead(Node *node) {
        deleteNode(node);
        addToHead(node);
    }
};

int main(){
    return 0;
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */