// FUNC_NAME: EARSObject::ensureSubsystemActivated
void EARSObject::ensureSubsystemActivated()
{
    // Check if subsystem flag bit 0x40000 (bit 18) is not set yet
    if ((*(uint32_t*)(this + 0x0C) & 0x40000) == 0)
    {
        // Set the bit to mark subsystem as activated
        *(uint32_t*)(this + 0x0C) |= 0x40000;

        // Call the actual subsystem initialization routine
        // (offset 0x0051b120)
        this->activateSubsystem(); // placeholder name for FUN_0051b120
    }
}