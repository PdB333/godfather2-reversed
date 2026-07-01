// FUNC_NAME: Entity::clearStringProperty
void __thiscall Entity::clearStringProperty(void)
{
    // +0x28: pointer to string data (e.g., file path, event name)
    char* strPtr = *(char**)(this + 0x28);
    // Temporary descriptor: pointer + length (0) + flags (0)
    // layout: 4-byte pointer, 4-byte length, 1-byte flags (padded to 12 bytes)
    char* descPtr = strPtr;
    int descLen = 0;
    byte descFlags = 0;
    // Internal call to release/clear the string (mode 0 = clear)
    FUN_00408a00(&descPtr, 0);
    // Set dirty flag (bit 1) at +0x30 to indicate modification
    *(byte*)(this + 0x30) |= 2;
}