// FUNC_NAME: DialogTreeManager::handleDialogEvent
// Address: 0x007fb9f0
// Role: Processes a dialog event from an event source, possibly playing a dialog line with audio.

void __thiscall DialogTreeManager::handleDialogEvent(
    DialogTreeManager* this,
    DialogEventSource* eventSource,
    float volume
) {
    // Temporary sink/listener node for event source callbacks
    SinkNode tempSink;
    SinkNode tempSink2;

    // Validate event source and check its "isActive" virtual method (vtable+0x78)
    if (eventSource == nullptr) {
        return;
    }
    if (!eventSource->isActive()) {
        return;
    }

    // Begin message or lock (unknown, possibly a mutex acquire or message buffer start)
    FUN_0084dd20();

    // Compute the address of the event source's sink node or reference (this+0x48)
    int* sinkTarget = (this != nullptr) ? (int*)((char*)this + 0x48) : nullptr;

    // --- First sink registration (tempSink) ---
    if (tempSink.pointer != sinkTarget) {
        if (tempSink.pointer != nullptr) {
            FUN_004daf90(&tempSink); // release old ref
        }
        tempSink.pointer = sinkTarget;
        if (sinkTarget != nullptr) {
            // Store the address of tempSink into sinkTarget's next field (+4)
            tempSink.next = *(int**)((char*)sinkTarget + 4);
            *(int**)((char*)sinkTarget + 4) = &tempSink;
        }
    }

    // --- Second sink registration (tempSink2) ---
    if (tempSink2.pointer != tempSink.pointer) {
        if (tempSink2.pointer != nullptr) {
            FUN_004daf90(&tempSink2);
        }
        tempSink2.pointer = tempSink.pointer;
        if (tempSink.pointer != nullptr) {
            tempSink2.next = *(int**)((char*)tempSink.pointer + 4);
            *(int**)((char*)tempSink.pointer + 4) = &tempSink2;
        }
    }

    // Retrieve audio manager or sound system object (FUN_00471610)
    AudioManager* audioManager = (AudioManager*)FUN_00471610();

    // Read 64-bit value from audioManager+0x30 (timestamp or context ID)
    __int64 audioContext = *(__int64*)((char*)audioManager + 0x30);

    // Query event source's volume (vtable+0xc0)
    float sourceVolume = eventSource->getVolume();  // virtual at offset 0xc0
    if (sourceVolume <= 0.0f) {
        volume = 0.0f;  // Override volume if source indicates inactive
    }

    // Build dialog message structure (stack based)
    DialogMessage msg;
    msg.flags = 8;                         // OR 8 into local flags
    msg.globalId = DAT_01205224;           // Global sound/line ID
    msg.sourceId = *(uint*)((char*)this + 0x6dc) >> 2;  // Source ID from this
    msg.volume = volume;
    msg.unknown1 = 1;                      // Likely priority or type
    msg.unknown2 = 2;                      // Another parameter

    // Send message via FUN_00408bb0 (post message to queue)
    // Uses global message queue DAT_0112dd94, event source type at offset 0xf, buffer, flags
    FUN_00408bb0(&DAT_0112dd94, (char*)eventSource + 0xf, &msg, 0);

    // Check if dialog can actually play now (FUN_00481660)
    bool canPlay = FUN_00481660(); // returns char (bool)
    if (canPlay) {
        // Execute dialog playback sequence
        FUN_0084d330();                   // Begin dialog lifecycle
        FUN_0084dda0(&msg);               // Set dialog line data from message
        FUN_0070b6a0();                   // Play voice over or audio
        FUN_004a8ec0((char*)eventSource + 0x16); // Set dialog context from event source field
        FUN_0084e1c0();                   // Finalize setup
    }

    // Cleanup: release temporarily registered sinks
    if (tempSink.pointer != nullptr) {
        FUN_004daf90(&tempSink);
    }
    if (tempSink2.pointer != nullptr) {
        FUN_004daf90(&tempSink2);
    }

    // (No explicit return; function ends)
}