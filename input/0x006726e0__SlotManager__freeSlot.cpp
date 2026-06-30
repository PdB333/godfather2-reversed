// FUNC_NAME: SlotManager::freeSlot
void __fastcall SlotManager::freeSlot(void* slotPtr, void* resultPtr)
{
    // slotPtr is the this pointer (in EAX) pointing to a slot structure
    // resultPtr is param_1, an output parameter set to null

    int32_t slotIndex = *(int32_t*)((uint8_t*)slotPtr - 8);          // Slot index stored at offset -8 from slotPtr
    SlotManager* manager = *(SlotManager**)((uint8_t*)slotPtr + 0x28); // +0x28: pointer to owning manager

    *resultPtr = nullptr;

    // Clear the entry in the manager's slot array
    ((uint32_t*)manager->entries)[slotIndex] = 0;    // manager entries: +0x0c (array of uint32_t)
    manager->count--;                                 // +0x04: active slot count

    // Destroy the slot object itself (located at offset -0x10 from slotPtr)
    void* slotObject = (uint8_t*)slotPtr - 0x10;
    ((void (*)(void*))DAT_01206694)(slotObject);     // Free function pointer (likely operator delete or destructor)

    // Some global lock or synchronization function
    FUN_00672fd0();

    // Free the manager's entries array and the manager itself
    ((void (*)(void*))DAT_01206694)(manager->entries); // +0x0c: entries array
    ((void (*)(void*))DAT_01206694)(manager);          // +0x00: manager object base
}