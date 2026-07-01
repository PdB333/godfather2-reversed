// FUNC_NAME: BaseObject::finalizePendingAction
void __fastcall BaseObject::finalizePendingAction(void)
{
    // Check if bit 1 (0x2) of flags at offset 0x30 is set and pointer at 0x38 is non-null
    if (((m_flags >> 1) & 1) != 0 && m_pendingPtr != nullptr)
    {
        // Call release/cleanup routine on the sub-object at offset 0x2C
        releaseSubObject(&m_subObject);  // FUN_009f1b20
        // Clear bit 1 in flags
        m_flags &= ~2;
    }
}