// FUNC_NAME: EAObject::getDataBlock
int __fastcall EAObject::getDataBlock(int thisPtr)
{
    // +0x08: mDataBlock pointer to the object's data block
    if (*(int *)(thisPtr + 8) != 0) {
        // Offset -0x48 adjusts from TNL NetObject pointer to EA data block
        return *(int *)(thisPtr + 8) + -0x48;
    }
    return 0;
}