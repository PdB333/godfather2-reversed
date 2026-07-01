// FUNC_NAME: Player::handleEvent

// External function declarations (assumed global)
void releaseComponent(int componentPtr);
void setActiveFlag(int flag);
void resetEventSystem();
void processEventData(int eventType, int data1, int data2);

void __thiscall Player::handleEvent(int thisPtr, int eventType)
{
    // Release the component at offset +0x74 (e.g., a sub-object like weapon or vehicle)
    releaseComponent(*(int*)(thisPtr + 0x74));
    // Clear the active flag (0 = inactive)
    setActiveFlag(0);
    // Reset the global event system
    resetEventSystem();
    // Process the event with data from offsets +0x80 and +0x88 (e.g., target or state data)
    processEventData(eventType, *(int*)(thisPtr + 0x80), *(int*)(thisPtr + 0x88));
}