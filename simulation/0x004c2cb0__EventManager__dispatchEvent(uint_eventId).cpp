// FUNC_NAME: EventManager::dispatchEvent(uint eventId)
void __thiscall EventManager::dispatchEvent(uint eventId)
{
    // +0x82 (0x208) : pointer to array of RegistrationEntry*
    RegistrationEntry** regList = (RegistrationEntry**)this->field_0x208;
    // +0x83 (0x20C) : count of entries in regList
    uint regCount = this->field_0x20C;
    RegistrationEntry** end = regList + regCount;

    for (RegistrationEntry** it = regList; it != end; ++it) {
        RegistrationEntry* entry = *it;
        // +0x00 of RegistrationEntry: pointer to key (uint)
        if (*entry->key != eventId) {
            continue;
        }
        // +0x04 : pointer to array of data (void*)
        // +0x08 : count of data entries
        for (uint i = 0; i < entry->dataCount; ++i) {
            // vtable +0x2c : virtual method taking a single void* argument
            (this->vtable->methodAt0x2c)(entry->dataArray[i]);
        }
        // Note: only first matching entry is handled? No, loop continues for all entries.
    }
}