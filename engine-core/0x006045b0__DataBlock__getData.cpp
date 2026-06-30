// FUNC_NAME: DataBlock::getData
int __thiscall DataBlock::getData(int this)
{
    // Dereference pointer at this+0x20 (likely internal buffer or control structure)
    // Then add 0x24 to get the actual data pointer
    return *(int*)(this + 0x20) + 0x24;
}