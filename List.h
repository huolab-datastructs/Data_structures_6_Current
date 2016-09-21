#include   "../../C/UTILITY.H"
template <class List_entry>
struct Node {
   List_entry entry;
   Node<List_entry> *next;
   Node();
   Node(List_entry, Node<List_entry> *link = NULL);
};
 
template <class List_entry>
class List {
public:
 
   List();
   int size() const;
   bool full() const;
   bool empty() const;
   void clear();
   void traverse(void (*visit)(List_entry &));
   Error_code retrieve(int position, List_entry &x) const;
   Error_code replace(int position, const List_entry &x);
   Error_code remove(int position, List_entry &x);
   Error_code insert(int position, const List_entry &x);
   ~List();
   List(const List<List_entry> &copy);
   void operator =(const List<List_entry> &copy);
 
//  Add specifications for the methods of the list ADT.
//  Add methods to replace the compiler-generated defaults.

protected:
//  Data members for the linked-list implementation with
//  current position follow:
   int count;
   mutable int current_position;
   Node<List_entry> *head;
   mutable Node<List_entry> *current;

//  Auxiliary function to locate list positions follows:
   void set_position(int position) const;
};
 
template <class List_entry>
Node<List_entry>::Node()
{
   next = NULL;
}

template <class List_entry>
Node<List_entry>::Node (List_entry data, Node<List_entry> *link)
{
   entry = data;
   next = link;
}
