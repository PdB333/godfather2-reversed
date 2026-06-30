// FUNC_NAME: TerrainPatchBuffer::addPatch
void __fastcall TerrainPatchBuffer::addPatch(uint32_t* param1, uint32_t* param2)
{
    // Global buffer: array of 512 terrain patch structures, each 0x60 bytes.
    // gTerrainPatchCount current index (DAT_0120596c)
    // Buffer starts at DAT_011f7540

    uint32_t index = gTerrainPatchCount; // DAT_0120596c
    uint8_t* patchBase = (uint8_t*)&gTerrainPatchBuffer + (index * 0x60); // &DAT_011f7540 + index*96

    // Copy fields from param1 (12 uint32s at offsets 0..11)
    *(uint32_t*)(patchBase + 0x00) = param1[0];   // +0x00: field0
    *(uint32_t*)(patchBase + 0x04) = param1[1];   // +0x04: field1
    *(uint32_t*)(patchBase + 0x14) = 0;            // +0x14: unaff_ESI (treated as 0)
    *(uint32_t*)(patchBase + 0x08) = param1[2];   // +0x08: field2
    *(uint32_t*)(patchBase + 0x24) = 0;            // +0x24: unaff_ESI
    *(uint32_t*)(patchBase + 0x18) = param2[0];   // +0x18: from param2[0]
    *(uint32_t*)(patchBase + 0x54) = 0;            // +0x54: unaff_ESI
    *(uint32_t*)(patchBase + 0x10) = param2[1];   // +0x10: from param2[1]
    *(uint32_t*)(patchBase + 0x1C) = param1[3];   // +0x1C: field3
    *(uint32_t*)(patchBase + 0x20) = param1[4];   // +0x20: field4
    *(uint32_t*)(patchBase + 0x28) = param1[5];   // +0x28: field5
    *(uint32_t*)(patchBase + 0x2C) = param2[2];   // +0x2C: from param2[2]
    *(uint32_t*)(patchBase + 0x30) = param2[3];   // +0x30: from param2[3]
    *(uint32_t*)(patchBase + 0x34) = param1[6];   // +0x34: field6
    *(uint32_t*)(patchBase + 0x38) = param1[7];   // +0x38: field7
    *(uint32_t*)(patchBase + 0x3C) = param1[8];   // +0x3C: field8
    *(uint32_t*)(patchBase + 0x40) = param2[4];   // +0x40: from param2[4]
    *(uint32_t*)(patchBase + 0x44) = param2[5];   // +0x44: from param2[5]
    *(uint32_t*)(patchBase + 0x48) = param1[9];   // +0x48: field9
    *(uint32_t*)(patchBase + 0x4C) = param1[10];  // +0x4C: field10
    *(uint32_t*)(patchBase + 0x50) = param1[11];  // +0x50: field11
    *(uint32_t*)(patchBase + 0x58) = param2[6];   // +0x58: from param2[6]
    *(uint32_t*)(patchBase + 0x5C) = param2[7];   // +0x5C: from param2[7]

    gTerrainPatchCount = index + 1;

    // When buffer is full (512 patches), process and clear
    if (gTerrainPatchCount == 512) {
        if (gTerrainPatchCount != 0) {
            // Load/process the buffer
            FUN_00612210(&DAT_00f15640);  // likely lock or begin processing

            DAT_01127774 = DAT_01127878;   // some global handles
            DAT_01127868 = FUN_0060a580(DAT_01127878, "lodBias"); // get LOD bias string

            if (DAT_012058e8 == &PTR_PTR_01127760) {
                FUN_0060a460(DAT_01127774);  // reset/clear
                FUN_0060aa90(DAT_01127774, DAT_01127868, DAT_01127840); // set LOD bias
            }

            FUN_00619950();  // finalize terrain data
            FUN_00619650();  // recalc normals? 
            FUN_0060cc10(13, gTerrainPatchCount * 4, &gTerrainPatchBuffer, 24); // submit buffer to renderer (type 13, size patches*4?, stride 24)
            FUN_00612e00();  // cleanup

            // Zero out some globals (likely min/max bounds)
            _DAT_01127804 = 0;
            _DAT_01127808 = 0;
            _DAT_0112780c = 0;
            _DAT_01127810 = 0;
            _DAT_01127814 = 0;
            _DAT_01127818 = 0;
            _DAT_0112781c = 0;

            FUN_00612210(&DAT_011f6b70); // unlock/unflush
            gTerrainPatchCount = 0;      // reset index
        }
    }
}