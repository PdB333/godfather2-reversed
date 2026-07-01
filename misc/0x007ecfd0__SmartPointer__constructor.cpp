// FUNC_NAME: SmartPointer::constructor
int __thiscall SmartPointer::constructor(SmartPointer *this, int *refCountedObj, int copyFlag)
{
    int *localPtr = refCountedObj;
    // Call vtable[2] (likely AddRef) on the referenced object
    (*(code **)(*refCountedObj + 8))(refCountedObj);

    int duplicateResult;
    if (copyFlag == 0) {
        duplicateResult = 0;
    } else {
        duplicateResult = FUN_004265d0(copyFlag, localPtr); // Duplicate/copy operation
    }

    // Initialize wrapper internal state (likely a counter or handle)
    FUN_007ece40(localPtr, duplicateResult);

    this->m_pObject = refCountedObj; // +0x8
    // Call AddRef again (increment reference count)
    (*(code **)(*refCountedObj + 8))();

    if (copyFlag != 0) {
        duplicateResult = FUN_004265d0(copyFlag, this->m_pObject);
        this->m_nHandle = duplicateResult; // +0xC
        // Release the original (param_3) reference
        (*(code **)(*refCountedObj + 4))(copyFlag, 0);
        // Call vtable[3] (likely some finalize or notify)
        (*(code **)(*refCountedObj + 0xC))();
        return (int)this;
    }

    this->m_nHandle = 0;
    (*(code **)(*refCountedObj + 0xC))();
    return (int)this;
}