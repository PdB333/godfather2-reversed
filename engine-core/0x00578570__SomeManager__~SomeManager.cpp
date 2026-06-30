// FUNC_NAME: SomeManager::~SomeManager
void __thiscall SomeManager::~SomeManager(SomeManager *this)
{
    // vtable pointer set to destruction vtable
    this->vtbl = &PTR_FUN_00e3ac08;

    // Destroy array of objects at offset 0xBB (each object size 0xE0)
    int count = this->arrayCount; // +0xB9
    if (count > 0) {
        int basePtr = this->arrayBase; // +0xBB
        for (int i = 0; i < count; i++) {
            // Each element is a pointer to an object; call its virtual function at index 0 (destructor-like)
            ObjectBase **objPtr = (ObjectBase **)(basePtr + i * 0xE0);
            ObjectBase *obj = *objPtr;
            if (obj != nullptr) {
                obj->vtbl->vfunc0(obj, 0);
            }
        }
    }

    // Free the array memory via global allocator
    g_Allocator->vtbl->deallocate(this->arrayBase, 0); // +4, DAT_0120556c

    // Switch to secondary destruction vtable
    this->vtbl = &PTR_FUN_00e3ac24;

    // Destroy sub-object at offset 0x19
    SubObject *subObj = reinterpret_cast<SubObject *>(this->field_0x19); // +0x19
    if (subObj != nullptr) {
        // Sub-object vtable is at offset 0x10 (4 dwords) from its start
        SubObjectVtbl *subVtbl = subObj->vtbl2; // +0x10
        if (subVtbl != nullptr) {
            subVtbl->destructor1(subObj, 0);   // vtable[1]
            if (subObj->field_0x0C != 0) {      // +0x0C
                subVtbl->destructor1(subObj->field_0x0C, 0);
            }
            subVtbl->destructor3();            // vtable[3]
            g_Allocator->vtbl->deallocate(subObj, 0);
        }
    }
}