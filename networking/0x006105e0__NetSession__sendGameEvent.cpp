// FUNC_NAME: NetSession::sendGameEvent
void NetSession::sendGameEvent(int param1, int param2, int param3, int param4)
{
    // Allocate buffer for 16 uint32 values (event structure)
    // FUN_0060cd00 likely: allocateBuffer(eventType=0xd, elementSize=4, align=0, flags=1, unknown=0)
    int *eventBuffer = (int *)allocateBuffer(0xd, 4, 0, 1, 0);
    
    if (eventBuffer != nullptr) {
        // Global constants (likely session IDs or event flags)
        int constA = DAT_00e2eff4;  // e.g., some global counter or ID
        int constB = DAT_00e2b1a4;  // another global constant
        
        eventBuffer[0] = constA;
        eventBuffer[1] = constB;
        eventBuffer[2] = param1;
        eventBuffer[3] = param3;
        eventBuffer[4] = constB;
        eventBuffer[5] = constB;
        eventBuffer[6] = param2;
        eventBuffer[7] = param3;
        eventBuffer[8] = constB;
        eventBuffer[9] = constA;
        eventBuffer[10] = param2;
        eventBuffer[11] = param4;
        eventBuffer[12] = constA;
        eventBuffer[13] = constA;
        eventBuffer[14] = param1;
        eventBuffer[15] = param4;
        
        // Submit the event buffer for processing (likely enqueue or send)
        // FUN_0060cde0: processEventBuffer(eventBuffer) or pushToNetworkQueue
        processEventBuffer();
    }
}