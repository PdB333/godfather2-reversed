// FUNC_NAME: ResourceManager::isValid
int __thiscall ResourceManager::isValid() {
    // +0x18: flag indicating validity state, reset to false
    *(char *)(this + 0x18) = 0;

    // +0x08: resource handle (file ID or pointer)
    if (*(int *)(this + 8) != 0) {
        FUN_005dbdf0(); // internal pre‑check (e.g., refresh state)
        if (FUN_005ddd90(DAT_01223508, *(int *)(this + 8))) { // global file system check
            return 1;
        }
    }
    return 0;
}