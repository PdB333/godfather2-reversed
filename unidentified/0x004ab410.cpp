// FUN_004ab410: DataBlock::loadFromHandle

// This function appears to copy two DWORDs (e.g., a GUID or identifier) from an internal
// source returned by FUN_004ab6d0 into the first two fields of this DataBlock object.
// The local_c buffer may be used as scratch space by the helper.
void __thiscall DataBlock::loadFromHandle(void) {
    // Buffer passed to helper (12 bytes, possibly unused by caller)
    uint8_t local_c[12];
    // Pointer to source data containing two 32-bit values
    uint32_t* puVar1;

    // Initialize local fields (maybe redundant, overwritten below)
    // offset +0x00: first DWORD field
    this->field0 = 0;
    // offset +0x04: second DWORD field
    this->field4 = 0;

    // Retrieve pointer to data from helper function (address 0x004ab6d0)
    puVar1 = (uint32_t*)FUN_004ab6d0(local_c);

    // Copy the two DWORDs into this block
    this->field0 = puVar1[0];
    this->field4 = puVar1[1];
}