#include <bits/stdc++.h>

using namespace std;

template <typename T>
class LinkedList
{
    class Node
    {
    public:
        T value;
        Node *next;
        Node *prev;
        
        Node(T newVal):value(newVal),next(nullptr),prev(nullptr){};
    };

    Node *head;
    Node *tail;
    Node *curr;

    size_t size;

    public:
        LinkedList():head(nullptr),tail(nullptr),curr(nullptr),size(0){};

        ~LinkedList()
        {
            Node *tmp = nullptr;

            while (head)
            {
                tmp = head;
                head = head->next;
                delete tmp;
            }
            
            head = nullptr;
            curr = nullptr;
            tail = nullptr;

            size = 0;

            cout<<"LinkedList destroyed\n";
        }

        LinkedList(const LinkedList<T> & ) = delete;
        LinkedList& operator=(LinkedList const &) = delete;

        void push_front(T newVal)
        {
            Node *newNode = new Node(newVal);
            Node *tmpHead = head;

            if(head == nullptr)
            {
                head = newNode;
                tail = newNode;
                curr = newNode;
            }
            else
            {
                newNode->next = head;
                head = newNode;
                newNode->next->prev = newNode;
            }

            size++;
        }

        void push_back(T newVal)
        {
            Node *newNode = new Node(newVal);
            newNode->prev = tail;

            if(head == nullptr)
            {
                head = newNode;
                tail = newNode;
                curr = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }

            size++;
        }

        bool empty()const
        {
            return size == 0;
        }

        size_t getSize()const
        {
            return size;
        }

        T getCurrent()
        {
            assert(curr != nullptr);
            return curr->value;
        }

        T first()
        {
            if(head)
              curr = head;

            return getCurrent();
        }

        T last()
        {
            if(tail)
              curr = tail;

            return getCurrent();
        }

        void nextElem()
        {
            assert(curr != nullptr);
            if(curr->next)
                curr = curr->next;
        }

        void prevElem()
        {
            assert(curr != nullptr);
            if(curr->prev)
                curr = curr->prev;
        }

        template <class TT>
        friend ostream & operator<<(std::ostream & os, const LinkedList<TT> & l)
        {
            l.print(os);
            return os;
        }

        private:

        void print(ostream & os = cout)const
        {
            Node *tmp = head;

            while(tmp)
            {
                os << tmp->value << ' ';
                tmp = tmp-> next;
            }
        }
};
template<typename T>
bool is_equal(LinkedList<T>&ll, initializer_list<T> il)
{
    if(ll.getSize() != il.size())
        return 0;

    ll.first();

    for(T elem: il)
    {
        if(elem != ll.getCurrent())
            return 0;

        ll.nextElem();
    }

    return 1;
}

int main()
{
    LinkedList<int> ll;

    assert(ll.empty() == 1);
    cout<<"LinkedList is empty\n";

    ll.push_back(1);
    assert(ll.getCurrent() == 1);
    cout<<"current == 1\n";

    ll.push_back(2);
    assert(ll.getCurrent() == 1);
    cout<<"current == 1\n";

    assert(is_equal(ll,{1,2}) == 1);
    cout<<"list equal to {1,2}\n";

    ll.push_back(3);
    assert(ll.getCurrent() == 2);
    cout<<"current == 2\n";

    assert(is_equal(ll,{1,2,3}) == 1);
    cout<<"list equal to {1,2,3}\n";

    assert(ll.getCurrent() == 3);
    cout<<"current == 3\n";

    ll.push_front(-4);
    assert(is_equal(ll,{-4,1,2,3}) == 1);
    cout<<"list equal to {-4,1,2,3}\n";

    ll.push_front(-5);
    assert(is_equal(ll,{-5,-4,1,2,3}) == 1);
    cout<<"list equal to {-5,-4,1,2,3}\n";

    ll.prevElem();
    assert(ll.getCurrent() == 2);
    cout<<"current == 2\n";

    ll.prevElem();
    ll.prevElem();
    assert(ll.getCurrent() == -4);
    cout<<"current == -4\n";

    ll.push_front(-6);
    ll.push_back(7);

    cout<<"in the end in linked_list we got: { "<<ll<<"}"<<endl;
    assert(is_equal(ll,{-6,-5,-4,1,2,3,7}) == 1);
    cout<<"list equal to {-6,-5,-4,1,2,3,7}\n";

    return 0;
}