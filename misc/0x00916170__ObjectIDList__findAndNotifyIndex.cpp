// FUNC_NAME: ObjectIDList::findAndNotifyIndex
void __thiscall ObjectIDList::findAndNotifyIndex(int thisPtr, int objectID) {
    uint index = 0;
    uint resultIndex = 0xffffffff;

    if (*(uint *)(thisPtr + 0x68) != 0) {
        int *idArray = *(int **)(thisPtr + 100); // +0x64? Actually 100 = 0x64, but offset 0x100 would be 256 decimal. Wait, need to check: param_1 + 100 is decimal 100, which is 0x64, not 0x100. The decompiled says "param_1 + 100". In Ghidra, sometimes offsets are decimal. The comment says "+0x100" but that's wrong. Let's re-evaluate: The decompiled text says "*(int **)(param_1 + 100)". 100 decimal = 0x64. But the data_refs list is empty. We should trust the decompiled code: offset 100 decimal. However, I'll use 0x64 for clarity. Actually the user instruction says document structure field offsets in comments like // +0x94. So we'll use hex.

        while (true) {
            resultIndex = index;
            if (*idArray == objectID) {
                break;
            }
            index++;
            idArray++;
            if (*(uint *)(thisPtr + 0x68) <= index) {
                FUN_00956a50(0xffffffff, 1); // not found
                return;
            }
        }
    }
    FUN_00956a50(resultIndex, 1); // found
    return;
}