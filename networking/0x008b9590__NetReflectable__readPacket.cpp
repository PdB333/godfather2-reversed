// FUNC_NAME: NetReflectable::readPacket
void __thiscall NetReflectable::readPacket(void* this, void* stream) {
    uint commandId;
    uint value;
    void* dataNode;
    int entityId;
    float* vectorPtr;
    uint* valuePtr;
    uint uiValue;
    int* intValue;

    // Initialize stream reader with hash 0xa7039c8 (likely class/type identifier)
    streamInit(stream, 0xa7039c8);

    while (!streamHasMoreData()) {
        streamAdvance(); // Skip separator/terminator?
        commandId = streamReadCommand();

        switch (commandId) {
            case 0: // Set flag bit 0 (enable/disable some state)
                dataNode = streamGetDataNode();
                if (*(int*)((uint)dataNode + 8) == 0) {
                    *(uint*)((uint)this + 0x18c) &= 0xfffffffe; // Clear bit 0
                } else {
                    *(uint*)((uint)this + 0x18c) |= 1;           // Set bit 0
                }
                break;

            case 1: // Set some field at offset 0x214
                dataNode = streamGetDataNode();
                *(uint*)((uint)this + 0x214) = *(uint*)((uint)dataNode + 8);
                break;

            case 2: // Set some field at offset 0x218
                dataNode = streamGetDataNode();
                *(uint*)((uint)this + 0x218) = *(uint*)((uint)dataNode + 8);
                break;

            case 3: // Set flag bit 1
                dataNode = streamGetDataNode();
                if (*(int*)((uint)dataNode + 8) == 0) {
                    *(uint*)((uint)this + 0x18c) &= 0xfffffffd; // Clear bit 1
                } else {
                    *(uint*)((uint)this + 0x18c) |= 2;           // Set bit 1
                }
                break;

            case 4: // Set field at offset 0x194 (could be float/int)
                dataNode = streamGetDataNode();
                *(uint*)((uint)this + 0x194) = *(uint*)((uint)dataNode + 8);
                break;

            case 5: // Set flag bit 4
                dataNode = streamGetDataNode();
                if (*(int*)((uint)dataNode + 8) == 0) {
                    *(uint*)((uint)this + 0x18c) &= 0xffffffef; // Clear bit 4
                } else {
                    *(uint*)((uint)this + 0x18c) |= 0x10;       // Set bit 4
                }
                break;

            case 6: // Set field at offset 400 (0x190)
                dataNode = streamGetDataNode();
                *(uint*)((uint)this + 400) = *(uint*)((uint)dataNode + 8);
                break;

            case 7: // Copy bitmask from stream to flag field at 0x18c (mapped bits)
                dataNode = streamGetDataNode();
                uiValue = *(uint*)((uint)dataNode + 8);
                // Each bit of uiValue maps to a specific flag bit in offset 0x18c
                if ((uiValue & 1) == 0)
                    *(uint*)((uint)this + 0x18c) &= 0xfffffbff; // Clear bit 10 (0x400)
                else
                    *(uint*)((uint)this + 0x18c) |= 0x400;     // Set bit 10
                if ((uiValue >> 1 & 1) == 0)
                    *(uint*)((uint)this + 0x18c) &= 0xffffbfff; // Clear bit 14 (0x4000)
                else
                    *(uint*)((uint)this + 0x18c) |= 0x4000;
                if ((uiValue >> 2 & 1) == 0)
                    *(uint*)((uint)this + 0x18c) &= 0xfffbffff; // Clear bit 18 (0x40000)
                else
                    *(uint*)((uint)this + 0x18c) |= 0x40000;
                if ((uiValue >> 3 & 1) == 0)
                    *(uint*)((uint)this + 0x18c) &= 0xfff7ffff; // Clear bit 19 (0x80000)
                else
                    *(uint*)((uint)this + 0x18c) |= 0x80000;
                if ((uiValue >> 4 & 1) == 0)
                    *(uint*)((uint)this + 0x18c) &= 0xffefffff; // Clear bit 20 (0x100000)
                else
                    *(uint*)((uint)this + 0x18c) |= 0x100000;
                if ((uiValue >> 5 & 1) == 0)
                    *(uint*)((uint)this + 0x18c) &= 0xff7fffff; // Clear bit 23 (0x800000)
                else
                    *(uint*)((uint)this + 0x18c) |= 0x800000;
                if ((uiValue >> 6 & 1) == 0)
                    *(uint*)((uint)this + 0x18c) &= 0xfeffffff; // Clear bit 24 (0x1000000)
                else
                    *(uint*)((uint)this + 0x18c) |= 0x1000000;
                if ((uiValue >> 7 & 1) == 0)
                    *(uint*)((uint)this + 0x18c) &= 0xfffdffff; // Clear bit 17 (0x20000)
                else
                    *(uint*)((uint)this + 0x18c) |= 0x20000;
                if ((uiValue & 0x100) == 0)
                    *(uint*)((uint)this + 0x18c) &= 0xfdffffff; // Clear bit 25 (0x2000000)
                else
                    *(uint*)((uint)this + 0x18c) |= 0x2000000;
                break;

            case 8: // Read 4-float vector into offset 0x1b4 (position?)
                streamGetDataNode(); // consume token
                vectorPtr = (float*)streamReadVector();
                *(float*)((uint)this + 0x1b4) = vectorPtr[0];
                *(float*)((uint)this + 0x1b8) = vectorPtr[1];
                *(float*)((uint)this + 0x1bc) = vectorPtr[2];
                *(float*)((uint)this + 0x1c0) = vectorPtr[3];
                break;

            case 9: // Read 4-float vector into offset 0x1c4 (rotation?)
                streamGetDataNode();
                vectorPtr = (float*)streamReadVector();
                *(float*)((uint)this + 0x1c4) = vectorPtr[0];
                *(float*)((uint)this + 0x1c8) = vectorPtr[1];
                *(float*)((uint)this + 0x1cc) = vectorPtr[2];
                *(float*)((uint)this + 0x1d0) = vectorPtr[3];
                break;

            case 10: // Resolve entity ID from string and store at offset 0x280
                streamGetDataNode();
                dataNode = (void*)streamReadString(); // returns pointer to string node
                if (dataNode != 0) {
                    entityId = lookupEntityByName(dataNode);
                    *(int*)((uint)this + 0x280) = entityId;
                    if (entityId != 0) {
                        *(char*)((uint)this + 0x21f) = 1; // Set flag byte
                    }
                    releaseStringReference(dataNode);
                }
                break;

            case 11: // Read 4-integer vector into offset 0x1d8 (maybe bounding box or other)
                streamGetDataNode();
                valuePtr = (uint*)streamReadVector();
                *(uint*)((uint)this + 0x1d8) = valuePtr[0];
                *(uint*)((uint)this + 0x1dc) = valuePtr[1];
                *(int*)((uint)this + 0x1e0) = valuePtr[2];
                *(int*)((uint)this + 0x1e4) = valuePtr[3];
                if ( *(int*)((uint)this + 0x1d8) != 0 ||
                     *(int*)((uint)this + 0x1dc) != 0 ||
                     *(int*)((uint)this + 0x1e0) != 0 ||
                     *(int*)((uint)this + 0x1e4) != 0 ) {
                    *(char*)((uint)this + 0x21c) = 1; // Set flag byte
                    *(char*)((uint)this + 0x21f) = 1;
                }
                break;

            case 12: // Set field at offset 0x1ec
                dataNode = streamGetDataNode();
                *(uint*)((uint)this + 0x1ec) = *(uint*)((uint)dataNode + 8);
                break;

            case 13: // Set field at offset 500 (0x1f4)
                dataNode = streamGetDataNode();
                *(uint*)((uint)this + 500) = *(uint*)((uint)dataNode + 8);
                break;

            case 14: // Set field at offset 0x1f0
                dataNode = streamGetDataNode();
                *(uint*)((uint)this + 0x1f0) = *(uint*)((uint)dataNode + 8);
                break;

            case 15: // Set field at offset 0x1f8
                dataNode = streamGetDataNode();
                *(uint*)((uint)this + 0x1f8) = *(uint*)((uint)dataNode + 8);
                break;

            case 16: // Set field at offset 0x1fc
                dataNode = streamGetDataNode();
                *(uint*)((uint)this + 0x1fc) = *(uint*)((uint)dataNode + 8);
                break;

            case 17: // Set field at offset 0x200
                dataNode = streamGetDataNode();
                *(uint*)((uint)this + 0x200) = *(uint*)((uint)dataNode + 8);
                break;

            case 18: // Set field at offset 0x204
                dataNode = streamGetDataNode();
                *(uint*)((uint)this + 0x204) = *(uint*)((uint)dataNode + 8);
                break;

            case 19: // Read 12 bytes (3 ints? 1 double??) into offset 0x284 (3 components
            // Possibly a Vector3 or double/float combine)
                streamGetDataNode();
                valuePtr = (uint*)streamReadVector(); // might be reading 2 or 3 values
                // But decompiled shows 8 bytes + 4 bytes = 12
                *(unsigned long long*)((uint)this + 0x284) = *(unsigned long long*)valuePtr;
                *(uint*)((uint)this + 0x28c) = *(uint*)(valuePtr + 1); // note: pointer arithmetic on uint*
                break;

            case 20: // Set field at offset 0x208
                dataNode = streamGetDataNode();
                *(uint*)((uint)this + 0x208) = *(uint*)((uint)dataNode + 8);
                break;
        }

        streamAdvance(); // Advance to next command
    }
}