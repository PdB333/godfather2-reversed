// FUNC_NAME: SomeClassWithList::~SomeClassWithList
// Address: 0x00956710
void __fastcall SomeClassWithList::~SomeClassWithList(SomeClassWithList* this)
{
  Node* nextIter;
  Node* current;

  // Set vtable to base class (presumably destructor chain)
  this->vtable = &PTR_FUN_00d8c120;
  // Call base class cleanup (maybe release references or detach)
  FUN_00976380(0);
  // If there is a sub-object at offset 0x10, destroy it
  if (this->subObject != 0) {
    FUN_004daf90(&this->subObject); // destructor for sub-object at +0x10
  }
  // Switch vtable to another base (likely final base)
  this->vtable = &PTR_FUN_00e32808;
  // Traverse and clear a linked list starting at offset +0x4
  current = (Node*)this->listHead; // param_1[1] - first node
  while (current != (Node*)0x0) {
    nextIter = (Node*)current->next; // current[1] - next pointer
    // Zero out the node (likely to invalidate it)
    current->next = (Node*)0x0;
    *current = (Node){0,0}; // zero entire node (first field and next)
    current = nextIter;
  }
  return;
}