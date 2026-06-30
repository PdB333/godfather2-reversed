// FUNC_NAME: NetSession::createNetworkObject
// Address: 0x00624b60
// This function appears to create a network-replicated object.
// It uses a global sequence counter (g_objectSequenceCounter) to assign unique IDs,
// allocates an object via a class-specific factory, calls a constructor,
// then invokes two virtual callbacks (likely init and network dispatch).

// Global variable at 0x012234ac (8 bytes offset for a counter)
extern uint32 g_objectSequenceCounter; // +0x0, base value; +0x8 is used as sequence number

// Forward declarations for helper functions (pool allocation and class vtable retrieval)
void* __cdecl allocateObjectFromPool(uint32 classId); // FUN_00621530
void* __cdecl getClassVtable(uint32 classId);        // FUN_00621610

void __thiscall NetSession::createNetworkObject(NetSession* this, undefined4 param2, undefined4 param3, uint32 classId)
{
    void* object;
    int classVtableOffset;
    uint32* vtable; // code* but used as uint32* for function pointers
    void* (*constructor)(void*, int); // Function pointer for constructor

    // Retrieve the base of the pool for this class
    object = allocateObjectFromPool(classId);

    // Get the vtable offset for the class (probably index into a table)
    classVtableOffset = *(int*)((int)object + 8); // Interpretation: offset 8 in pool data stores vtable index
    vtable = (uint32*)getClassVtable(*(uint32*)((int)object + 8)); // Resolve to actual vtable pointer

    // Call the constructor for this class (param2 unused, always 0)
    constructor = (void* (*)(void*, int))vtable[0]; // First vtable entry = constructor?
    constructor(object, 0);

    // Set the object's network sequence number (offset 0x2C) from global counter
    *(uint32*)((int)object + 0x2C) = *(uint32*)((int)&g_objectSequenceCounter + 8);

    // Increment the global sequence counter
    (*(uint32*)((int)&g_objectSequenceCounter + 8))++;

    // Set object's type/ID from the 'this' object's field at offset 4
    *(uint32*)((int)object + 4) = *(uint32*)((int)this + 4);

    // Call virtual callback at vtable offset 0x10 (e.g., onObjectCreated)
    ( (void (*)(void*)) vtable[0x10/4] ) (object);

    // Call virtual callback at vtable offset 0x18 with three arguments
    // (unaff_retaddr is the return address, but we treat it as a void* parameter)
    ( (void (*)(void*, undefined4, void*)) vtable[0x18/4] ) ( /* return address? */ , param2, object);
}