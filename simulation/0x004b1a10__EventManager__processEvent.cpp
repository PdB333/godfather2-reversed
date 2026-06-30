// FUNC_NAME: EventManager::processEvent
void __thiscall EventManager::processEvent(uint eventId, void* eventData)
{
    uint result;
    uint uVar1;
    int index;
    byte flagBit;
    uint* eventDefArray; // from global DAT_012234bc
    EventDefinition* def;
    void* handler;

    // Local array for some temporary data? Actually used for FUN_005e49d0 output
    uint local_24 = 0;
    uint local_20 = 0;
    uint local_1c = 0;
    uint local_18 = 0;
    // Unused label pointer? Possibly debug info
    // local_14 = &LAB_004b1980;

    if (this->m_context != 0) {
        // Acquire lock or enter critical section
        FUN_005dbc10();
        // Get some global object (maybe event manager itself)
        FUN_004dafd0();
        // Look up event definition by eventId (probably hashed or ID)
        result = FUN_005e49d0(g_EventDefinitionArray, &local_24);
    }
    this->m_eventId = result;

    if (result != 0) {
        // Possibly attach data to the event
        FUN_005e6580(result, eventId);
        index = this->m_eventId & 0xFFFF;
        if (index < 0x200) {
            eventDefArray = (uint*)((int)g_EventDefinitionArray + index * 0x30 + 0x10); // +0x10 to skip table header
            if (eventDefArray != 0 && eventDefArray[0x2c / 4] == this->m_eventId) {
                handler = (void*)eventDefArray[0x10 / 4];
                if (handler != 0) {
                    // Set a field in the handler object to eventData
                    *(uint*)((int)handler + 0x5C) = (uint)eventData;
                }
            }
        }
        // Now search for additional handler or flag
        void* context = FUN_004dafd0();
        void* found = FUN_005f0560(context, &eventId, &eventData);
        flagBit = 0;
        if (found != 0 && found != (void*)-0x20) {
            // Extract bit 6 from flags at offset 0x28
            flagBit = (*(uint*)((int)found + 0x28) >> 6) & 1;
        }
        this->m_flag1 = (byte)flagBit;
        this->m_flag2 = 0;
    }
}