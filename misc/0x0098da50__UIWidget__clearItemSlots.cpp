// FUNC_NAME: UIWidget::clearItemSlots
void __fastcall UIWidget::clearItemSlots(int this)
{
    undefined4 *slotPtr;
    int itemData;
    undefined4 uVar3;
    int slotIndex;
    uint slotCount;
    int local_70;
    int local_6c;
    undefined4 local_68;
    code *local_64;
    undefined1 local_60 [96];
    
    slotCount = 0;
    if (*(int *)(this + 0x74) != 0) { // +0x74: number of slots
        slotIndex = 0;
        do {
            local_70 = 0;
            local_6c = 0;
            local_68 = 0;
            local_64 = (code *)0x0;
            FUN_0098d7a0(local_60, "/text/popup_root/popup/contentPlaceholderMc/item%d/instance8/input",
                         slotCount); // build path string for slot
            uVar3 = FUN_004dafd0(local_60); // get UI element by path
            FUN_0098b8e0(uVar3, &local_70); // get item data from UI element
            if (local_6c != 0) { // if item data is valid
                itemData = *(int *)(*(int *)(this + 0x70) + 0x10 + slotIndex); // +0x70: slot array, +0x10: offset to slot data
                slotPtr = (undefined4 *)(*(int *)(this + 0x70) + 0x10 + slotIndex);
                if (itemData != 0) {
                    (*(code *)slotPtr[3])(itemData); // call destructor on item data
                }
                *slotPtr = 0; // clear slot data
                slotPtr[2] = 0;
                slotPtr[1] = 0;
                FUN_004d3e20(&local_70); // free item data
            }
            if (local_70 != 0) {
                (*local_64)(local_70); // release UI element
            }
            slotCount = slotCount + 1;
            slotIndex = slotIndex + 0x4c; // each slot is 0x4c bytes
        } while (slotCount < *(uint *)(this + 0x74));
    }
    return;
}