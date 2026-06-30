// FUNC_NAME: RefCountPtr::RefCountPtr (constructor) / 0x005fbd30
// This function initializes a reference-counted wrapper object.
// param_1 (this) - pointer to the wrapper object (offsets: +0x10 = m_pObject, +0x14 = m_refCountOrHandle)
// param_2 (pObj) - pointer to an object with a virtual table (vtable offsets: +4, +8, +0xC)
// param_3 (pExtra) - optional extra pointer/object for reference counting
// Returns this (the initialized wrapper)

class RefCountPtr {
public:
    void* m_pObject;        // +0x10
    int m_refCountOrHandle; // +0x14
};

int FUN_004265d0(void* ptr1, void* ptr2);  // Likely a reference-counting or copy routine
void FUN_005fc2c0(void* ptr, int val);     // Probably sets an internal reference

RefCountPtr* __thiscall RefCountPtr::RefCountPtr(RefCountPtr* this, void* pObj, void* pExtra)
{
    void* pObjCopy = pObj;

    // Call vtable+8 on the source object (e.g., AddRef or initialize)
    ((void (__thiscall*)(void*))(*(int**)pObjCopy)[2])(pObjCopy);  // offset +8

    int handle;
    if (pExtra == nullptr) {
        handle = 0;
    } else {
        handle = FUN_004265d0(pExtra, pObjCopy);
    }

    // Attach the reference/increment to pObj
    FUN_005fc2c0(pObjCopy, handle);

    this->m_pObject = pObjCopy;  // +0x10

    // Second call to vtable+8 (likely same method)
    ((void (__thiscall*)(void*))(*(int**)pObjCopy)[2])(pObjCopy);

    if (pExtra != nullptr) {
        // Obtain another reference using pExtra and stored m_pObject
        int uVar = FUN_004265d0(pExtra, this->m_pObject);
        this->m_refCountOrHandle = uVar;  // +0x14

        // Call vtable+4 with pExtra and 0 (e.g., a method that takes two args)
        ((void (__thiscall*)(void*, void*, int))(*(int**)pObjCopy)[1])(pObjCopy, pExtra, 0);

        // Call vtable+0xC (finalize or other)
        ((void (__thiscall*)(void*))(*(int**)pObjCopy)[3])(pObjCopy);

        return this;
    }

    this->m_refCountOrHandle = 0;  // +0x14

    // Call vtable+0xC (no args)
    ((void (__thiscall*)(void*))(*(int**)pObjCopy)[3])(pObjCopy);

    return this;
}