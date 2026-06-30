// FUNC_NAME: HandlePool::getValidatedElement
// Address: 0x00625950
// __thiscall: this in ECX, index1 in EDX, index2 on stack
// Validates two 1-based indices and returns the result of a function on the element at index2.
// Structure offsets: +0x08 = end address of data array (base + count*8), +0x0C = base pointer to array of 8-byte elements.

int __fastcall HandlePool::getValidatedElement(int index1, int index2) {
    uint addr1;
    uint addr2;
    uint result;

    // If index1 is invalid (<1), get a sentinel (likely 0) from a helper.
    if (index1 < 1) {
        addr1 = getNullSentinel(); // FUN_00625430
    } else {
        // Compute address of element at 1-based index1: base + (index1-1)*8
        addr1 = *(int*)(this + 0x0C) + -8 + index1 * 8;
        // Clamp to zero if address exceeds the end boundary (invalid index)
        addr1 = -(uint)(addr1 < *(uint*)(this + 0x08)) & addr1;
    }

    // Same for index2
    if (index2 < 1) {
        addr2 = getNullSentinel();
    } else {
        addr2 = *(int*)(this + 0x0C) + -8 + index2 * 8;
        addr2 = -(uint)(addr2 < *(uint*)(this + 0x08)) & addr2;
    }

    // If both indices are valid (non-zero addresses), call resolve function on the second element
    if ((addr1 != 0) && (addr2 != 0)) {
        result = resolveElement(addr2); // FUN_00634150
        return result;
    }
    return 0;
}