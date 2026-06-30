// FUNC_NAME: SomeManager::processActiveSlot
// Address: 0x005c1d00
// This function seems to process an active slot (controller or object) based on a global index (DAT_00f17914).
// It makes virtual calls on 'this' and on another object pointed to by a member at offset +0x10.
// Pattern suggests it's part of an input or controller manager, updating a selected slot's state.

int SomeManager::processActiveSlot()
{
    // Call virtual function at vtable+4 (likely preUpdate or validate)
    (this->*vtable[4])(); // Unknown virtual

    // Check global active slot index
    if (g_activeSlotIndex < 0)
        goto done;

    int* slotPtr = &g_slotArray[g_activeSlotIndex]; // global array of pointers
    if (slotPtr == 0)
        goto done;

    // Call virtual at vtable+0x24 on this (something like getActiveObject?)
    int result = (this->*vtable[0x24])(); // Unknown virtual, returns int
    if (result != 0)
    {
        int* slotData = *slotPtr; // dereference to get some structure pointer
        // Call virtual at vtable+4 on the object stored at this+0x10 (offset 16)
        int value = (*(this->memberAtOffset0x10)->vtable[4])(); // returns something
        // Call virtual at vtable+0x14 on slotData, passing the value
        (slotData->vtable[0x14])(value); // slotData->someMethod(value)
    }

done:
    // Call virtual at vtable+0 (likely postUpdate or destructor? )
    (this->*vtable[0])();
    return 2; // Return code 2 (maybe "processed" or "continue")
}