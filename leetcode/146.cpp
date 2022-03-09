//LRU缓存 
class LRUCache {
private:
public:
    struct Node {
        int key, value;
        Node *pre, *next;
        Node(int m_key, int m_value): key(m_key), value(m_value), pre(NULL), next(NULL) {

        }
    };
    Node *head, *tail;
    int sum;
    unordered_map<int, Node*> mp;
    LRUCache(int capacity) {
        sum = capacity;
        head = new Node(-1, -1);
        tail = new Node(-2, -1);
        head->next = tail;
        tail->pre = head;
    }
    void del(Node *now) { //删除某个节点
        now->next->pre = now->pre;
        now->pre->next = now->next;
    }
    void insert(Node *now) {
        Node *x = head->next;
        head->next = now;
        now->next = x;
        now->pre = head;
        x->pre = now;
    }
    int get(int key) {
        if (mp.find(key) == mp.end())
			return -1;
		auto p = mp[key];
		del(p);
		insert(p);
		return p->value;
    }
    
    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {
            mp[key]->value = value;
            del(mp[key]);
            insert(mp[key]);
        } else {
            if (mp.size() == sum) {
				auto p = tail->pre;
				del(p);
				mp.erase(p->key);
				delete p;
            } 
            auto p = new Node(key, value);
            mp[key] = p;
            insert(p);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */