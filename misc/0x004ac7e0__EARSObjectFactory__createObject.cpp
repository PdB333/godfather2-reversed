// FUNC_NAME: EARSObjectFactory::createObject
// Address: 0x004ac7e0
// Creates a new game object using a class hash and initializes it with type ID and unique ID.

void __thiscall EARSObjectFactory::createObject(uint hash, uint arg2, uint unused) {
    int* pFreeList;        // this->freeList at +0x48
    int* pNewObject;       // pointer to newly created object
    int classDescriptor;   // from hash lookup
    int vtablePtr;         // vtable for the class
    int* (*createFunc)(uint, uint*); // factory function for the class
    int localReserved;     // local variable for factory call
    uint magicHash = 0xd42a2c49; // seed for hash? unused?
    static int* globalIdCounter = DAT_012234ac; // +8 is next ID

    // Possibly get a pooled object if available (field at +0x48 is a free list pointer)
    // The computation seems to convert a free list node pointer to the container object,
    // but the result (local_4) is not used – likely a debug or inlined optimization.
    if (this->freeList == 0) {
        local_4 = 0; // no free list
    } else {
        local_4 = (int)this->freeList - 0x48; // container offset
    }

    // Look up the class descriptor from the hash
    classDescriptor = getClassDescriptorFunc(hash); // FUN_00621530
    vtablePtr = getVtableFunc(*(int*)(classDescriptor + 8)); // FUN_00621610
    createFunc = (int* (*)(uint, uint*))vtablePtr;

    // Create the object (passes hash and a local scratch)
    pNewObject = (*createFunc)(hash, &localReserved);

    // Assign a unique ID from a global counter
    pNewObject[0x2c / 4] = *(int*)(globalIdCounter + 2); // offset +0x2c
    *(int*)(globalIdCounter + 2) += 1; // increment counter

    // Set the object's type ID from this factory's field at +0x04
    pNewObject[0x04 / 4] = this->typeId;

    // Call virtual initialization on the new object (vtable index 4)
    (*(void (**)(void*))(*(int*)pNewObject + 0x10))(pNewObject);

    // Notify parent/caller (vtable index 6, passes return address, arg2, new object)
    // The return address (unaff_retaddr) is captured implicitly by the calling convention.
    (*(void (**)(int, uint, int*))(*(int*)this + 0x18))(/*retaddr*/ 0, arg2, pNewObject);
}