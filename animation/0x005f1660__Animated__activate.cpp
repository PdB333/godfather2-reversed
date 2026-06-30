//FUNC_NAME: Animated::activate
// Function address: 0x005f1660
// Role: Activates the animated object if not already active and pending count > 0.
// Flags at +0x10: bit 6 (0x40) = active, bit 5 (0x20) = unknown (cleared on activation)
// Counter at +0x18: pending activation count

void Animated::activate()
{
    // Check if this is valid and the object is not already active
    if (this != nullptr && (*(uint8_t*)(this + 0x10) & 0x40) == 0)
    {
        // If there is a pending activation count, process it
        if (*(int32_t*)(this + 0x18) > 0)
        {
            // Call internal activation functions (likely start/stop animation)
            this->onActivate();      // FUN_005f57b0
            this->onActivateComplete(); // FUN_005f5730
            // Reset the pending count
            *(int32_t*)(this + 0x18) = 0;
        }
        // Set the active flag and clear bit 5
        *(uint16_t*)(this + 0x10) = (*(uint16_t*)(this + 0x10) & 0xFFDF) | 0x40;
    }
}