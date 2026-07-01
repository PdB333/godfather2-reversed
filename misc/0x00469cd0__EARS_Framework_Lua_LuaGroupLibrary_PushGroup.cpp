// Xbox PDB: EARS::Framework::Lua::LuaGroupLibrary::PushGroup
// FUNC_NAME: GroupStack::pushGroup
void GroupStack::pushGroup(int param1) {
    // Expand buffer if needed: check current size vs capacity at this+0x10 buffer
    if (*(uint*)(*(int*)(this + 0x10) + 0x20) <= *(uint*)(*(int*)(this + 0x10) + 0x24)) {
        expandBuffer(); // FUN_00627360
    }
    int* newGroup = allocateGroup(4); // FUN_00638a40(4) – allocate with size hint
    int* stackPtr = *(int**)(this + 8);
    *stackPtr = 7; // type = 7 (group?)
    *(stackPtr + 1) = (int)newGroup;
    *(int**)(this + 8) = stackPtr + 2; // advance stack pointer by 8 bytes

    if ((int*)(newGroup + 0x10) != nullptr) {
        *(int*)(newGroup + 0x10) = param1; // store parameter at newGroup+0x10
        int result = someValidation(); // FUN_00627c90
        if (result != 0) {
            logString(&PTR_s___index_00e32180); // FUN_004aeb70
        }
        int currentStackTop = *(int*)(this + 8); // after push
        int* previousEntryValue = (int*)(*(int*)(currentStackTop - 0xc)); // value of entry before this push
        int previousEntryType = *(int*)(currentStackTop - 0x10); // type of entry before

        if (previousEntryType == 5) {
            // Link: set previous group's child pointer to new group's +4 field
            *(int*)(previousEntryValue + 2) = *(int*)(newGroup + 1); // +8 offset (since int* +2 = 8 bytes)
        }
        else if (previousEntryType == 7) {
            // Same link, then pop the newly pushed entry
            *(int*)(previousEntryValue + 2) = *(int*)(newGroup + 1);
            *(int*)(this + 8) = currentStackTop - 8; // pop current entry
            return;
        }
        *(int*)(this + 8) = currentStackTop - 8; // pop current entry (undo push)
        return;
    }
    errorLog("Failed to PushGroup"); // FUN_00627bd0
    code* breakpoint = (code*)swi(3);
    (*breakpoint)();
}