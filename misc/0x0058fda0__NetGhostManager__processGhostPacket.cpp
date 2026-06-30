// FUNC_NAME: NetGhostManager::processGhostPacket
int NetGhostManager::processGhostPacket(PacketDescriptor* packet, undefined4 param3, undefined4 param4, undefined4 param5, uint flags, undefined4 param7)
{
    byte opcode;
    short* shortsPtr;
    int result;
    char type;
    int copySize;
    int destBuffer;
    int srcBuffer;
    undefined4 vecX, vecY, vecZ;
    undefined4 vector[3];

    // Packet structure: +0x00 state, +0x01 type, +0x04 short array ptr, +0x0C data pointer
    type = *(packet + 1);
    if (type > 0) {
        shortsPtr = *(short**)(packet + 4);
        opcode = **(byte**)(packet + 0xC);
        if ((opcode & 0x3F) < 0x23) {
            // Dispatch table at 0x0103afc0 indexed by opcode & 0x3F
            result = dispatchTable[opcode & 0x3F](this, *(byte**)(packet + 0xC), param3, param4, param5, flags, param7);
            if (result != 0) {
                if (((flags & 4) == 0) && ((*(uint*)(this + 0x10) >> 8 & 1) == 0)) {
                    // Begin snapshot read
                    if (beginSnapshotRead() == 0) {
                        // Allocate snapshot buffer
                        destBuffer = allocateSnapshot();
                        initSnapshotState();
                        prepareSnapshotV1();
                        prepareSnapshotV2();
                        prepareSnapshotV3();

                        // Copy ghost data from source to new buffer
                        srcBuffer = *(int*)(*(int*)(result + 0x38) + 0xC); // +0x38->+0xC size
                        copySize = getGhostSize(srcBuffer); // FUN_0056ef10 likely returns size in elements
                        *(int*)(destBuffer + 0x38) = copySize;
                        _memcpy((void*)(copySize + 0x10), (void*)(*(int*)(result + 0x38) + 0x10), srcBuffer << 5); // each element 32 bytes
                        finishSnapshotCopy();
                        result = destBuffer;
                    }

                    // Process first target pair (shorts[0], shorts[1]) with action shorts[2]
                    if ((shortsPtr[0] >= 0) && (shortsPtr[1] >= 0)) {
                        if (isGhostIdValid(result, shortsPtr[0]) != 0) {
                            // Copy vector from somewhere (likely from stack set by dispatch)
                            vecX = vector[0];
                            vecY = vector[1];
                            vecZ = vector[2];
                            setTargetPosition(this, &vecX); // Set target position with XYZ
                            applyActionEffect(auStack_170, result, (char)shortsPtr[2]);
                        }
                    }

                    // Process second target pair (shorts[3], shorts[4]) with action shorts[5]
                    if ((shortsPtr[3] >= 0) && (shortsPtr[4] >= 0)) {
                        if (isGhostIdValid(result, shortsPtr[3]) != 0) {
                            vecX = vector[0];
                            vecY = vector[1];
                            vecZ = vector[2];
                            setTargetPosition(this, &vecX);
                            applyActionEffect(auStack_170, result, (char)shortsPtr[5]);
                        }
                    }
                }
                return result;
            }
        }
    }
    return 0;
}