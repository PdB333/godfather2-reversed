// FUNC_NAME: ObjectListNode::constructor
void __thiscall ObjectListNode::constructor(void *this) {
    // 'this' is in register ESI (unknown calling convention, assume __thiscall with ESI)
    // Original decompiled uses in_EAX as this pointer, but unaff_ESI is the actual object base.
    // We reinterpret: in_EAX is actually the this pointer passed in EAX, but for __thiscall it's ECX.
    // Ghidra confusion: treat all registers as part of the object context.
    int *vtablePtr = *(int **)this;                       // offset 0x00: vtable pointer
    int countValue = *(int *)((char *)this + 4);          // offset 0x04: some integer (e.g., count or type)

    // Call virtual function at vtable+8 (index 2) — likely base class initializer
    // The vtable is for a base class (e.g., TNL::ListItem or EARS::ListNode)
    ((void (__thiscall *)(int *))vtablePtr[2])(vtablePtr);

    // Determine argument for list insertion
    int arg;
    if (countValue == 0) {
        arg = 0;
    } else {
        arg = FUN_004265d0(countValue, vtablePtr); // some conversion/helper (e.g., allocate node)
    }

    // Insert node into a list; first parameter is this object, second is vtable pointer, third is arg
    FUN_005e0170(this, vtablePtr, arg);

    // Allocate a new node from a memory pool (likely from a free list)
    int *newNode = (int *)FUN_005e0b10();             // returns a pointer to a new node
    *(int *)((char *)this + 0x1C) = (int)newNode;    // store node at offset 0x1C (maybe head pointer)

    // Initialize the node as a circular doubly-linked list (pointing to itself)
    *(char *)((char *)newNode + 0x15) = 1;           // some flag (e.g., isHead, isActive)
    newNode[0] = (int)newNode;                       // offset 0x00: previous pointer
    newNode[1] = (int)newNode;                       // offset 0x04: next pointer
    newNode[2] = (int)newNode;                       // offset 0x08: perhaps data or a self-reference

    // Clear another member at offset 0x20
    *(int *)((char *)this + 0x20) = 0;
}