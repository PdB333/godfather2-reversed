// FUNC_NAME: StreamManager::registerStreamBuffer
void __thiscall StreamManager::registerStreamBuffer(uint size, StreamBuffer* buffer, uint flags, void* extraData)
{
    // extraData is passed in EAX (implicit parameter from caller)
    this->setupBuffer(flags, extraData);
    // Set buffer flags at offset +0x2c: size in dwords (>>2) OR high flags (0xC0000000)
    *(uint*)(buffer + 0x2c) = (size >> 2) | 0xC0000000;
    globalMutexRelease();  // FUN_0043b490 - likely release a lock
    sendMessage(0x2001, flags, 0);  // notify stream manager about buffer registration
}

// Helper function declarations (not defined here)
void StreamManager::setupBuffer(uint flags, void* extraData);
void globalMutexRelease();
void sendMessage(uint msgId, uint param1, uint param2);