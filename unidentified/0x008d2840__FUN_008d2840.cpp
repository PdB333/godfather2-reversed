// FUNC_NAME: SomeClass::~SomeClass
void* __thiscall SomeClass::~SomeClass(void* thisObj, byte shouldDelete) {
    // Set vtable pointer to base class vtable
    *(void**)thisObj = (void*)&PTR_FUN_00d7d3d8; // +0x00: vtable pointer

    // Destroy sub-object at offset 0x3C (thisObj[0xf])
    if (*(void**)((char*)thisObj + 0x3c) != nullptr) {
        FUN_009c8f10(*(void**)((char*)thisObj + 0x3c)); // release/deallocate
    }

    // Destroy sub-object at offset 0x28 (thisObj[10])
    if (*(void**)((char*)thisObj + 0x28) != nullptr) {
        FUN_009c8f10(*(void**)((char*)thisObj + 0x28)); // release/deallocate
    }

    // If shouldDelete has bit 0 set, free this object's memory
    if (shouldDelete & 1) {
        FUN_009c8eb0(thisObj); // deallocation (operator delete)
    }

    return thisObj;
}