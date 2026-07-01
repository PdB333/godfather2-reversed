// FUNC_NAME: SomeClass::InitializeSubObject
void __fastcall SomeClass::InitializeSubObject(int thisObj)
{
    // Get memory manager singleton
    int** memoryManager = (int**)FUN_009c8f80();  // likely GetMemoryManager()
    int allocationFlags[3] = {2, 0x10, 0};       // flags: heap type, alignment, unknown

    // Allocate 0xA0 bytes via memory manager vtable
    int* allocated = (int*)(*(code**)*memoryManager)(0xA0, &allocationFlags);

    if (allocated != 0) {
        FUN_0060ffd0();                      // init sub-object (constructor/init)
        allocated[0x90 / 4] = 0;             // clear field at +0x90
        allocated[0x94 / 4] = 0;             // clear field at +0x94
    }

    // Store allocated sub-object in this at +0x18
    *(int**)(thisObj + 0x18) = allocated;

    // Call some function (likely cleanup of flags)
    FUN_004bfbf0(allocationFlags[0]);

    // Call a virtual method on an object at this+0x8
    int* baseObj = *(int**)(thisObj + 8);    // +0x8: pointer to base object
    int** vtable = *(int***)((int)baseObj + 8);  // baseObj->someField at +0x8 is vtable ptr
    (**(code**)(vtable + 1))();             // virtual function at vtable+4 (index 1)

    // Register the allocated sub-object
    allocationFlags[0] = (int)allocated;      // reuse local stack
    FUN_00610160();                           // likely AddRef or Register()
}