// FUNC_NAME: DataBlock::Deserialize

// Reads binary data stream for a data block object.
// param_1: this pointer (DataBlock)
// param_2: stream handle (opaque ID)
// Offsets:
// +0x50: bool enabled
// +0x60..0x9c: 16 uint32 fields (e.g., matrix or color)
// +0xa0, +0xa8: string/ID fields (stored via String::Set)
// +0xb0..0xef: array of 4-int blocks, count at +0xf0 (max 4 entries)

void __thiscall DataBlock::ReadFromStream(DataBlock* thisPtr, uint streamHandle)
{
    bool streamEnd;
    int blockData[4];
    int dataType;
    int* blockArray;
    int val0, val1, val2, val3;
    int blockCount;
    int i;
    // Stack buffer for initial 16-byte read
    int initialBlock[4];

    // Initialize stream for reading
    StreamInit(streamHandle);
    // Begin reading a named block (tag 0xb390b11a)
    StreamBeginBlock(streamHandle, 0xb390b11a);
    // Set block version to 1
    StreamSetVersion(1);

    streamEnd = StreamIsEnded(streamHandle);
    if (streamEnd == false)
    {
        // Read the initial 16-byte block (4 ints) from stream
        StreamReadInt32Array(streamHandle, initialBlock, 4);
        // Process the initial block (maybe convert endian-ness or validate)
        StreamProcessInt32Array(streamHandle, initialBlock, 4);

        // Copy the 16 bytes to this+0x60..0x9c
        thisPtr->field_60 = initialBlock[0];
        thisPtr->field_64 = initialBlock[1];
        thisPtr->field_68 = initialBlock[2];
        thisPtr->field_6C = initialBlock[3];
        // Note: offset 0x70..0x9c are also written but not shown in decompiled? Let's check: decompiled shows local_130..local_f4 (16 elements) copied to offsets 0x60,100=0x64,0x68,0x6c,0x70,0x74,0x78,0x7c,0x80,0x84,0x88,0x8c,0x90,0x94,0x98,0x9c.
        // Actually the decompiled code:
        // local_124 = 0; local_114 = 0; local_104 = 0; local_f4 = _DAT_00d5780c;
        // then FUN_0043b210(puVar8); reads into puVar8 which points to local_130 (so local_130..local_10c? wait, local_130 is first, then local_12c, local_128, local_124, local_120, local_11c, local_118, local_114, local_110, local_10c, local_108, local_104, local_100, local_fc, local_f8, local_f4. That's 16 dwords.
        // Then FUN_0043ad90(puVar8); processes them.
        // Then:
        // *(undefined4 *)(param_1 + 0x60) = local_130;
        // *(undefined4 *)(param_1 + 100) = local_12c;  (100 decimal = 0x64)
        // *(undefined4 *)(param_1 + 0x68) = local_128;
        // *(undefined4 *)(param_1 + 0x6c) = local_124;
        // *(undefined4 *)(param_1 + 0x70) = local_120;
        // *(undefined4 *)(param_1 + 0x74) = local_11c;
        // *(undefined4 *)(param_1 + 0x78) = local_118;
        // *(undefined4 *)(param_1 + 0x7c) = local_114;
        // *(undefined4 *)(param_1 + 0x80) = local_110;
        // *(undefined4 *)(param_1 + 0x84) = local_10c;
        // *(undefined4 *)(param_1 + 0x88) = local_108;
        // *(undefined4 *)(param_1 + 0x8c) = local_104;
        // *(undefined4 *)(param_1 + 0x90) = local_100;
        // *(undefined4 *)(param_1 + 0x94) = local_fc;
        // *(undefined4 *)(param_1 + 0x98) = local_f8;
        // *(undefined4 *)(param_1 + 0x9c) = local_f4;
        // So I need to write all 16. I'll store them in initialBlock array, but initialBlock is only 4 ints. Actually the decompiled uses separate variables: local_130, local_12c, ... up to local_f4. They are all undefined4 (int). That's 16 separate stack variables. To simplify, I'll use an array of 16 ints.
        int initialData[16];
        // The code sets local_124, local_114, local_104 to 0, and local_f4 from global, then reads the whole block. So the read fills 16 ints.
        // So I'll replace with:
        int initialData[16];
        initialData[3] = 0; // local_124 offset third? need to match indices: Let's map:
        // local_130 [0]
        // local_12c [1]
        // local_128 [2]
        // local_124 [3]
        // local_120 [4]
        // local_11c [5]
        // local_118 [6]
        // local_114 [7]
        // local_110 [8]
        // local_10c [9]
        // local_108 [10]
        // local_104 [11]
        // local_100 [12]
        // local_fc [13]
        // local_f8 [14]
        // local_f4 [15] - initialized from global
        initialData[7] = 0; // local_114 is index 7
        initialData[11] = 0; // local_104 is index 11
        initialData[15] = globals__DAT_00d5780c; // _DAT_00d5780c is a global variable
        // Then read into &initialData[0] (base of array)
        StreamReadInt32Array(streamHandle, initialData, 16);
        StreamProcessInt32Array(streamHandle, initialData, 16);
        // Then copy to fields
        thisPtr->field_60 = initialData[0];
        thisPtr->field_64 = initialData[1];
        thisPtr->field_68 = initialData[2];
        thisPtr->field_6C = initialData[3];
        thisPtr->field_70 = initialData[4];
        thisPtr->field_74 = initialData[5];
        thisPtr->field_78 = initialData[6];
        thisPtr->field_7C = initialData[7];
        thisPtr->field_80 = initialData[8];
        thisPtr->field_84 = initialData[9];
        thisPtr->field_88 = initialData[10];
        thisPtr->field_8C = initialData[11];
        thisPtr->field_90 = initialData[12];
        thisPtr->field_94 = initialData[13];
        thisPtr->field_98 = initialData[14];
        thisPtr->field_9C = initialData[15];
    }

    // Begin another block with a different tag (0x42e409b)
    StreamBeginBlock(streamHandle, 0x42e409b);
    streamEnd = StreamIsEnded(streamHandle);
    if (streamEnd == false)
    {
        // Early exit if stream ended? Actually no: the loop below runs, and if streamEnd is false initially, it will loop until end.
        // Actually the decompiled code does: cVar4 = FUN_0043b120(); do { if (cVar4 != '\0') { ... return; } ... } while(true);
        // So it's a loop that continues until stream end.
        // I'll restructure with a while loop.
    }

    while (true)
    {
        streamEnd = StreamIsEnded(streamHandle);
        if (streamEnd)
        {
            // If the block is enabled (flag at +0x50), call post-read handler
            if (thisPtr->enabled)
            {
                DataBlock::PostRead(thisPtr, streamHandle);
            }
            return;
        }

        StreamBeginRead(streamHandle);  // FUN_0043b210
        dataType = StreamGetDataType(streamHandle); // FUN_0043ab70
        switch (dataType)
        {
        case 0: // bool field
            StreamBeginRead(streamHandle);
            thisPtr->enabled = (StreamReadInt32(streamHandle) != 0); // FUN_0043b210 returns pointer, then read int at offset 8? Actually decompiled: iVar6 = FUN_0043b210(); *(bool *)(param_1 + 0x50) = *(int *)(iVar6 + 8) != 0; So it reads an int from offset 8 of the buffer returned by FUN_0043b210. That's likely StreamReadBool.
            // I'll simplify as StreamReadBool
            thisPtr->enabled = StreamReadBool(streamHandle);
            break;
        case 1: // string field 1
            StreamBeginRead(streamHandle);
            StringSet(&thisPtr->field_A0, StreamGetString(streamHandle)); // FUN_0043ab90 returns string
            break;
        case 2: // string field 2
            StreamBeginRead(streamHandle);
            StringSet(&thisPtr->field_A8, StreamGetString(streamHandle));
            break;
        case 3:
        case 4:
        case 5:
        case 6: // 4-int block
            StreamBeginRead(streamHandle);
            blockArray = StreamGetInt32Array(streamHandle); // FUN_0043abc0 returns pointer to 4 ints
            val0 = blockArray[0];
            val1 = blockArray[1];
            val2 = blockArray[2];
            val3 = blockArray[3];
            // Check if the block is a sentinel (all zeros or specific magic)
            bool shouldStore = true;
            if (val0 == SENTINEL_MAGIC_0)
            {
                if (val1 == SENTINEL_MAGIC_1 && val2 == SENTINEL_MAGIC_2 && val3 == SENTINEL_MAGIC_3)
                {
                    shouldStore = false; // skip storing if all magic match
                }
            }
            else if (val0 == 0 && val1 == 0 && val2 == 0 && val3 == 0)
            {
                shouldStore = false; // skip storing if all zeros
            }
            if (shouldStore)
            {
                blockCount = thisPtr->blockCount; // +0xf0
                if (blockCount < 4)
                {
                    int* dest = &thisPtr->blockArray[blockCount * 4]; // +0xb0 base
                    dest[0] = val0;
                    dest[1] = val1;
                    dest[2] = val2;
                    dest[3] = val3;
                    thisPtr->blockCount = blockCount + 1;
                }
            }
            break;
        }
        StreamNext(streamHandle); // FUN_0043b1a0
    }
}