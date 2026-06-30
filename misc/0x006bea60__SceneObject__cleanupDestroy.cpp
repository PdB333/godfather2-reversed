// FUNC_NAME: SceneObject::cleanupDestroy
void __fastcall SceneObject::cleanupDestroy(SceneObject* this)
{
    int iVar1;
    uint uVar2;
    
    // Set vtable pointers to base class destructor vtables for safe chaining
    this->vtable0 = &PTR_LAB_00d5ebb0;  // +0x00
    this->vtable1 = &PTR_LAB_00d5eb9c;  // +0x04
    
    // Check if state at +0x40 is not 0 or 1 (likely initialization states)
    if ((this->state != 0) && (this->state != 1)) {
        // Release a sub-component stored at (this->m_pSubObj + 0x38)
        FUN_0093ea60(*(undefined4 *)(this->m_pSubObj + 0x38));
    }
    
    // If registered with global manager (check flag bit 1 at +0x34)
    if (((((uint)this->flags >> 1 & 1) != 0) &&
         (**(int **)(DAT_012233a0 + 4) != 0) &&
         (**(int **)(DAT_012233a0 + 4) != 0x1f30)) &&
        (iVar1 = FUN_0043b870(DAT_01131018), iVar1 != 0))
    {
        // Unregister from manager using secondary pointer at +0x04
        FUN_009af0a0(this + 1);
    }
    
    // Release elements of first resource array (count at +0x20)
    uVar2 = 0;
    if (this->firstArrayCount != 0) {
        do {
            FUN_00791350(this); // Releases next array element using internal state
            uVar2 = uVar2 + 1;
        } while (uVar2 < (uint)this->firstArrayCount);
    }
    
    // Release elements of second resource array (count at +0x2c)
    uVar2 = 0;
    if (this->secondArrayCount != 0) {
        do {
            FUN_00791350(this);
            uVar2 = uVar2 + 1;
        } while (uVar2 < (uint)this->secondArrayCount);
    }
    
    // Global cleanup (likely ref-count decrement or memory pool cleanup)
    FUN_006b5790();
    
    // Delete two member pointers at +0x28 and +0x1c
    if (this->m_pPointer1 != 0) {
        FUN_009c8f10(this->m_pPointer1); // safeDelete
    }
    if (this->m_pPointer2 != 0) {
        FUN_009c8f10(this->m_pPointer2); // safeDelete
    }
    return;
}