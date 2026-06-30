// FUNC_NAME: Entity::shutdown
void __fastcall Entity::shutdown() {
    // Local variable used as output parameter for message handler
    int result = reinterpret_cast<int>(this);

    // Check if the pointer at offset 0x5c is valid (likely a message handler or component)
    // Offset 0x5c: pointer to a structure with virtual functions
    if (*(void**)(reinterpret_cast<char*>(this) + 0x5c) != nullptr) {
        // Prepare to indicate shutdown by setting result to 0
        result = 0;

        // Retrieve virtual function table from the pointed structure
        void** vtable = *reinterpret_cast<void***>(reinterpret_cast<char*>(this) + 0x5c);
        // Call virtual function at index 4 (offset 0x10) – likely a "sendMessage" or "dispatchEvent"
        auto messageHandler = reinterpret_cast<void (__fastcall*)(int, int*)>(vtable[4]);
        // 0xa0d329d6 appears to be a hash for a specific message (e.g., kMessageShutdown)
        messageHandler(0xa0d329d6, &result);
    }

    // Call base class cleanup routine
    // FUN_004df590 corresponds to BaseEntity::cleanupInternal or similar
    cleanupInternal();
}