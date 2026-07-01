// FUNC_NAME: BaseObject::getDataBlock
int __fastcall BaseObject::getDataBlock(int thisPtr)
{
    // Read pointer at offset +0x58 (likely to an internal data region)
    // Add offset 0x3C0 to access a specific sub-structure within that region
    return *(int *)(thisPtr + 0x58) + 0x3C0;
}