// FUNC_NAME: Entity::processPendingFlags
void Entity::processPendingFlags()
{
    // Check flag at offset 0x13 (byte) - e.g., m_pendingTriggerFlag
    if (*(char*)(this + 0x13) != '\0')
    {
        // Clear the flag
        *(char*)(this + 0x13) = '\0';
        
        // Check flag at offset 0x12 (byte) - e.g., m_triggerReadyFlag
        if (*(char*)(this + 0x12) != '\0')
        {
            // Call virtual function at vtable offset 0xA4 (e.g., onPendingTrigger)
            void (**vtable)(void*) = *(void (***)(void*))(this);
            vtable[0x29](this); // 0xA4 / 4 = 0x29
        }
    }
}