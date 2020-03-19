#include <iostream>

// Uncomment line with "#define DEBUG" if you want to see your hashtable.
// But rememeber to send only solutions with debug turned off!
// #define DEBUG 1 

using namespace std;


struct Node
{
    string text;
    Node *next;
};

int hashfunc(string txt, int n) {
    int result = 0;
    for(int i=0; i<txt.length(); i++) result ^= txt[i] << ((i % 4) * 8);
    return result % n;
}

bool check_if_exists(Node** hashtable, int n, string txt) {
    if(n == 0) return false;   
    Node *p = hashtable[hashfunc(txt, n)];
       while(p != NULL) {
           if(p->text == txt) return true;
           p = p->next;
       }   
       return false;
}

void add_to_hashtable(Node** hashtable, int n, string txt) {  
        Node *p = new Node;
        p->text = txt;
        p->next = hashtable[hashfunc(txt, n)];
        hashtable[hashfunc(txt, n)] = p;
}

void free_memory(Node** hashtable, int n) {
    Node *ptr, *nxt;    
    for (int i = 0; i < n; i++) {
        ptr = hashtable[i];
        while (ptr != NULL) {
            nxt = ptr->next;
            delete ptr;
            ptr = nxt;
        }
    }
    delete[](hashtable);
}

void debug_print_hashtable(Node** hashtable, int n) {
    #ifdef DEBUG
        Node* ptr;  
        for (int i = 0; i < n; i++) {
            cout << i << ": ";
            ptr = hashtable[i];
            while (ptr != NULL) {
                cout << ptr->text << " | ";
                ptr = ptr->next;
            }
            cout << endl;
        }
    #endif
}

int main() {
    ios::sync_with_stdio(false);
    int Z;
    cin >> Z;

    while (Z--) {
        int n, k;
        string tmp;

        cin >> n;
        cin >> k; 
        int size = n;
        Node** hashtable = new Node*[size]();
        
        for (int i = 0; i < size; i++)
            hashtable[i] = NULL;

        for (int i = 0; i < n; i++) {
            cin >> tmp;
            add_to_hashtable(hashtable, size, tmp);
        }

        debug_print_hashtable(hashtable, size);

        for (int i = 0; i < k; i++) {
            cin >> tmp;
            if (check_if_exists(hashtable, size, tmp)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }

        free_memory(hashtable, size);

    }

}
