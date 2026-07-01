// FUNC_NAME: Player::readFromStream
void __thiscall Player::readFromStream(void* thisPtr, Stream* stream)
{
    uint typeId;
    char hasMore;
    float* vecPtr;
    int itemPtr;
    char localBuffer[12];
    float tempVec[3]; // Actually four floats but we use array of 4
    int tempInt;

    stream->setSource(stream); // FUN_009c5750
    *(char*)(thisPtr + 0x3a8) = 0; // Clear dirty flag? +0x3a8

    stream->beginBlock(0xb390b11a); // Begin reading block A
    stream->setVersion(1); // FUN_0043af00

    hasMore = stream->hasMoreData(); // FUN_0043b120
    if (!hasMore) {
        // Initial data read? (maybe a header)
        char* buf = localBuffer;
        localBuffer[0] = 0;
        localBuffer[4] = 0;
        localBuffer[8] = 0;
        localBuffer[12] = *(int*)0x00d5780c; // Some constant
        stream->readBuffer(buf); // FUN_0043b210
        stream->readVector3(buf); // FUN_0043ac60
        *(float*)(thisPtr + 0x1b80) = *(float*)tempVec; // +0x1b80 X
        *(float*)(thisPtr + 0x1b84) = *(float*)(tempVec+1); // +0x1b84 Y
        *(float*)(thisPtr + 0x1b88) = *(float*)(tempVec+2); // +0x1b88 Z
    }

    stream->beginBlock(0x55859efa); // Begin reading block B
    hasMore = stream->hasMoreData();
    while (!hasMore) {
        stream->readItemHeader();
        typeId = stream->readType();
        switch (typeId) {
        case 0: // bool flag
            itemPtr = stream->readItemPtr();
            if (*(int*)(itemPtr + 8) == 0) {
                *(uint*)(thisPtr + 0x4a4) &= 0xfffffffe; // Clear bit 0
            } else {
                *(uint*)(thisPtr + 0x4a4) |= 1; // Set bit 0
            }
            break;
        case 1:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1ed0) = *(int*)(itemPtr + 8);
            break;
        case 2:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x600) = *(int*)(itemPtr + 8);
            break;
        case 4: // Vector4
            stream->readItemPtr();
            vecPtr = stream->readVector4();
            *(float*)(thisPtr + 0x1be0) = vecPtr[0];
            *(float*)(thisPtr + 0x1be4) = vecPtr[1];
            *(float*)(thisPtr + 0x1be8) = vecPtr[2];
            *(float*)(thisPtr + 0x1bec) = vecPtr[3];
            break;
        case 5: // Another Vector4
            stream->readItemPtr();
            vecPtr = stream->readVector4();
            *(float*)(thisPtr + 0x1bd0) = vecPtr[0];
            *(float*)(thisPtr + 0x1bd4) = vecPtr[1];
            *(float*)(thisPtr + 0x1bd8) = vecPtr[2];
            *(float*)(thisPtr + 0x1bdc) = vecPtr[3];
            break;
        case 6: // per-case 6 through 0xd set individual fields and dirty flag
        case 7:
        case 8:
        case 9:
        case 0xa:
        case 0xb:
        case 0xc:
        case 0xd:
            {
                int offset = 0x1c8c + (typeId - 6) * 4; // each is 4 bytes apart? Actually 6->0x1c8c,7->0x1c90,8->0x1c94,... 0xd->0x1ca8
                itemPtr = stream->readItemPtr();
                *(int*)(thisPtr + offset) = *(int*)(itemPtr + 8);
                *(char*)(thisPtr + 0x3a8) = 1; // Set dirty flag
            }
            break;
        case 0xe:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1cac) = *(int*)(itemPtr + 8);
            break;
        case 0xf:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1cb0) = *(int*)(itemPtr + 8);
            break;
        case 0x10: // float with scale
            itemPtr = stream->readItemPtr();
            *(float*)(thisPtr + 0x1cb4) = *(float*)(itemPtr + 8) * DAT_00e445c8; // Scale factor (meters to game units)
            break;
        case 0x11:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1cb8) = *(int*)(itemPtr + 8);
            break;
        case 0x12: // float with scale
            itemPtr = stream->readItemPtr();
            *(float*)(thisPtr + 0x1cbc) = *(float*)(itemPtr + 8) * DAT_00e445c8;
            break;
        case 0x13:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d74) = *(int*)(itemPtr + 8);
            break;
        case 0x14:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d78) = *(int*)(itemPtr + 8);
            break;
        case 0x15:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d7c) = *(int*)(itemPtr + 8);
            break;
        case 0x16:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d34) = *(int*)(itemPtr + 8);
            break;
        case 0x17:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d48) = *(int*)(itemPtr + 8);
            break;
        case 0x18:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d4c) = *(int*)(itemPtr + 8);
            break;
        case 0x19:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d50) = *(int*)(itemPtr + 8);
            break;
        case 0x1a:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d54) = *(int*)(itemPtr + 8);
            break;
        case 0x1b:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d6c) = *(int*)(itemPtr + 8);
            break;
        case 0x1c:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d70) = *(int*)(itemPtr + 8);
            break;
        case 0x1d:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d80) = *(int*)(itemPtr + 8);
            break;
        case 0x1e:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d84) = *(int*)(itemPtr + 8);
            break;
        case 0x1f:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d58) = *(int*)(itemPtr + 8);
            break;
        case 0x20:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d5c) = *(int*)(itemPtr + 8);
            break;
        case 0x21:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d60) = *(int*)(itemPtr + 8);
            break;
        case 0x22:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d64) = *(int*)(itemPtr + 8);
            break;
        case 0x23: // float with conversion to int using another scale
            itemPtr = stream->readItemPtr();
            tempInt = (int)roundf(*(float*)(itemPtr + 8) * DAT_00d60d04);
            *(int*)(thisPtr + 0x1d90) = tempInt;
            break;
        case 0x24:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x618) = *(int*)(itemPtr + 8);
            break;
        case 0x25:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x61c) = *(int*)(itemPtr + 8);
            break;
        case 0x26:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x620) = *(int*)(itemPtr + 8);
            break;
        case 0x27:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x624) = *(int*)(itemPtr + 8);
            break;
        case 0x28:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x628) = *(int*)(itemPtr + 8);
            break;
        case 0x29:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x62c) = *(int*)(itemPtr + 8);
            break;
        case 0x2a:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d18) = *(int*)(itemPtr + 8);
            break;
        case 0x2b:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d1c) = *(int*)(itemPtr + 8);
            break;
        case 0x3c:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1ef0) = *(int*)(itemPtr + 8);
            break;
        case 0x3d:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d20) = *(int*)(itemPtr + 8);
            break;
        case 0x3e:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d24) = *(int*)(itemPtr + 8);
            break;
        case 0x3f: // Vector4
            stream->readItemPtr();
            vecPtr = stream->readVector4();
            *(float*)(thisPtr + 0x1e60) = vecPtr[0];
            *(float*)(thisPtr + 0x1e64) = vecPtr[1];
            *(float*)(thisPtr + 0x1e68) = vecPtr[2];
            *(float*)(thisPtr + 0x1e6c) = vecPtr[3];
            break;
        case 0x40:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d28) = *(int*)(itemPtr + 8);
            break;
        case 0x41:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d2c) = *(int*)(itemPtr + 8);
            break;
        case 0x42: // Vector4
            stream->readItemPtr();
            vecPtr = stream->readVector4();
            *(float*)(thisPtr + 0x1e74) = vecPtr[0];
            *(float*)(thisPtr + 0x1e78) = vecPtr[1];
            *(float*)(thisPtr + 0x1e7c) = vecPtr[2];
            *(float*)(thisPtr + 0x1e80) = vecPtr[3];
            break;
        case 0x43:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d30) = *(int*)(itemPtr + 8);
            break;
        case 0x44:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d38) = *(int*)(itemPtr + 8);
            break;
        case 0x45:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d3c) = *(int*)(itemPtr + 8);
            break;
        case 0x46:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x1d40) = *(int*)(itemPtr + 8);
            break;
        case 0x47: // bitfield with action
            itemPtr = stream->readItemPtr();
            uint flags = *(uint*)(itemPtr + 8);
            *(uint*)(thisPtr + 0x820) = flags;
            if ((flags & 2) != 0) {
                FUN_004706f0(1.0f); // Some function call with 1.0
            }
            break;
        case 0x48: // Vector4
            stream->readItemPtr();
            vecPtr = stream->readVector4();
            *(float*)(thisPtr + 0x1efc) = vecPtr[0];
            *(float*)(thisPtr + 0x1f00) = vecPtr[1];
            *(float*)(thisPtr + 0x1f04) = vecPtr[2];
            *(float*)(thisPtr + 0x1f08) = vecPtr[3];
            break;
        case 0x49:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x7b8) = *(int*)(itemPtr + 8);
            break;
        case 0x4a:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x7bc) = *(int*)(itemPtr + 8);
            break;
        case 0x4b:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x7c0) = *(int*)(itemPtr + 8);
            break;
        case 0x4c:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x7c4) = *(int*)(itemPtr + 8);
            break;
        case 0x4d:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x7c8) = *(int*)(itemPtr + 8);
            break;
        case 0x4e:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x7cc) = *(int*)(itemPtr + 8);
            break;
        case 0x4f:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 2000) = *(int*)(itemPtr + 8); // 2000 = 0x7d0
            break;
        case 0x50:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x7d4) = *(int*)(itemPtr + 8);
            break;
        case 0x51:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x7d8) = *(int*)(itemPtr + 8);
            break;
        case 0x52:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x7dc) = *(int*)(itemPtr + 8);
            break;
        case 0x53:
            itemPtr = stream->readItemPtr();
            *(int*)(thisPtr + 0x7e0) = *(int*)(itemPtr + 8);
            break;
        }
        stream->advance();
        hasMore = stream->hasMoreData();
    }
    stream->end();
    return;
}