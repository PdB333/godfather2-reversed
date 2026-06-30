// FUN_004613a0: OverrideManager::registerOverride
void __fastcall OverrideManager::registerOverride(int thisPtr)
{
    int resourceId;
    int overrideType;

    resourceId = *(int *)(thisPtr + 0x264);
    if ((resourceId != 0) && (*(int *)(thisPtr + 0x164) != 0)) {
        int *vtableSlotPtr = (int *)(DAT_01206880 + 0x14);
        overrideType = *(int *)(thisPtr + 0x260);
        // Replace current vtable pointer at the global override table slot
        **(int **)(DAT_01206880 + 0x14) = (int)&PTR_LAB_0110b974;
        *vtableSlotPtr = *vtableSlotPtr + 4; // Move to next slot
        // Load 16 bytes of override data into buffer at this+0x54 using the resource ID (packed from type and id)
        FUN_00461a30(thisPtr + 0x54, CONCAT44(resourceId, overrideType), 0x10);
    }
}