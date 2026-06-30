// FUNC_NAME: GameEventManager::dispatchEvent
void __cdecl GameEventManager::dispatchEvent(int32_t handlerIndex, int32_t triggerParam, uint8_t extraData)
{
    if (triggerParam != 0)
    {
        // gEventHandlers is a global array with stride 0x10 (16 bytes per entry)
        // Each entry is a pointer to an IEventHandler object
        // Offset 0x34 is a virtual method: onEvent(context, triggerParam, extraData)
        void **handler = *(void ***)((uint8_t *)gEventHandlers + handlerIndex * 0x10);
        if (handler != nullptr)
        {
            // gEventContext is the global context passed to the handler (e.g., event source or manager)
            (*(void (__thiscall **)(void *, void *, int32_t, uint8_t))(*(uint32_t *)handler + 0x34))
                (handler, (void *)gEventContext, triggerParam, extraData);
        }
    }
}