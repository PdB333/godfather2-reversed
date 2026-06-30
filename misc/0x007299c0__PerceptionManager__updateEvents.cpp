// FUNC_NAME: PerceptionManager::updateEvents

void __fastcall PerceptionManager::updateEvents() {
    float threshold = DAT_01205214; // Global max sensing distance (e.g., hearing range)
    uint32_t eventCount = *(int32_t*)(this + 0xa28); // m_eventCount
    if (eventCount != 0) {
        float* eventData = (float*)(this + 0x4c); // m_events array (each entry: 10 floats = 40 bytes)
        uint32_t index = 0;
        do {
            // Compare first float of current event (e.g., distance or time since heard)
            if (threshold < eventData[0] || threshold == eventData[0]) {
                // Event is within threshold – keep it and advance
                index++;
                eventData += 10; // stride to next event struct
            } else {
                // Event exceeds threshold – call remove/handle function for this index
                removeOrHandleEvent(index); // FUN_00729730
            }
        } while (index < eventCount);
    }
}