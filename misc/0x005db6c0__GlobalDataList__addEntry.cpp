// FUNC_NAME: GlobalDataList::addEntry

void __fastcall GlobalDataList::addEntry(void* srcObj)
{
    // srcObj offsets:
    // +0x14: field1 (uint32_t) - value to be stored as second element
    // +0x20: field2 (uint32_t) - value to be stored as first element
    // +0x18: field3 (uint32_t) - copied to +0xc after storing
    // +0xc: destination for field3 copy

    uint32_t uVar1 = *(uint32_t*)((char*)srcObj + 0x14);
    uint32_t uVar2 = *(uint32_t*)((char*)srcObj + 0x20);
    uint32_t uVar3 = *(uint32_t*)((char*)srcObj + 0x18);

    // Global list header at DAT_01206880; offset +0x14 holds current write pointer into a pre-allocated buffer.
    // Each entry consists of: vtable pointer (4 bytes), uVar2 (4 bytes), uVar1 (4 bytes) = 12 bytes total.
    struct DataListHeader {
        char unknown[0x14];
        uint32_t** currentWritePtr; // +0x14
    };

    DataListHeader* header = (DataListHeader*)DAT_01206880;
    uint32_t** writePtr = header->currentWritePtr;

    // Write vtable pointer for this entry type
    *(uint32_t*)*writePtr = (uint32_t)&PTR_LAB_011273b8; // vtable for the entry type
    (*writePtr)++;

    // Write field2 (uVar2)
    *(uint32_t*)*writePtr = uVar2;
    (*writePtr)++;

    // Write field1 (uVar1)
    *(uint32_t*)*writePtr = uVar1;
    (*writePtr)++;

    // Update the header's write pointer
    header->currentWritePtr = writePtr;

    // Copy field3 to srcObj+0xc
    *(uint32_t*)((char*)srcObj + 0xc) = uVar3;
}