// FUNC_NAME: InputManager::enqueueControllerEvent
void __thiscall InputManager::enqueueControllerEvent(int thisPtr, uint slotIndex, int addFlag)
{
    // Check if we should actually enqueue, and slot is within the 16 controller slots
    if ((addFlag != 0) && (slotIndex < 0x10))
    {
        // Each slot is 0x18 bytes, array starts at offset +0x14
        InputManagerControllerSlot* slot = (InputManagerControllerSlot*)(thisPtr + 0x14 + slotIndex * 0x18);
        if (slot != nullptr) // Redundant, but kept from decompiled logic
        {
            // Get current event ID from the manager (e.g., button/action ID)
            uint32_t eventId = InputManager::getCurrentEventId(thisPtr);
            if (eventId != 0)
            {
                // Allocate a new event node
                InputManagerEventNode* newNode = InputManager::allocateEventNode();
                if (newNode != nullptr)
                {
                    // Mark slot as having a pending event (bit 0)
                    slot->flags |= 1;
                    // Prepend the new node to the slot's event list
                    newNode->next = slot->head;
                    slot->head = newNode;
                    // Fill in event data: event ID and global timestamp
                    newNode->eventId = eventId;
                    newNode->timestamp = g_globalTimestamp; // Global timer value
                }
            }
        }
    }
}