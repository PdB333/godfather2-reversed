// FUNC_NAME: ResourceObject::ResourceObject
void __fastcall ResourceObject::ResourceObject(ResourceObject *this) {
    // Set base class vtable
    this->vtable = &g_baseVtable;                       // 0x00e37f58
    // Call base class constructor
    BaseResource::BaseResource();                       // 0x004ebba0
    // Override vtable with derived class vtable
    this->vtable = &g_resourceObjectVtable;             // 0x00e37110

    int handle = *(int*)((char*)this + 0x10);           // +0x10: handle/ID
    if (handle != 0) {
        // Global resource manager pool head
        int *pFreeList = (int*)((char*)&g_resourceManager + 0x14); // +0x14: pool cursor
        // The pool nodes are 8 bytes: next pointer (4) + data (4)
        // Write sentinel as next of current free node
        *(void**)*pFreeList = &g_resourceSentinel;      // PTR_LAB_01123be8
        *pFreeList += 4;                                 // Move to data field
        // Store handle as data
        *(int*)*pFreeList = handle;
        *pFreeList += 4;                                 // Advance to next free slot
        // Clear handle fields from object
        *(int*)((char*)this + 0x10) = 0;                // +0x10
        *(int*)((char*)this + 0x14) = 0;                // +0x14
    }
}