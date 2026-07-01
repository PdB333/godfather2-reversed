// FUNC_NAME: TimerNode::processEvent
void __thiscall TimerNode::processEvent(int eventId)
{
    // Offset +0x60: countdown timer (decrements each tick)
    this->countdown--;

    // Offset +0x64: stored event ID or handle (may be 0 or have a base offset)
    int *pEventId = (int *)(this + 0x64);
    int normalizedId = 0;
    if (*pEventId != 0)
    {
        normalizedId = *pEventId - 0x48; // Adjust for a possible base (0x48 = 72)
    }

    // Check if the normalized stored ID matches the incoming event ID
    if (normalizedId == eventId)
    {
        // Call to check system state (returns nonzero if active)
        bool isActive = FUN_00909590();
        if (isActive || (*pEventId != 0 && *pEventId != 0x48))
        {
            // Set flags: bit0 and bit2 (possibly "triggered" or "completed")
            *(uint *)(this + 0xb4) |= 5;
        }

        // Offset +0xb0: some state or pointer to clear
        *(undefined4 *)(this + 0xb0) = 0;

        // If the stored ID is non‑zero, release the resource and clear it
        if (*pEventId != 0)
        {
            FUN_004daf90(pEventId); // Release/free resource associated with this ID
            *pEventId = 0;
        }
    }
}