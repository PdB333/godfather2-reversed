// FUNC_NAME: EARSObject::setActiveState
// Function address: 0x00450340
// This method controls activation/deactivation of a feature, using a flag at +0x94 (bit 3) 
// and storing the desired state at +0x90. When deactivating from an active state (flag set),
// it calls a deactivation handler at 0x0049feb0.
void EARSObject::setActiveState(int enable)
{
    // Check the current activation flag (bit 3) at offset +0x94
    if ((*(uint32_t*)(this + 0x94) & 8) == 0)
    {
        // Currently inactive: only act if enabling
        if (enable == 0)
            return;
        // Set the activation flag
        *(uint32_t*)(this + 0x94) |= 8;
    }
    else if (enable == 0)
    {
        // Currently active and disabling: call deactivation handler
        FUN_0049feb0(0);
        // Clear the activation flag
        *(uint32_t*)(this + 0x94) &= 0xFFFFFFF7;
        return;
    }
    // Store the enable value at +0x90
    *(int32_t*)(this + 0x90) = enable;
}