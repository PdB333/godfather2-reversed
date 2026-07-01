// FUNC_NAME: GenericList::pushFront
void __fastcall GenericList::pushFront(undefined4 *this)
{
  undefined4 *node;
  undefined4 *head;
  
  // Get the memory allocator or default
  head = (undefined4 *)this[3];
  if (head == (undefined4 *)0x0) {
    head = (undefined4 *)&DAT_01218a14; // default allocator
  }
  
  // Allocate new node (12 bytes: value + prev + next)
  node = (undefined4 *)(*(code *)**(undefined4 **)this[4])(0xc, head);
  
  if (node != (undefined4 *)0x0) {
    *node = *unaff_ESI;           // store value at +0x00
    node[2] = 0;                  // next pointer at +0x08 = NULL
    node[1] = 0;                  // prev pointer at +0x04 = NULL
  }
  
  if (this[1] != 0) {             // if list is not empty (has head)
    *(undefined4 **)(this[1] + 4) = node;    // old head->prev = new node
    *(undefined4 *)(*(int *)(this[1] + 4) + 8) = this[1]; // new node->next = old head
    this[2] = this[2] + 1;        // increment size at +0x08
    this[1] = *(undefined4 *)(this[1] + 4); // head = new node (node is now head)
    return;
  }
  
  // Empty list case
  this[2] = this[2] + 1;          // increment size at +0x08
  *this = node;                   // tail at +0x00 = new node
  this[1] = node;                 // head at +0x04 = new node
  return;
}