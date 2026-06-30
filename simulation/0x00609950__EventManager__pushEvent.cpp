// FUNC_NAME: EventManager::pushEvent
// Address: 0x00609950
// Stores two parameters and a zero into a fixed-size event queue (max 8 entries).
// The queue uses three separate global arrays for data1, data2, and flags,
// with a global counter tracking the number of stored events.
// Arrays:
//   sEventCount (0x00f15a6c) - uint32 counter
//   sEventData1 (0x01205768) - first data array (6-byte stride per entry)
//   sEventData2 (0x0120576c) - second data array (6-byte stride)
//   sEventFlags (0x01205770) - flag array (24-byte stride per entry)
// Parameters are likely pointers or handles (unknown semantics).

void EventManager::pushEvent(uint32_t param1, uint32_t param2)
{
    int32_t* eventCount = (int32_t*)0x00f15a6c;
    int32_t count = *eventCount;

    if (count < 8)
    {
        // Offsets derived from current count; note the different strides (6 vs 24)
        int offset6 = count * 6;
        int offset24 = count * 24;

        // Store the two parameters
        *(uint32_t*)(0x01205768 + offset6) = param1;
        *(uint32_t*)(0x0120576c + offset6) = param2;

        // Store a zero (possibly a ready flag or unused field)
        *(uint32_t*)(0x01205770 + offset24) = 0;

        // Advance the counter
        *eventCount = count + 1;
    }
}