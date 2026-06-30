// FUNC_NAME: StreamManager::destroy
void __thiscall StreamManager::destroy(StreamManager *this)
{
    // Set vtable to this class's own vtable for destruction
    this->vtable = &s_StreamManagerVTable;                 // +0x00
    this->unknownPtr3 = &PTR_LAB_00d60cc8;                 // +0x0C

    // Clean up base or internal resources
    this->cleanupStreams();                                 // FUN_006ff5b0

    // Get pointer to stream list sub-object at offset 0x24
    StreamList *listPtr = reinterpret_cast<StreamList*>(this + 0x9); // +0x24

    // Free stream data if present at offset 0x40
    if (this->streamData != nullptr)                       // +0x40
    {
        this->freeStreamData();                            // FUN_006ff660
    }

    // Destroy the stream list
    listPtr->release();                                    // FUN_006fc560
    // Remove timer callback associated with this list
    listPtr->removeTimer(StreamManager::onStreamTimer, listPtr); // FUN_006fc4c0
    // Final shutdown of list
    listPtr->shutdown();                                   // FUN_006fbca0

    // Complete destruction
    this->finalizeShutdown();                              // FUN_006ff560

    // Restore to base class vtable (or null out second pointer)
    this->unknownPtr3 = &PTR_LAB_00d60c94;                 // +0x0C

    // Clear global instance pointer
    g_streamManagerInstance = nullptr;                     // DAT_01129980

    // Deallocate the object memory
    delete this;                                           // FUN_004083d0
}