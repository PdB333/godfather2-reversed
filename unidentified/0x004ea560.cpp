// FUN_004ea560: EventQueue::pushEvent
void EventQueue::pushEvent(int eventType, int unknownPtr, int data1, int data2, int data3, int forceImmediate)
{
    // Get the global App object via TLS (FS segment)
    int* appObject = **(int**)(__readfsdword(0x2c));  // TEB+0x2c -> process data
    int updatePhase = *(int*)(appObject + 0x34);      // +0x34: current update phase (0=pre-update, 1=active, etc.)

    // Decide which buffer to use: phase==0 ? phase0 : phase1
    int* eventListBase = &this->phase0_count + (updatePhase != 0) * 0x26;  // offset by 38 ints for phase1
    int* eventCount = eventListBase + 1;  // skip the main flag? Actually eventListBase points to the correct list header
    // Wait: recalc: param_1 is 'this', and the condition for adding is:
    bool shouldQueue = (updatePhase != 1) || (this->m_bActive == 0) || (forceImmediate == 2);

    if (shouldQueue)
    {
        // Choose the event list buffer based on phase
        int* eventBuffer = &this->m_bActive + 1;  // base of phase0 list
        if (updatePhase != 0)
        {
            eventBuffer = &this->phase1_count;  // start of phase1 list
        }
        // eventBuffer now points to the count field of the chosen list

        // Override data2 and data3 if phase==0
        if (updatePhase == 0)
        {
            if (eventType == g_someGlobalEventType)  // DAT_012054f0
            {
                data2 = 8;
            }
            else
            {
                data2 = getSomeValue1();  // FUN_004e9d00
                data3 = getSomeValue2();  // FUN_004e9d40
            }
        }

        // Write event data into the queue
        int index = *eventBuffer;  // current count
        // Each event occupies 4 ints, stored after a 2-int header (count, unknown)
        int* eventSlot = eventBuffer + index * 4 + 2;  // skip two ints per entry
        eventSlot[0] = eventType;       // +0
        eventSlot[1] = data1;           // +1
        eventSlot[2] = data2;           // +2
        eventSlot[3] = data3;           // +3

        // If we are in a non-zero update phase and the event type has a non-zero callback pointer, validate it
        if ((updatePhase != 0) && (*(int*)(eventType + 0x178) != 0))
        {
            validateEventSender(unknownPtr);  // FUN_004e9a30
        }

        // Increment the event count
        (*eventBuffer)++;
    }

    // After queueing (or even if not queued), decide whether to process immediately
    bool shouldProcess = ((updatePhase == 1) && (this->m_bActive != 0)) || (forceImmediate == 2);
    if (shouldProcess)
    {
        processEventImmediate(eventType, unknownPtr, data1, data2, data3, (updatePhase != 0));  // FUN_004ea470
    }
}