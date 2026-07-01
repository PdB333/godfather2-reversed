// FUNC_NAME: UnknownClass::getDataBuffer
int __fastcall FUN_00994b40(void* thisPointer)
{
    // +0x20: pointer to internal data block (e.g., mData)
    // The data block has an 8-byte header, so actual data starts at offset +8
    // Returns the address of the usable data
    return *reinterpret_cast<int*>(static_cast<char*>(thisPointer) + 0x20) + 8;
}