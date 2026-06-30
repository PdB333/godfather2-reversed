// FUNC_NAME: UIList::addListItem
void __thiscall UIList::addListItem(int param_1) {
    // this+0x1f4 (500) is the count (must be > 1)
    // this+0x1e4 is the index into s_sourceItems
    if ((*(uint *)(this + 500) <= 1) ||
        (uint index = *(uint *)(this + 0x1e4), index == 0))
        return;

    // s_sourceItems is an array of 0x38-byte structures
    uint8_t* pSource = (index < 0x1000) ? &s_sourceItems[index * 0x38] : nullptr;
    if (pSource == nullptr)
        return;

    // Offset +4: ushort relative value, offset +2: ushort some other data
    uint relative = (uint)*(ushort *)(pSource + 4) / *(uint *)(this + 500);
    ushort someVal = *(ushort *)(pSource + 2);

    // s_renderBuffer is a 0x18-byte structure array, s_renderBufferIndex is current count
    int bufferOffset = s_renderBufferIndex * 0x18;

    // Fill render entry:
    *(uint32_t*)((uint8_t*)s_renderBuffer + bufferOffset + 0x00) = 0;
    *(uint32_t*)((uint8_t*)s_renderBuffer + bufferOffset + 0x04) = relative * param_1;
    *(uint32_t*)((uint8_t*)s_renderBuffer + bufferOffset + 0x08) = someVal;
    *(uint32_t*)((uint8_t*)s_renderBuffer + bufferOffset + 0x0C) = relative;
    *(uint32_t*)((uint8_t*)s_renderBuffer + bufferOffset + 0x10) = 0;
    *(uint32_t*)((uint8_t*)s_renderBuffer + bufferOffset + 0x14) = s_globalSomeValue; // DAT_00e2b1a4

    // Additional processing: call FUN_00609500 with the original index and 1.0f
    FUN_00609500((int)index, 0x3f800000); // likely sets some state
}