// FUNC_NAME: StreamManager::addStream
void __thiscall StreamManager::addStream(StreamManager* this, uint param2, uint param3)
{
    // Call virtual function at vtable offset 0xc (likely base initializer)
    (this->vtable[3])();

    // Increment global stream reference count
    g_streamRefCount++;

    // Local buffer (probably a GUID or hash)
    uint8 buffer[0x14] = {0};

    // Call external function to resolve stream data (e.g., load from asset index)
    FUN_00654c00(param2, buffer, param3);

    // Decrement global reference count
    g_streamRefCount--;

    // Set vtable pointer (restore or assign for this object)
    this->vtable = &s_streamVTable; // PTR_LAB_00e36658

    // Initialize stream timeout fields (offset +0x84 = 60000 ms, +0x88 = 30 frames)
    this->field_0x84 = 60000;
    this->field_0x88 = 0x1e; // 30
}