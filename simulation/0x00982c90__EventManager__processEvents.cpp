// FUNC_NAME: EventManager::processEvents

// Address: 0x00982c90
// EA EARS engine event processing system.
// Iterates through an array of pending events, finds one ready to process (bit 3 set, bit 4 clear),
// marks it as processing (bit 4), and returns.
// If none found, invokes the active callback, then checks if the queue is completely empty
// and calls a virtual finalization method.

void __fastcall EventManager::processEvents(EventManager* this)
{
    bool bFoundReady = false;

    // Iterate over pending event array (m_pEventArray at +0x50, count at m_eventCount +0x6C)
    if (this->m_eventCount != 0)
    {
        uint32_t i = 0;
        do
        {
            EventObject* pEvent = this->m_pEventArray[i]; // m_pEventArray[i] at +0x50 + i*4

            // Check bit 3 (0x08) - "ready to process" flag
            if ((pEvent->flags >> 3 & 1) != 0)
            {
                bFoundReady = true;

                // Check bit 4 (0x10) - "already being processed" flag
                if ((pEvent->flags >> 4 & 1) == 0)
                {
                    // Mark as processing and return (early exit)
                    pEvent->flags |= 0x10;
                    return;
                }
            }
            i++;
        } while (i < this->m_eventCount);
    }

    // No new event started processing; handle current active callback (m_pCurrentCallback at +0x68)
    if (this->m_pCurrentCallback != nullptr)
    {
        // Callback object layout: vtable at +0, data at +8, function pointer at +0x14
        if (this->m_pCurrentCallback->vtable != nullptr)
        {
            this->m_pCurrentCallback->vtable->invokeCallback(
                this->m_pCurrentCallback->data,
                this->m_pCurrentCallback,
                1);
        }
        this->m_pCurrentCallback = nullptr;
    }

    // If no pending event was found at all, try to finalize the queue
    if (!bFoundReady)
    {
        // Sub-object at +0x10 (possibly base class or state machine)
        sendNotification(&this->m_subObject, &MSG_QUEUE_EMPTY, 1); // send "queue empty" message

        // Check if queue is completely drained: no events, no other counter, no active callback
        if (this->m_eventCount == 0 && this->m_field_1F == 0 && this->m_pCurrentCallback == nullptr)
        {
            sendNotification(&this->m_subObject, &MSG_QUEUE_EMPTY, 1); // second notification (duplicate?)

            // Virtual call at vtable offset 0x2c: finalize / cleanup
            this->vtable->onQueueDrained();
        }
    }
}