// FUNC_NAME: GodfatherGameManager::handleAutosave
void __thiscall GodfatherGameManager::handleAutosave(char isSave) {
    char* saveName;
    int zero1;
    int zero2;
    void (*freeFunc)(void*);

    int* flags = (int*)((char*)this + 0x10); // +0x10: flags, bit3 = autosave flag

    if (isSave == '\0') {
        if (((uint)*flags >> 3 & 1) != 0) {
            // vtable[0x38] -> load autosave
            (**(code (**)(void))(*this + 0x38))();
        }
    } else if (((uint)*flags >> 3 & 1) == 0) {
        saveName = 0;
        zero1 = 0;
        zero2 = 0;
        freeFunc = 0;
        FUN_008f22f0(&saveName); // initialize save name buffer
        FUN_004d4300("autosave");
        char* namePtr = saveName;
        if (saveName == 0) {
            namePtr = (char*)&DAT_0120546e; // default save name
        }
        // vtable[0x34] -> save with filename
        (**(code (**)(char*))(*this + 0x34))(namePtr);
        if (saveName != 0) {
            freeFunc(saveName);
        }
    }

    if (isSave != '\0') {
        *flags = *flags | 8;
    } else {
        *flags = *flags & 0xfffffff7; // clear bit3
    }
}