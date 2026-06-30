// FUNC_NAME: SomeClass::dispatchEvent
// Function at 0x006903d0 - dispatches an event to a virtual method, likely part of EARS event system
// Registers: ESI = this (object), EDI = optional context pointer
void SomeClass::dispatchEvent(undefined4 param2) // param2 might be event type or additional data
{
    // Check if this pointer is valid
    if (this != nullptr) 
    {
        // Create an event object (likely a 64-bit or 8-byte structure)
        uint64_t eventObj = FUN_00496470(); // e.g. createEvent
        
        // If context pointer (EDI) is set, process it (e.g. serialize or initialize event)
        if (/* unaff_EDI */ contextPointer != 0) 
        {
            FUN_00496780(&eventObj); // e.g. serializeEvent
        }
        
        // Call virtual function at vtable+0x4 (second function) with param2 and event object
        // This is likely a virtual method like handleEvent(uint32 param, Event& event)
        (this->vtable[1])(param2, eventObj);
        
        // Finalize event dispatch (e.g. send/publish)
        FUN_00497960((uint32_t)eventObj, this, param2); // e.g. dispatchEventToListeners
    }
}