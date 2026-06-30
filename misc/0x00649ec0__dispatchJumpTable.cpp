// FUNC_NAME: dispatchJumpTable
// Address: 0x00649ec0
// Role: Jump table dispatcher. Index is passed in EAX. The table is at 0x00649f10.
// Called from 0x00648930 (likely part of a state machine or event handler).
// The jump table entries are unknown due to incomplete decompilation.
void dispatchJumpTable(int index) {
    // The original code: (*(code *)(&PTR_LAB_00649f10)[in_EAX])();
    // Reconstructed as a static function pointer array.
    // The table at 0x00649f10 contains addresses of handler functions.
    // Index should be validated; the table size is unknown.
    static void (*jumpTable[])() = {
        nullptr, // Placeholder – actual addresses unknown
        nullptr,
        // ... additional entries
    };
    jumpTable[index]();
}