// FUNC_NAME: StreamManager::computeCombinedSize
int __thiscall StreamManager::computeCombinedSize(int this, int baseIndex)
{
    // FUN_006b2360 likely returns a size or offset based on baseIndex
    int size1 = FUN_006b2360(baseIndex);
    // FUN_006b2470 likely returns a size from a pointer (this+0x84 is a table or buffer)
    int size2 = FUN_006b2470(size1 + baseIndex, this + 0x84);
    // Combine sizes
    int combined = size1 + baseIndex + size2;
    // Another lookup from this+0x9c
    int size3 = FUN_006b2470(combined, this + 0x9c);
    // Final result: size3 + (combined - baseIndex)
    return size3 + (combined - baseIndex);
}