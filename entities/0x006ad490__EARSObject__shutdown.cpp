// FUNC_NAME: EARSObject::shutdown
// Address: 0x006ad490
// Destroys sub-object at offset 0x8, then sets vtable to base class vtable for cleanup chain.
void __fastcall EARSObject::shutdown(EARSObject* thisObj)
{
    // Check if the pointer at offset +0x8 (e.g., m_pData) is non-null
    if (thisObj->m_pData != nullptr) {
        // Release/destroy the sub-object pointed to by m_pData
        FUN_004daf90(&thisObj->m_pData);
    }
    // Set vtable to base class vtable (likely EARSObject's own vtable) for proper destruction chain
    thisObj->vfptr = (void**)&PTR_LAB_00e2f0c0;
}