// FUNC_NAME: EARSObject::EARSObject(byte contructFlag)

extern int* g_pGlobalTable; // DAT_01223410

int __thiscall EARSObject::EARSObject(byte contructFlag) {
    // Invoke base constructor or object initialization routine
    FUN_00479690();

    if (contructFlag & 1) {
        // Retrieve virtual function table from global manager
        // g_pGlobalTable +0x2d4 contains a pointer to a pointer to the vtable
        void** pVtablePtr = *(void***)((char*)g_pGlobalTable + 0x2d4);
        // Dereference to get actual vtable, then call the second virtual function (offset 4 bytes)
        void(*vfunc)(void*, int) = (void(*)(void*, int))pVtablePtr[1];
        vfunc(this, 0);
    }

    return this;
}