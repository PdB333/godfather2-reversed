// FUNC_NAME: EARSObject::releaseReference
void __fastcall EARSObject::releaseReference(int thisPtr)
{
    // Check if reference count (or active flag) at +0x7c is non-zero
    if (*(short *)(thisPtr + 0x7c) != 0) {
        // Unregister/cleanup via the global manager instance at DAT_012069c4
        ManagerClass::unregisterItem(&g_manager);
    }
}