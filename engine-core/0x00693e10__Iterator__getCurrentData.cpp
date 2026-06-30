// FUNC_NAME: Iterator::getCurrentData

int* __fastcall Iterator::getCurrentData(int* this) {
    // *this is pointer to container (assume non-null)
    if (this[0] == 0) {
        debugBreak(); // FUN_00b97aea
    }
    // container +4 stores the end marker (e.g. last index or sentinel)
    if (this[1] == *(int*)(this[0] + 4)) {
        debugBreak(); // iterator is at end
    }
    // Return pointer to current element's data (offset 0xc from current index/pointer)
    return (int*)(this[1] + 0xc);
}