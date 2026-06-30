// FUNC_NAME: EntityObject::~EntityObject
void __fastcall EntityObject::~EntityObject(EntityObject* this)
{
    int childPtr;

    // Set vtable to the destructing vtable (ensures correct virtual dispatch during destruction)
    *(int**)this = &PTR_FUN_00e38238;

    // Release first child object (offset +0xE0) via the global allocator
    childPtr = *(int*)((char*)this + 0xE0);
    if (childPtr != 0) {
        AllocatorInterface* alloc = (AllocatorInterface*)FUN_009c8f80();
        alloc->vtable->release(childPtr, 0); // 0 = not sure, maybe flag for immediate deallocation
    }

    // Release second child object (offset +0xDC)
    childPtr = *(int*)((char*)this + 0xDC);
    if (childPtr != 0) {
        AllocatorInterface* alloc = (AllocatorInterface*)FUN_009c8f80();
        alloc->vtable->release(childPtr, 0); 
    }

    // Restore vtable to the base destructed vtable (to allow safe delete after destruction)
    *(int**)this = &PTR_LAB_00e381a0;
}