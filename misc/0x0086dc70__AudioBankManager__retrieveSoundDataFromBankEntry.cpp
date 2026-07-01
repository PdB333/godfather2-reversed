// FUNC_NAME: AudioBankManager::retrieveSoundDataFromBankEntry
void __thiscall AudioBankManager::retrieveSoundDataFromBankEntry(SoundBankEntry* entry)
{
    int typeID;
    
    typeID = entry->getTypeID();
    if ((typeID == 0x72703570) && 
        (typeID = *(int *)(*(int *)(this + 0x50) + 0x70), typeID != 0) && 
        (typeID != 0x48)) {
        typeID = getAudioDataManagerInstance();
        *(uint64_t *)(entry + 0x18) = *(uint64_t *)(typeID + 0x30);
        entry[0x1a] = *(uint32_t *)(typeID + 0x38);
    }
    return;
}