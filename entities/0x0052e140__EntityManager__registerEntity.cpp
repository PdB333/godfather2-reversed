// FUNC_NAME: EntityManager::registerEntity
void EntityManager::registerEntity(void)
{
    int slotIndex;
    undefined8 *entityData;
    int currentSlot;
    uint offset;
    undefined8 *entityDataPtr;
    
    slotIndex = *in_EAX; // +0x00: current slot index
    if (-1 < slotIndex) {
        // Slot already assigned, update entity data
        *(undefined8 *)(&DAT_01219388 + slotIndex * 6) = *unaff_EDI; // entity ID
        (&DAT_01219390)[slotIndex * 3] = unaff_EDI[1]; // entity type
        *(undefined8 *)(&DAT_01219398 + slotIndex * 6) = unaff_EDI[2]; // entity data
        return;
    }
    
    // Find empty slot
    if ((DAT_01219858 < 0x1f) && (*(int *)(unaff_EDI + 1) != 0)) {
        currentSlot = 0;
        entityData = (undefined8 *)&DAT_01219388;
        offset = 0;
        do {
            if (0x2ff < offset) break;
            if (*(int *)(entityData + 1) == 0) {
                *entityData = *unaff_EDI;
                entityData[1] = unaff_EDI[1];
                uVar1 = *(undefined4 *)((int)unaff_EDI + 0x14);
                *(undefined4 *)(entityData + 2) = *(undefined4 *)(unaff_EDI + 2);
                *(undefined4 *)((int)entityData + 0x14) = uVar1;
                *in_EAX = currentSlot;
                DAT_01219858 = DAT_01219858 + 1;
            }
            currentSlot = currentSlot + 1;
            offset = offset + 0x18;
            entityData = entityData + 3;
        } while (*in_EAX < 0);
    }
    
    // Assign to category
    if ((-1 < *in_EAX) && (DAT_01219859 < 0x1f)) {
        currentSlot = 0;
        offset = 0x4a0;
        do {
            if (*(int *)((int)&DAT_01219388 + offset) == *(int *)(&DAT_01219390 + *in_EAX * 3)) {
                (&DAT_0121982c)[currentSlot * 2] = (&DAT_0121982c)[currentSlot * 2] + 1;
                (&DAT_01219688)[*in_EAX] = currentSlot;
                return;
            }
            offset = offset + 8;
            currentSlot = currentSlot + 1;
        } while (offset < 0x4d0);
        
        currentSlot = 0;
        offset = 0x4a0;
        do {
            if (*(int *)((int)&DAT_01219388 + offset) == 0) {
                (&DAT_0121982c)[currentSlot * 2] = 1;
                (&DAT_01219828)[currentSlot * 2] = *(undefined4 *)(&DAT_01219390 + *in_EAX * 3);
                (&DAT_01219688)[*in_EAX] = currentSlot;
                (&DAT_01219708)[*in_EAX] = 0;
                if ((*(uint *)((int)unaff_EDI + 0xc) & 0x1000000) != 0) {
                    (&DAT_01219708)[*in_EAX] = (&DAT_01219398)[*in_EAX * 6];
                }
                DAT_01219859 = DAT_01219859 + 1;
                return;
            }
            offset = offset + 8;
            currentSlot = currentSlot + 1;
        } while (offset < 0x4d0);
    }
    return;
}