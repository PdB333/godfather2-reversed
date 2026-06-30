// FUNC_NAME: EARSObject::constructor
int __thiscall EARSObject::constructor(EARSObject* thisObj, byte flags) {
    // Call base class constructor (likely SimObject or EARSObject base)
    FUN_0046c640();

    if (flags & 1) {
        // Call a virtual function from the class's vtable
        // The class vtable is stored in a global table at offset 0x2d4 from g_classVtableBase
        // The function at offset 4 (index 1) is called with argument 0
        void (__thiscall* vfunc)(EARSObject*, int) = 
            (void (__thiscall*)(EARSObject*, int))((*(int**)g_classVtableBase)[0x2d4])[1];
        vfunc(thisObj, 0);
    }

    return (int)thisObj;
}