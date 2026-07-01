// FUNC_NAME: EARSObject::deactivate
void __fastcall EARSObject::deactivate(void)
{
    // Check if the object's active flag at offset +0x180 is set
    if (this->m_bIsActive) // +0x180
    {
        // Perform global cleanup/shutdown (likely removes from manager or decrements refcount)
        FUN_004df600();
        // Call virtual function at vtable index 0x28 (10th entry) with parameter 0x20 (e.g., stop reason)
        (*(void (__fastcall **)(int))(*((int *)this->m_pSomeTable + 0x28)))(0x20);
        // Clear the active flag
        this->m_bIsActive = false;
    }
}