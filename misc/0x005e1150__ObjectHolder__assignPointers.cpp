// FUNC_NAME: ObjectHolder::assignPointers
// Address: 0x005e1150
// This function likely manages reference-counted assignment of two interface pointers (objA and objB).
// It stores objA at offset 0x0c and a derived interface from objB at offset 0x10.
// vtable layout for objA: +0 = QueryInterface, +4 = AddRef, +8 = Release, +0xC = SomeMethod
void __thiscall ObjectHolder::assignPointers(IUnknown* objA, IUnknown* objB) {
    IUnknown* a = objA;
    int interfacePtr;

    // Release the existing objA (if any)
    if (objA) {
        objA->Release(); // vtable+8
    }

    // If objB is non-null, obtain a secondary interface from objB to objA
    if (objB) {
        interfacePtr = getInterface(objB, a); // FUN_004265d0
    } else {
        interfacePtr = 0;
    }

    initObject(a, interfacePtr); // FUN_005e1480

    // Store objA at this+0x0c
    this->m_pObjA = a;

    // Release objA again? Possibly to counter a temporary AddRef from getInterface
    if (objA) {
        objA->Release(); // vtable+8
    }

    if (objB != 0) {
        // Obtain another interface from objB to the stored m_pObjA
        interfacePtr = getInterface(objB, this->m_pObjA); // FUN_004265d0
        this->m_pObjBInterface = interfacePtr; // Store at this+0x10
        objB->AddRef(0); // vtable+4, note: second argument 0 is unusual but preserved
        objA->SomeMethod(); // vtable+0xc
    } else {
        this->m_pObjBInterface = 0;
        objA->SomeMethod(); // vtable+0xc
    }
    return;
}