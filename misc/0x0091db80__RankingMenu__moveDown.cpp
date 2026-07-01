//FUNC_NAME: RankingMenu::moveDown
void __thiscall RankingMenu::moveDown(int this) {
    int* currentPtr;
    int maxCount;
    int copySize;
    int copyCount;

    // +0xb8: state/type field
    if (*(int*)(this + 0xb8) == 1) {
        // State 1: direct update via virtual function
        // +0xc0: current index, +0xb4: offset, +0xa0: max index
        if (*(int*)(this + 0xc0) + *(int*)(this + 0xb4) != *(int*)(this + 0xa0) - 1) {
            FUN_00402050(&DAT_011301c0, 0); // assertion
        }
        // Call virtual function at vtable offset 0x68 on object at +0x50
        (**(code**)(*(int*)(this + 0x50) + 0x68))(this + 0xc0, *(int*)(this + 0xb4), *(int*)(this + 0xa0), 10);
        return;
    }
    if (*(int*)(this + 0xb8) - 10U < 0x10) {
        // State between 10 and 25 (inclusive)
        currentPtr = (int*)(this + 0xc0);
        maxCount = FUN_009185a0(); // get max count
        if (*currentPtr + *(int*)(this + 0xb4) != maxCount - 1) {
            FUN_00402050(&DAT_011301c0, 0); // assertion
        }
        copyCount = 10;
        copySize = FUN_009185a0(10); // get size for copy
        FUN_0091ce30(currentPtr, *(int*)(this + 0xb4), copySize, copyCount); // memcpy-like
        FUN_00918940(*currentPtr + *(int*)(this + 0xb4), *(int*)(this + 0xf0), 0x80); // string copy?
        FUN_005a04a0("UpdateRankingText", 0, &DAT_00d8510c, 1, *(int*)(this + 0xf0)); // log/event
        return;
    }
    // Default: log "MoveDown"
    FUN_005a04a0("MoveDown", 0, &DAT_00d8510c, 0);
}