// FUNC_NAME: BNKStreamManager::playStream
void __fastcall BNKStreamManager::playStream(void* this) {
    char* soundName;
    // Build sound name from member at +0x3e4
    FUN_004d4a60(&soundName, 1, &DAT_00d5db54, *(int*)((char*)this + 0x3e4));
    char* name = soundName;
    if (soundName == nullptr) {
        name = (char*)&DAT_0120546e;
    }
    // Play wave: bank ID 0x53504750, wave ID 0x5357474c
    FUN_009085a0(0x53504750, 0x5357474c, name);
    FUN_006acd80();
    if (soundName != nullptr) {
        // Destructor for allocated string
        (*(void(__thiscall**)(char*))((int*)soundName - 1))(soundName);
    }
}