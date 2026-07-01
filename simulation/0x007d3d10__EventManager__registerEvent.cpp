// FUNC_NAME: EventManager::registerEvent
// Address: 0x007d3d10
// Role: Registers an event handler by storing a pointer to an event source and subscribing to a specific event hash.
// Offsets: this+0x7c = m_pEventSource (pointer to event source object)
//          this+0x88 = m_eventFlags (flags set based on subscription result)
//          this+0x84 = m_existingFlags (assumed, used in bitwise AND)

void __thiscall EventManager::registerEvent(void* pEventSource)
{
    // Store the event source pointer
    this->m_pEventSource = pEventSource;  // +0x7c

    // Initialize the event source (likely sets up vtable or internal state)
    pEventSource->init();  // FUN_007ff8a0

    // Prepare output pointer (initially null) for the virtual function
    void* pResult = nullptr;

    // Call virtual function at vtable offset 0x10 (4th method) on the event source
    // This function takes an event hash and a pointer to a pointer (output)
    // Returns non-zero if the subscription succeeded
    bool bSubscribed = pEventSource->subscribeEvent(0x7c32d73b, &pResult);

    // Update event flags: if subscribed, copy existing flags; otherwise clear
    // Note: unaff_ESI is assumed to be a member variable at this+0x84 (m_existingFlags)
    this->m_eventFlags = bSubscribed ? this->m_existingFlags : 0;  // +0x88
}