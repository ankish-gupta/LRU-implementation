#include<bits/stdc++.h>
using namespace std;
class node{
    public:
        string key;
        int value; 
    node(string key,int value){
        this->key=key;
        this->value=value;
    }
};

class LRUCache{
    public:
        int maxsize;
        list<node> l;
        unordered_map<string, list<node>::iterator> m;

    LRUCache(int maxsize){
        if(maxsize>1)
            this->maxsize=maxsize;
        else
            maxsize=1;
    }

    void insertData(string key, int value){
        if(m.find(key)!=m.end()){
            auto it=m[key];        //accessing the value (which is address of list) of map
            it->value=value;       //change the value of the list by the address stored in map
        }
        else{
            // if the cache i.e.. the list is full
            if(l.size()==maxsize){
                node last=l.back();
                m.erase(last.key);
                l.pop_back();
            }
            node kv(key,value);
            l.push_front(kv);
            m[key]=l.begin();      //storing the address of the list in which key-value pair is inserted in the map
        }
    }

    //Here's a catch in getValue(), the key which you access will be become the head of the list
    int* getValue(string key){
        if(m.find(key)!=m.end()){
            auto it=m[key];         //accessing the key in the unordered map which is actually the address of the pair where the element is present 
            l.push_front(*it);      //pushing the key-value pair to the top of the list
            m[key]=l.begin();       //storing the address of the list accessed in the map
            l.erase(it);            //erasing the original of the key-value pair from the list
            return &l.begin()->value;
        }
        return NULL;                //if key doesn't found return NULL
    }

    string mostRecentlyUsed(){
        return l.front().key;       //Most recent key is on the front of the list i.e.. at the head
    }
};

int main(){
    LRUCache lru(5);
    //Insert Data
    lru.insertData("Reynolds Roller Gel",15);
    lru.insertData("Reynolds Trimax",55);
    lru.insertData("Cello Gripper",10);
    lru.insertData("Parker Roller Ball",280);
    lru.insertData("Cello Spinter Gel",10);

    cout<<"LRU implementation\n\n";
    while(1){
        cout<<"choose the options:\n";
        cout<<"1.Insert data\n";
        cout<<"2.Get value of the item\n";
        cout<<"3.Most recently used item\n";
        cout<<"For Exit press any other key:\n";
        int choice;
        cin>>choice;
        switch(choice){
            case 1:{
                string key;
                int value;
                cout<<"Insert key and value respectively\n";
                cin.get();
                getline(cin,key);
                cin>>value;
                lru.insertData(key,value);
                cout<<"Data inserted successfully!\n";
                break;
            }
            case 2:{
                string key;
                cin.get();
                getline(cin,key);
                cout<<"Value of "<<key<<" :";
                cout<<*lru.getValue(key);
                cout<<endl;
                break;
            }
            case 3:{
                cout<<lru.mostRecentlyUsed();
                cout<<endl;
                cout<<"\n";
                break;
            }
            default:
                exit(0);
                cout<<"\nThanking you!";
                cout<<"\n By: Ankish Gupta";
            }
        }
    return 0;
}