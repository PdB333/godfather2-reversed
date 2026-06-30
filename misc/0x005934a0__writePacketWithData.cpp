// FUNC_NAME: writePacketWithData
void __fastcall writePacketWithData(void* outputPtr, void* extraDataPtr, void* objectPtr) 
{
    void* packetInfoPtr = *(void**)((char*)objectPtr + 4); // objectPtr+4 -> pointer to packet info
    uint32_t typeField = *(uint32_t*)((char*)packetInfoPtr + 4) & 0xFF; // +0x04: type/sequence, low byte
    void* dataPtr;
    if (typeField < 10) {
        dataPtr = *(void**)((char*)packetInfoPtr + 0x0C); // +0x0C: data buffer (normal)
    } else {
        dataPtr = *(void**)((char*)packetInfoPtr + 0x20); // +0x20: data buffer (special)
    }
    FUN_00586df0(outputPtr, dataPtr, 
                 *(uint32_t*)extraDataPtr, *(uint32_t*)((char*)extraDataPtr + 4),
                 *(uint32_t*)((char*)extraDataPtr + 8), *(uint32_t*)((char*)extraDataPtr + 12),
                 *(uint32_t*)((char*)extraDataPtr + 16), *(uint32_t*)((char*)extraDataPtr + 20),
                 *(uint32_t*)((char*)extraDataPtr + 24), *(uint32_t*)((char*)extraDataPtr + 28));
}