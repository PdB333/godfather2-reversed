// FUNC_NAME: SomeClass::releaseAndDestroy
void SomeClass::releaseAndDestroy(void)
{
    // this pointer is in unaff_ESI (likely ESI holds 'this')
    int* thisPtr = unaff_ESI; // this is what unaff_ESI really is
    int iVar1;
    
    iVar1 = thisPtr[0]; // +0x00: first pointer field (e.g., m_pSomeList)
    if (iVar1 != 0) {
        if (*(int *)(iVar1 + 8) != 0) { // +0x08: some child pointer
            FUN_00573f70(*(int *)(iVar1 + 8)); // releaseChild or similar
        }
        if (*(int *)(iVar1 + 0xc) != 0) { // +0x0C: another child
            FUN_00573f70(*(int *)(iVar1 + 0xc));
        }
        // Call a virtual method on the object (vtbl+4) to destroy it
        (**(code **)(*(int *)thisPtr[3] + 4))(iVar1, 0); // thisPtr[3] might be a vtbl pointer or factory
        thisPtr[1] = thisPtr[1] - 1; // +0x04: reference count?
    }
    thisPtr[0] = 0; // +0x00: null out pointer
    if (thisPtr[2] != 0) { // +0x08: another pointer
        (**(code **)(*(int *)thisPtr[3] + 4))(thisPtr[2], 0);
    }
    // Call virtual method at vtbl+0x0C to destroy 'this'
    (**(code **)(*(int *)thisPtr[3] + 0xc))();
    return;
}