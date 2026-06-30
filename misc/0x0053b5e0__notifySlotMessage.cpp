// FUNC_NAME: notifySlotMessage
void __fastcall notifySlotMessage(int unusedParam, int messageParam)
{
    uint currentSlotIndex = *(uint*)0x01125388;          // global current slot index (e.g., for iterating slots)
    int* slotPointer = *(int**)(0x011253f4 + currentSlotIndex * 0x38);  // array of slot structures (0x38 bytes each)
    if (slotPointer != 0)
    {
        // If the slot has a valid object, forward the message
        FUN_0060b020(*(int*)0x011252e8, slotPointer, messageParam);  // manager callback
    }
}