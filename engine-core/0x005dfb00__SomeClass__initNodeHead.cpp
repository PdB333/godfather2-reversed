// FUNC_NAME: SomeClass::initNodeHead
// Address: 0x005dfb00
// This function initializes a node list head for a class. It takes an interface object (likely a factory or allocator) in EAX,
// calls a virtual method on it (at vtable offset 8) to perform some setup, then retrieves or creates a node (via FUN_004265d0),
// passes it to FUN_005e0800 to finalize the list head, allocates a new node from FUN_005e10a0, and sets up circular pointers.

void SomeClass::initNodeHead(void* interfaceObj) // interfaceObj in EAX, this in ESI
{
    // Presumed vtable layout: interfaceObj points to a vtable; third entry (+8) is a method taking (interfaceObj)
    // The method is used for some initialization of the interface.
    void* vtablePtr = *(void**)interfaceObj;
    (*(void (__thiscall**)(void*))((char*)vtablePtr + 8))(interfaceObj); // call vtable[2] (offset 8)

    int nodeData = *(int*)(interfaceObj + 4); // second field of interfaceObj? Possibly a handle or ID
    int result;
    if (nodeData == 0) {
        result = 0;
    } else {
        result = FUN_004265d0(nodeData, vtablePtr); // Get or create some structure from nodeData via vtablePtr
    }

    // FUN_005e0800(this, vtablePtr, result) — likely inserts or links the node into this class's list
    FUN_005e0800(this, vtablePtr, result);

    // Allocate a new node (likely from a pool)
    int newNode = FUN_005e10a0(); // returns a pointer to a node structure
    *(int*)(this + 0x1c) = newNode; // store node pointer at this+0x1c
    *(char*)(newNode + 0x15) = 1;   // set flag byte at offset 0x15 to 1

    // Initialize circular pointers: prev, next, and an additional pointer at +8 all point to self
    *(int*)(newNode + 4) = newNode; // node+4 = self
    *(int*)newNode = newNode;       // node+0 = self
    *(int*)(newNode + 8) = newNode; // node+8 = self

    *(int*)(this + 0x20) = 0; // clear another field at this+0x20
}