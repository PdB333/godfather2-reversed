// FUNC_NAME: SlotManager::attachToFourSlots
void __thiscall SlotManager::attachToFourSlots(uint this, void* pResource)
{
    // Set resource's field at +0x10 to 0 (likely a usage count or version)
    *(int*)((char*)pResource + 0x10) = 0;

    // Initialize four slots at offsets 0xb0, 0xc0, 0xd0, 0xe0 from this
    // Each slot is 0x10 bytes apart, and the helper function (FUN_008117c0) 
    // likely links the resource to each slot.
    connectSlot(this + 0xb0, pResource);
    connectSlot(this + 0xc0, pResource);
    connectSlot(this + 0xd0, pResource);
    connectSlot(this + 0xe0, pResource);
}