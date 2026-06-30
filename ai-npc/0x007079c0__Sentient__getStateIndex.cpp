// FUNC_NAME: Sentient::getStateIndex
// Address: 0x007079c0
// Returns zero-based index from current state field at +0x214.
// Special values: 0 (invalid) and 0x48 (idle/none) map to index 0.
int __thiscall Sentient::getStateIndex() {
    int state = *(int*)((char*)this + 0x214); // +0x214: current state enum
    if (state != 0 && state != 0x48) {
        return state - 0x48;
    }
    return 0;
}