// FUNC_NAME: NetSession::dispatchGameEvent
// Address: 0x00730060
// Identified role: Sends a game event through the event system, possibly for network synchronization.
// Parameters:
//   this: NetSession object
//   sender: Pointer to a network connection or player object with a large data block (e.g., PlayerData)
//   eventType: Byte indicating the type of event to dispatch (1, 2, or 5)
void __thiscall NetSession::dispatchGameEvent(int this, int* sender, char eventType)
{
    int id1, id2;
    int localId;
    // Stack-allocated event structures
    struct EventA { /* sized 0x28? */ } eventA;
    struct EventB { /* sized 0x28? */ } eventB;

    // Check if we already processed this sender: compare cached ID with sender's ID at large offset
    if (*(int*)(this + 0x2138) == sender[0x7b5])
        return;

    // Call a virtual function on the sender object (index 0x230) to get an identifier
    id1 = (*(int (__thiscall**)(int*))(*sender + 0x230))(sender);
    // Get local player/object identifier (likely from a global or static)
    localId = getLocalPlayerId();

    // If the identifier matches this session, or is non-zero and matches the local ID
    if ((id1 == this) || (id1 != 0 && (id2 = FUN_007ff880(), id1 == id2)))
    {
        // Prepare eventA with a specific event type hash 0x5822766
        eventA.m_type = 0x5822766;
        eventA.m_vtable = &PTR_FUN_00d5dbbc; // Event base vtable
        eventA.m_data = sender[0x12];         // Save sender list pointer
        eventA.m_next = nullptr;
        eventA.m_flags = 0;
        eventA.m_userData = DAT_01205228;     // Some global constant

        // If sender has a linked list head (at +0x12), insert eventA into it temporarily
        if (sender + 0x12 != nullptr)
        {
            eventA.m_next = (int*)sender[0x13]; // Save old next
            sender[0x13] = (int)&eventA.m_next; // Insert eventA into list
            eventA.m_data = (int)(sender + 0x12); // Point back to head
        }

        // Dispatch eventA to the event listener list at this+0x3c
        dispatchEvent(&eventA, (void*)(this + 0x3c), 0);

        // Remove the temporary node from the list (if inserted)
        if (eventA.m_next != nullptr)
            removeFromList(&eventA.m_next);
    }

    // Prepare eventB with type based on eventType
    eventB.m_type = 0;
    eventB.m_vtable = &PTR_FUN_00d5dbbc;
    eventB.m_flags = 0;
    eventB.m_userData = DAT_01205228;

    if (eventType == 1)
        eventB.m_type = 0xb6988728;
    else if (eventType == 2)
        eventB.m_type = 0x23f3d3fd;
    else if (eventType == 5)
        eventB.m_type = 0x7b35500e;
    else
        eventB.m_type = 0xb6988728; // Default case matches eventType==1? Check decompilation: actually it falls through to 0xb6988728 for non-1/2/5.

    // Insert eventB into the sender's list similarly
    eventB = {0};
    eventB.m_vtable = &PTR_FUN_00d5dbbc;
    eventB.m_userData = DAT_01205228;
    if (sender + 0x12 != nullptr)
    {
        eventB.m_next = (int*)sender[0x13];
        sender[0x13] = (int)&eventB.m_next;
        eventB.m_data = (int)(sender + 0x12);
    }

    // Dispatch eventB
    dispatchEvent(&eventB, (void*)(this + 0x3c), 0);

    // Remove temporary node
    if (eventB.m_next != nullptr)
        removeFromList(&eventB.m_next);
}