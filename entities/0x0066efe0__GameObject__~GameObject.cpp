// FUNC_NAME: GameObject::~GameObject
// Address: 0x0066efe0
// Role: Derived class destructor; sets derived vtable, optionally calls virtual function on a sub-object (at +0xA1C), then calls base destructor (FUN_00aa1900).

void __thiscall GameObject::~GameObject(void)
{
    // Set derived vtable pointer (vtable at 0x00e444d0)
    this->vtable = (void*)&PTR_FUN_00e444d0;

    // Check sub-object pointer at offset +0xA1C (0x287 * 4)
    void* subObj = *(void**)((char*)this + 0xA1C);
    if (subObj != nullptr)
    {
        // Call virtual function at index 3 (offset 12 bytes) on the sub-object
        // The sub-object's vtable is the first 4 bytes of subObj.
        int* subVtable = *(int**)subObj;
        // __fastcall function taking the sub-object as 'this' in ECX
        typedef void (__fastcall *SubObjVFunc)(void* thisPtr);
        SubObjVFunc func = (SubObjVFunc)(subVtable[3]); // vtable[3] = offset 12
        func(subObj);
    }

    // Call base class destructor (FUN_00aa1900)
    FUN_00aa1900();
}