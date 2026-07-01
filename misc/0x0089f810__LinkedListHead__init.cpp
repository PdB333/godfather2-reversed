// FUNC_NAME: LinkedListHead::init
// Function address: 0x0089f810
// Role: Initializes a doubly-linked list head node (or empty list sentinel).
// Sets both next (offset 0) and prev (offset 4) pointers to point to itself,
// forming a circular empty list. Calls base class initializer first.

void __thiscall LinkedListHead::init(void) {
    baseConstructor(); // Calls FUN_0089ec40 (base class or common init)
    this->next = this; // +0x00: next pointer
    this->prev = this; // +0x04: prev pointer
}