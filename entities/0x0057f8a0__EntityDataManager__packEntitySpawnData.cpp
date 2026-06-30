// FUNC_NAME: EntityDataManager::packEntitySpawnData
void __thiscall EntityDataManager::packEntitySpawnData(uint8_t* outBuffer, int index) const
{
    // outBuffer[0] = type identifier (7)
    outBuffer[0] = 7;

    // +0x2a: count of first sub-array
    short count1 = *(short*)(this + 0x2a);
    if (count1 < 1) {
        *(uint32_t*)(outBuffer + 4) = 0;
        *(uint32_t*)(outBuffer + 8) = 0;
        *(uint32_t*)(outBuffer + 0xc) = 0;
        *(uint32_t*)(outBuffer + 0x10) = 0xFFFFFFFF; // -1 marks empty
    } else {
        uint32_t offset;
        if (*(uint32_t*)(this + 0x78) == 0) {
            offset = 0;
        } else {
            uint16_t* table = *(uint16_t**)(this + 0x7c);
            offset = table[index] + *(uint32_t*)(this + 0x78);
        }
        *(uint32_t*)(outBuffer + 4) = offset;
        *(uint32_t*)(outBuffer + 8) = *(uint32_t*)(this + 0x4c); // +0x4c: some base value
        *(uint32_t*)(outBuffer + 0xc) = *(uint32_t*)(this + 0x6c); // +0x6c: another base
        *(uint32_t*)(outBuffer + 0x10) = 0; // valid flag
    }

    // +0x2c: count of second sub-array
    if (*(short*)(this + 0x2c) < 1) {
        *(uint32_t*)(outBuffer + 0x14) = 0;
        *(uint32_t*)(outBuffer + 0x18) = 0xFFFFFFFF;
    } else {
        *(uint32_t*)(outBuffer + 0x14) = *(uint32_t*)(this + 0x50); // +0x50: base pointer/offset
        *(uint32_t*)(outBuffer + 0x18) = 0;
    }

    // +0x34: count of third sub-array
    if (*(short*)(this + 0x34) < 1) {
        *(uint32_t*)(outBuffer + 0x1c) = 0;
        *(uint32_t*)(outBuffer + 0x20) = 0;
        *(uint32_t*)(outBuffer + 0x24) = 0;
        *(uint32_t*)(outBuffer + 0x28) = 0xFFFFFFFF;
    } else {
        short elemSize = *(short*)(this + 0x38);
        uint32_t base = *(uint32_t*)(this + 0x60);
        *(uint32_t*)(outBuffer + 0x28) = 0;
        *(uint32_t*)(outBuffer + 0x1c) = elemSize * index + base;
        *(uint32_t*)(outBuffer + 0x20) = *(uint32_t*)(this + 0x68); // +0x68: another base
        *(uint32_t*)(outBuffer + 0x24) = *(uint32_t*)(this + 0x70); // +0x70: yet another base
    }

    // +0x32: count of fourth sub-array (short)
    if (*(short*)(this + 0x32) < 1) {
        *(uint32_t*)(outBuffer + 0x2c) = 0;
        *(uint32_t*)(outBuffer + 0x30) = 0;
        *(uint32_t*)(outBuffer + 0x34) = 0;
        *(uint32_t*)(outBuffer + 0x38) = 0xFFFFFFFF;
    } else {
        uint32_t base2 = *(uint32_t*)(this + 0x5c);
        short elemStride = *(short*)(this + 0x36);
        *(uint32_t*)(outBuffer + 0x2c) = base2 + elemStride * index * 2;
        *(uint32_t*)(outBuffer + 0x30) = *(uint32_t*)(this + 0x64); // +0x64
        *(uint32_t*)(outBuffer + 0x34) = *(uint32_t*)(this + 0x74); // +0x74
        *(uint32_t*)(outBuffer + 0x38) = 0;
    }

    // +0x30: count of fifth sub-array (short)
    if (*(short*)(this + 0x30) < 1) {
        *(uint32_t*)(outBuffer + 0x3c) = 0;
        *(uint32_t*)(outBuffer + 0x40) = 0xFFFFFFFF;
    } else {
        uint32_t base3 = *(uint32_t*)(this + 0x54);
        short elemStride2 = *(short*)(this + 0x30);
        *(uint32_t*)(outBuffer + 0x3c) = base3 + elemStride2 * index * 12;
        *(uint32_t*)(outBuffer + 0x40) = 0;
    }

    // +0x18: count of sixth sub-array
    short count6 = *(short*)(this + 0x18);
    *(uint32_t*)(outBuffer + 0x44) = *(uint32_t*)(this + 0x58); // +0x58: base
    *(uint32_t*)(outBuffer + 0x48) = 0;
    if (count6 == 0) {
        *(uint32_t*)(outBuffer + 0x4c) = 0;
    } else {
        *(uint32_t*)(outBuffer + 0x4c) = *(uint32_t*)(this + 0x48); // +0x48: parent index?
    }

    // Last fields:
    short count7 = *(short*)(this + 0x2e);
    uint16_t divisor = *(uint16_t*)(this + 0x24);
    *(uint32_t*)(outBuffer + 0x50) = 0;
    *(uint32_t*)(outBuffer + 0x54) = *(uint32_t*)(this + 0x3c); // +0x3c: base
    *(uint32_t*)(outBuffer + 0x58) = (count7 / divisor) * index + *(uint32_t*)(this + 0x44); // +0x44: base for index calculation
}