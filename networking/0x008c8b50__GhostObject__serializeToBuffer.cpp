// FUNC_NAME: GhostObject::serializeToBuffer
void __thiscall GhostObject::serializeToBuffer(int ghostObject, uint32_t* buffer)
{
    // ghostObject: this pointer for the GhostObject
    // buffer: output buffer (array of uint32_t) to be filled with serialized ghost data

    int subObject = *(int*)(ghostObject + 8);                     // +0x8: pointer to sub-object (e.g., Transform)
    buffer[0] = *(uint32_t*)(subObject + 0x20);                   // subObj position X / some vector component
    buffer[1] = *(uint32_t*)(subObject + 0x24);                   // subObj position Y
    buffer[2] = *(uint32_t*)(subObject + 0x28);                   // subObj position Z
    buffer[3] = *(uint32_t*)(subObject + 0x2C);                   // subObj orientation or extra component
    buffer[4] = *(uint32_t*)(ghostObject + 4);                    // +0x4: object ID or type
    buffer[5] = *(uint32_t*)(ghostObject + 0x14);                 // +0x14: some state field
    buffer[6] = *(uint32_t*)(ghostObject + 0x18);                 // +0x18: another state field
    buffer[7] = 0;                                                // flags initially zero

    // Check bit 29 of a field at subObject+0x5C (maybe a state mask)
    if (((*(uint32_t*)(subObject + 0x5C) >> 0x1D) & 1) != 0) {
        buffer[7] |= 2;                                           // set flag 2 if rolling/interpolating?
    }

    if (*(int*)(ghostObject + 0x10) == 0) {                       // +0x10: pointer to additional data or null
        buffer[8] = 0;
    } else {
        // Serialize sub-data into buffer+8 (8 uint32s offset)
        FUN_008fda90(buffer + 8);
    }

    buffer[0xB] = 0;                                              // slot 0xB: zero (padding or reserved)
    buffer[9] = *(uint32_t*)(subObject + 0xC4);                  // +0xC4: some ID or timestamp
    buffer[10] = 0x14;                                            // default team/value

    // Retrieve a global manager (likely PlayerManager)
    int playerManager = FUN_00791300();
    if (playerManager != 0) {
        int playerIndexPtr = *(int*)(playerManager + 0x74C);     // +0x74C: player data array
        if (playerIndexPtr != 0) {
            if (playerIndexPtr != 0x48) {                        // sanity check
                if (*(char*)(playerIndexPtr + 0x160) == '\x01') { // +0x160: enabled flag
                    buffer[10] = (uint32_t)*(unsigned char*)(playerIndexPtr + 0x165); // +0x165: team/color index
                }
            }
        }
    }

    buffer[0xC] = 0xFFFFFFFF;                                     // default ghost index = -1
    uint32_t sequence = FUN_00791750();                           // global sequence/timestamp
    buffer[0xD] = sequence;

    buffer[0xE] = 0;                                               // default extra data

    int netSession = 0;
    if (*(int*)(ghostObject + 8) != 0) {
        netSession = FUN_0043b870(DAT_01131010);                  // DAT_01131010: global NetSession singleton
    }
    // netSession may be a pointer to a network session object; read field at +0x1C
    buffer[0xF] = *(uint32_t*)(netSession + 0x1C);               // +0x1C: session ID or timestamp

    // Magic packet signatures (identify packet type)
    buffer[0x10] = 0xBADBADBA;
    buffer[0x11] = 0xBEEFBEEF;
    buffer[0x12] = 0xEAC15A55;
    buffer[0x13] = 0x91100911;

    // Check bit 0 of a field at subObject+0x5F (another state flag)
    if ((*(unsigned char*)(subObject + 0x5F) & 1) != 0) {
        buffer[7] |= 1;                                           // set flag 1
    }

    // Global array for ghost data (likely indexed by ghost index)
    int ghostArrayBase = DAT_0112989c;
    // Check type of object: if it's a known ghost type (0x637B907)
    if (*(int*)(*(int*)(ghostObject + 0xC) + 0x54) == 0x637B907) {
        int ghostIndex = FUN_0090b0a0(*(uint32_t*)(ghostObject + 8)); // get ghost index from sub-object
        if (ghostIndex != -1) {
            int ghostEntry = ghostArrayBase + 0x18 + ghostIndex * 0x24; // each entry 0x24 bytes, base +0x18 offset
            if (ghostEntry != 0) {
                buffer[0xC] = ghostIndex;
                buffer[0xE] = *(uint32_t*)(ghostEntry + 0x10);
                buffer[0x10] = *(uint32_t*)(ghostEntry + 0x14);   // overwrite magic with stored data
                buffer[0x11] = *(uint32_t*)(ghostEntry + 0x18);
                buffer[0x12] = *(uint32_t*)(ghostEntry + 0x1C);
                buffer[0x13] = *(uint32_t*)(ghostEntry + 0x20);
            }
        }
    }
    return;
}