// FUNC_NAME: DataBlock::copyFromOffset
void __thiscall DataBlock::copyFromOffset(int thisPtr, int param2)
{
    int sourcePtr;
    
    if (thisPtr == 0) {
        sourcePtr = 0;
    }
    else {
        sourcePtr = thisPtr + 0x50; // +0x50: optional secondary buffer pointer
    }
    // destination at +0xe8, source, count (param2), flags 0 and 4 (likely stride or endianness)
    FUN_00440590(thisPtr + 0xe8, sourcePtr, param2, 0, 4);
    return;
}