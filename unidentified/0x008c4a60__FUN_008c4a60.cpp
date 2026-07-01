// FUNC_NAME: SomeManager::getSlotOffset
int __thiscall SomeManager::getSlotOffset(int index)
{
    FUN_008c4190(index);  // likely validates or converts index
    // +0x130: base offset (int) – perhaps pointer to array start + 28
    // +0x134: index multiplier or stride index (int)
    int base = *(int *)(this + 0x130);
    int strideValue = *(int *)(this + 0x134);
    // Computes offset = base - 28 + strideValue * 28
    // Equivalent to base + (strideValue - 1) * 28, suggesting strideValue is 1-based index
    return base - 0x1c + strideValue * 0x1c;
}