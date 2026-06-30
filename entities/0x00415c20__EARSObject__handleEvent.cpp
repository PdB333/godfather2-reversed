// FUNC_NAME: EARSObject::handleEvent
// Address: 0x00415c20
// Role: Event handler (likely virtual override) that processes a specific event ID (0x20e5862) by calling the base handler and, if conditions match, updating a sub-object's field at offset 0x84

void __thiscall EARSObject::handleEvent(uint32_t eventId, void* eventData) {
    // Call base class event handler (FUN_00415370)
    handleBaseEvent(eventId, eventData);

    // Check for the specific event hash 0x20e5862 and non-null data
    if ((eventId == 0x20e5862) && (eventData != nullptr)) {
        // Get pointer to sub-object stored at this+0x80
        void* subObject = *(void**)(this + 0x80);  // +0x80: sub-object pointer
        if (subObject != nullptr) {
            // Obtain a new value (e.g., timestamp, sequence number) from helper
            int32_t newValue = generateNewValue();  // FUN_004151d0
            // Write the value into the sub-object at offset 0x84
            *(int32_t*)((char*)subObject + 0x84) = newValue;  // +0x84: field in sub-object
        }
    }
}