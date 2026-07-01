// FUNC_NAME: ConnectionManager::processSendQueue

void __thiscall ConnectionManager::processSendQueue(int thisObj, uint data1, uint data2)
{
    byte* pbVar1;
    byte bVar2;
    uint currentSlotIndex;
    uint uVar4;
    int counter;
    uint* puVar6;

    counter = 0;
    puVar6 = (uint*)(thisObj + 0x18);  // start of slot array

    // Search for a slot that matches the current ID and is not flagged with bit1
    while (true) {
        currentSlotIndex = FUN_00791750();  // get current slot ID
        if (puVar6[1] == currentSlotIndex && ((*puVar6 >> 1 & 1) == 0))
            break;  // found matching slot with bit1 clear

        ++counter;
        puVar6 += 9;  // each slot is 9 dwords (0x24 bytes)
        if (counter > 6)
            return;  // no empty slot found
    }

    pbVar1 = (byte*)(thisObj + 0x18 + counter * 0x24);  // pointer to the found slot

    if (pbVar1 != nullptr) {
        bVar2 = *pbVar1;  // first byte of slot status

        // Wait until the slot's bit0 becomes set, while incrementing a global counter
        while ((bVar2 & 1) == 0) {
            *(int*)(thisObj + 0x14) += 1;  // m_sendIndex

            switch (*(int*)(thisObj + 0x14)) {
                case 8:
                    *(uint*)(thisObj + 0xf0) |= 1;  // slot[6].flags
                case 7:
                    *(uint*)(thisObj + 0xcc) |= 1;  // slot[5].flags
                case 5:
                case 6:
                    *(uint*)(thisObj + 0x84) |= 1;  // slot[3].flags
                case 4:
                    *(uint*)(thisObj + 0xa8) |= 1;  // slot[4].flags
                case 3:
                    *(uint*)(thisObj + 0x60) |= 1;  // slot[2].flags
                case 2:
                    *(uint*)(thisObj + 0x3c) |= 1;  // slot[1].flags
                case 1:
                    *(uint*)(thisObj + 0x18) |= 1;  // slot[0].flags
                default:
                    bVar2 = *pbVar1;  // re-read slot status
            }
        }

        // Now slot is ready, package data and send
        uVar4 = 0;
        uint slotID = FUN_00791750(data1, data2, counter, 0);
        FUN_0090b4e0(slotID, data1, data2, counter, uVar4);
    }
    return;
}