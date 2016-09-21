#include "LIST.H"
template <class List_entry>
List<List_entry>::List()
/* 
 
Post: The List is initialized to be empty.
 
*/

{
   count = 0;
   current = head = NULL;
   current_position = -1;
}
 
template <class List_entry>
void List<List_entry>::clear()
/* 
 
Post: The List is cleared.
 
*/

{
   Node<List_entry> *p, *q;

   for (p = head; p; p = q) {
      q = p->next;
      delete p;
   }
   count = 0;
   current = head = NULL;
   current_position = -1;
}
 
template <class List_entry>
int List<List_entry>::size() const
/* 
 
Post: The function returns the number of entries in the List.
 
*/

{
   return count;
}
 
template <class List_entry>
bool List<List_entry>::empty() const
/* 
 
Post: The function returns true or false according as the List is empty or not.
 
*/

{
   return count <= 0;
}
 
template <class List_entry>
bool List<List_entry>::full() const
/* 
 
Post: The function returns true or false according as the List is full or not.
 
*/

{
   return false;
}
 
template <class List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry &))
/* 
 
Post: The action specified by function *f has been performed on every
entry of the List, beginning at position 0 and doing each in turn.
 
*/

{
   Node<List_entry> *to_visit;

   for (to_visit = head; to_visit; to_visit = to_visit->next)
      (*visit)(to_visit->entry);
}
 
template <class List_entry>
Error_code List<List_entry>::insert(int position, const List_entry &x)
/* 
 
Post: If the List is not full and 0 <= position <= n,
where n is the number of entries in the List,
the function succeeds:
Any entry formerly at
position and all later entries have their
position numbers increased by 1 and
x is inserted at position in the List.

 
Else:
the function fails with a diagnostic error code.
 
*/

{
   Node<List_entry> *new_node;

   if (position < 0 || position > count) return Error_code::range_error;
   new_node = new Node<List_entry>;

   if (new_node == NULL) return fail;
   new_node->entry = x;

   if (position == 0) {
      new_node->next = head;
      current = head = new_node;
      current_position = 0;
   } else {
      set_position(position - 1);
      new_node->next = current->next;
      current->next = new_node;
   }
   count++;
   return success;
}
 
template <class List_entry>
Error_code List<List_entry>::retrieve(int position, List_entry &x) const
/* 
 
Post: If the List is not full and 0 <= position < n,
where n is the number of entries in the List,
the function succeeds:
The entry at position is copied to x.
Otherwise the function fails with an error code of range_error.
 
*/

{
   if (position < 0 || position >= count) return range_error;
   set_position(position);
   x = current->entry;
   return success;
}
 
template <class List_entry>
Error_code List<List_entry>::replace(int position, const List_entry &x)
/* 
 
Post: If 0 <= position < n,
where n is the number of entries in the List,
the function succeeds:
The entry at position is replaced by x,
all other entries remain unchanged.
Otherwise the function fails with an error code of range_error.
 
*/

{
   if (position < 0 || position >= count) return range_error;
   set_position(position);
   current->entry = x;
   return success;
}
 
template <class List_entry>
Error_code List<List_entry>::remove(int position, List_entry &x)
/* 
 
Post: If 0 <= position < n,
where n is the number of entries in the List,
the function succeeds:
The entry at position is removed
from the List, and the entries in all later positions
have their position numbers decreased by 1.
The parameter x records a copy of
the entry formerly at position.
Otherwise the function fails with a diagnostic error code.
 
*/

{
   Node<List_entry> *old_node;
   if (count == 0) return fail;
   if (position < 0 || position >= count) return range_error;

   if (position > 0) {
      set_position(position - 1);
      old_node = current->next;
      current->next = old_node->next;
   }

   else {
      old_node = head;
      current = head = old_node->next;
      current_position = 0;
   }

   x = old_node->entry;
   delete old_node;
   count--;
   return success;
}
 
template <class List_entry>
void List<List_entry>::set_position(int position) const
/*   
Pre:   position is a valid position in the List:
      0 <= position < count.
Post: The current Node pointer references the Node at position.
 */
{
   if (position < current_position) {  //  must start over at head of list
      current_position = 0;
      current = head;
   }
   for ( ; current_position != position; current_position++)
      current = current->next;
}
 
template <class List_entry>
List<List_entry>::~List()
/* 
 
Post: The List is empty: all entries have been removed.
 
*/

{
   clear();
}
 
template <class List_entry>
List<List_entry>::List(const List<List_entry> &copy)
/* 
 
Post: The List is initialized to copy the parameter copy.
 
*/

{
   count = copy.count;
   current_position = 0;
   Node<List_entry> *new_node, *old_node = copy.head;

   if (old_node == NULL) current =  head = NULL;
   else {
      new_node = current = head = new Node<List_entry>(old_node->entry);
      while (old_node->next != NULL) {
         old_node = old_node->next;
         new_node->next = new Node<List_entry>(old_node->entry);
         new_node = new_node->next;
      }
      set_position(copy.current_position);
   }
}
 
template <class List_entry>
void List<List_entry>::operator =(const List<List_entry> &original)
/* 
 
Post: The List is assigned to copy a parameter
 
*/

{
   List new_copy(original);
   clear();
   count = new_copy.count;
   current_position = new_copy.current_position;
   head = new_copy.head;
   current = new_copy.current;
   new_copy.count = 0;
   new_copy.current_position = 0;
   new_copy.head = NULL;
   new_copy.current = NULL;
}
