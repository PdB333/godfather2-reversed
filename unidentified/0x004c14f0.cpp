// FUN_004c14f0: SomeClass::setFlagsWithAction
void SomeClass::setFlagsWithAction(uint newFlags)
{
    // Check if the bit 8 (0x8) flag changed between current m_flags and newFlags
    if ((m_flags ^ newFlags) & 8) {
        if (!(newFlags & 8)) {
            // Bit 8 is being cleared (was 1, now 0); call stop/release on global
            FUN_004086d0(&g_someGlobalHandle);
        } else if (g_someGlobalHandle) {
            // Bit 8 is being set (was 0, now 1) and global handle is non-null;
            // remove/disable the action associated with this object's +0x3c member
            FUN_00407e60(this + 0x3c, &g_someGlobalHandle);
        }
    }
    // Always write the new flags value
    m_flags = newFlags;
}