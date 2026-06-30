// Xbox PDB: EARS::Framework::Lua::LuaScriptManager::OpenLevel
// FUNC_NAME: EclipseLog::initialize
void __thiscall EclipseLog::initialize() {
    EclipseLogHandle* handle;

    // Create the underlying logging handle (EclipseLog subsystem)
    handle = createEclipseLogHandle();
    this->mHandle = handle; // +0x1c

    // Attach a name to the handle for debugging
    setHandleName(handle, "EclipseLog");

    // Check internal state: if write position >= buffer size, trigger debug assertion
    int handlePtr = *(int*)(this->mHandle + 0x10);
    if (*(uint*)(handlePtr + 0x20) <= *(uint*)(handlePtr + 0x24)) {
        debugAssertFailed(); // FUN_00627360
    }

    // Allocate a new log sink object with vtable at 0x0043e5c0
    LogSink* newSink = (LogSink*)allocateSinkObject(0); // FUN_00638110(0)
    newSink->vtable = (void**)0x0043e5c0; // +0xc

    // Store the sink into the handle's internal buffer (pool)
    int** bufferPtr = *(int***)(handle + 8); // pointer to current free slot
    bufferPtr[1] = (int*)newSink; // store sink pointer at buffer[1]
    *bufferPtr = 6;                // possibly size or type tag
    *(int*)(handle + 8) += 8;      // advance buffer pointer

    // Re‑register the sink into the handle's internal list (undo the allocation?)
    handle = this->mHandle;
    registerSinkInHandle(handle + 0x40,
                         *(int*)(handle + 8) - 0x10,
                         *(int*)(handle + 8) - 8); // FUN_00633d60
    *(int*)(handle + 8) -= 0x10; // revert buffer pointer

    // Iterate over all existing sink list nodes and call their virtual method
    SinkListNode* current = *(SinkListNode**) *(int**)(this + 0x38); // head of node list
    SinkListNode* listHead = *(SinkListNode**)(this + 0x38);
    while (current != listHead) {
        // Debug assertions related to loop safety (probably from an assert macro)
        if (this == (EclipseLog*)-0x20) {
            debugAssertFailed(); // unlikely, but present in original
        }
        if (current == listHead) break;
        if ((int)this == -0x20) {
            debugAssertFailed();
        }
        // Call the virtual method at offset 4 of the sink's vtable (likely `processLog`)
        SinkObject* sink = (SinkObject*)current->sink; // current[2] = offset 8
        sink->vtable[1](this->mHandle);
        if (current == listHead) {
            debugAssertFailed();
        }
        current = current->next; // current[0] = next pointer
    }
}