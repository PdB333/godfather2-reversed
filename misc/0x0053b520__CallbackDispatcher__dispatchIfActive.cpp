// FUNC_NAME: CallbackDispatcher::dispatchIfActive
void __fastcall CallbackDispatcher::dispatchIfActive(int unusedParam1, void* extraParam)
{
    // Global index selecting which slot to check
    // Slot array: each element is 0x38 bytes, first 4 bytes is a handler pointer
    // +0x00: handler (void*)
    // +0x34: other data (unused here)
    int activeSlotIndex = *(int*)0x01125388;            // g_activeSlotIndex
    void* slotBase = (void*)0x01125410;                // g_slotArray
    void** handlerPtr = (void**)((uint8_t*)slotBase + activeSlotIndex * 0x38);

    if (*handlerPtr != nullptr)
    {
        // Invoke the handler with a global context and the original extra parameter
        // FUN_0060add0 signature: void dispatchContext(void* context, void* handler, void* param)
        ((void(*)(void*, void*, void*))0x0060add0)(
            *(void**)0x011252e8,   // g_systemContext (e.g., manager or event dispatcher)
            *handlerPtr,
            extraParam
        );
    }
}