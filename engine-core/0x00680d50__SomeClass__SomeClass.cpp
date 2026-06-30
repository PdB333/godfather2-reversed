// FUNC_NAME: SomeClass::SomeClass
int __thiscall SomeClass::SomeClass(void *thisObj, byte allocFlags) {
    undefined4 *vtablePtr;
    
    if (thisObj == nullptr) {
        vtablePtr = nullptr;
    } else {
        vtablePtr = (undefined4 *)((int)thisObj + 0x20);  // vtable at offset 0x20
    }
    *vtablePtr = &kClassVTable;           // Set vtable pointer
    g_GlobalFlag = 0;                     // Clear global flag at 0x011298f0
    baseInit();                           // Internal initialization (FUN_007edfb0)
    if ((allocFlags & 1) != 0) {
        customDealloc(thisObj);           // Deallocation if flag bit 0 set (FUN_009c8eb0)
    }
    return (int)thisObj;
}