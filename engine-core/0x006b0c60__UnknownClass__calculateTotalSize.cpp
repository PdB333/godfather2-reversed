// FUNC_NAME: UnknownClass::calculateTotalSize

int __fastcall UnknownClass::calculateTotalSize(int thisPtr)  // __fastcall: first arg in ecx (this), second in edx (unused)
{
    int totalSize = 0x14; // Base size of the structure (e.g., header or fixed overhead)
    int count = *(int *)(thisPtr + 0x20); // Number of elements (+0x20)

    if (count != 0) {
        for (int i = 0; i < count; i++) {
            int elementSize = FUN_006b2320(); // Returns size of individual element
            totalSize += elementSize;
        }
    }

    return totalSize; // Total memory/byte size of the container
}