// FUNC_NAME: StreamSlotManager::releaseSlot
void __fastcall StreamSlotManager::releaseSlot(int *this)
{
    // Check if current active count (+0x10) is less than capacity (+0x4)
    // and the global audio manager is initialized; if not, attempt to init it
    if ((this[4] < this[1]) && ((g_streamAudioActive != 0) || (StreamAudioManager::init(), g_streamAudioActive != 0)))
    {
        // Stop/cleanup the stream associated with this slot
        StreamAudioManager::stopStream();
    }

    // Reset slot state
    this[2] = 0;   // probably index or lock flag
    this[1] = 0;   // capacity counter

    // If the handle is valid, call its virtual Release method (vtable index 1)
    if (this[0] != 0)
    {
        // VTable pointer is stored at global offset g_vtableBase + 4
        int *vtable = *(int **)(g_vtableBase + 4);
        ((void (__thiscall *)(int, int))vtable[1])(this[0], 0);
    }

    // Clear the handle
    this[0] = 0;
}