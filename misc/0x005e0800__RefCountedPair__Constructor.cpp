// FUNC_NAME: RefCountedPair::Constructor
int RefCountedPair::Constructor(int this, int* pRefCountedObj, int pOther)
{
    int* pObj = pRefCountedObj;
    int tempRef;

    // AddRef the object (vtable+8 is AddRef)
    (*(code**)*pObj)(pObj);

    // If pOther is non-null, duplicate the reference from pOther to pObj
    if (pOther == 0) {
        tempRef = 0;
    } else {
        tempRef = FUN_004265d0(pOther, pObj); // duplicateRefCounted
    }

    FUN_005e1150(pObj, tempRef); // store duplicate result internally

    // Store pRefCountedObj into member at offset 0x14
    *(int**)(this + 0x14) = pRefCountedObj;

    // AddRef again (second increment)
    (*(code**)*pObj)();

    if (pOther != 0) {
        // Duplicate reference from pOther to the stored object
        tempRef = FUN_004265d0(pOther, *(int**)(this + 0x14));
        *(int*)(this + 0x18) = tempRef; // store at offset 0x18

        // Release the original pOther reference (vtable+4 is Release)
        (*(code**)(*pRefCountedObj + 4))(pOther, 0);

        // Finalize (vtable+0xc is some cleanup)
        (*(code**)(*pRefCountedObj + 0xc))();

        return this;
    }

    *(int*)(this + 0x18) = 0; // clear second member

    // Finalize
    (*(code**)(*pRefCountedObj + 0xc))();

    return this;
}