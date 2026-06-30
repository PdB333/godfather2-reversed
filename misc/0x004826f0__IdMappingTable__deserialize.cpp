// FUNC_NAME: IdMappingTable::deserialize
void __thiscall IdMappingTable::deserialize(uint32_t *buffer)
{
    uint16_t *usa;
    short sVar2;
    uint16_t uVar3;
    int iVar4;
    int iVar5;
    uint16_t uVar6;
    int *piVar7;
    uint32_t uVar8;

    // copy header
    header = buffer[0];
    count = 0;
    uVar6 = (uint16_t)buffer[1];  // low word of second dword
    maxId = uVar6;                // store the max ID value
    totalSize = (uint32_t)uVar6 * 4 + 4; // expected total size

    // clear reverse map (0->0xfe, 255 entries, 510 bytes)
    memset(reverseMap, 0, 0x1fe);

    // allocate space for flagArray and idArray together (3 bytes per ID)
    iVar4 = FUN_009c8e80((uint32_t)maxId * 3); // e.g., allocate memory
    flagArray = (uint8_t *)iVar4;
    idArray = (uint16_t *)(maxId + iVar4); // idArray follows flagArray

    if (maxId != 0) {
        piVar7 = (int *)(DAT_01223490 + 4); // global table base +4
        uVar6 = 0;
        do {
            uVar8 = (uint32_t)uVar6;
            iVar5 = FUN_00482ce0(buffer + uVar8 + 2); // get index into global table
            usa = (uint16_t *)(iVar5 * 0x10 + 4 + *piVar7); // structure of size 0x10
            idArray[uVar8] = (uint16_t)iVar5; // store ID
            flagArray[uVar8] = *(uint8_t *)((uint8_t *)usa + 3); // store flags

            uVar6 = uVar6 + 1;
            // store mapping from original ID to local index+1 (1-based)
            reverseMap[usa[2]] = uVar6;

            if ((flagArray[uVar8] & 1) != 0) {
                // adjust totalSize if this ID has additional data
                totalSize = totalSize + (uint32_t)(uint8_t)usa[1] + (uint32_t)usa[0];
            }
        } while (uVar6 < maxId);
    }

    // resolve duplicate/reverse mappings: propagate first found IDs
    uVar6 = 0;
    do {
        sVar2 = reverseMap[uVar6]; // existing mapping
        if ((sVar2 != 0) && (uVar3 = *(uint16_t *)(*(int *)(iVar4 + 0x10) + (uint32_t)uVar6 * 2), uVar3 != 0))
        {
            if (reverseMap[uVar3] == 0) {
                reverseMap[uVar3] = sVar2;
                uVar6 = 0; // restart scan
            }
        }
        uVar6 = uVar6 + 1;
    } while (uVar6 < 0xff);
}