// FUNC_NAME: InputControllerManager::updateControllerSlots
void __thiscall InputControllerManager::updateControllerSlots(void *this, uint someArg)
{
    // +0x20: pointer to a flag or active state indicator (non-null means system is initialized)
    if (*(int32_t *)((uint8_t *)this + 0x20) != 0)
    {
        // Array of global data slots (each likely represents a controller or device block)
        static const uint32_t *gSlotData[] = {
            (uint32_t *)0x01135af0,
            (uint32_t *)0x01135eb0,
            (uint32_t *)0x01136130,
            (uint32_t *)0x01135ff0,
            (uint32_t *)0x01135d70,
            (uint32_t *)0x011363b0
        };
        const int numSlots = sizeof(gSlotData) / sizeof(gSlotData[0]);

        for (int i = 0; i < numSlots; ++i)
        {
            // First function: processes the slot data, uses a global context (DAT_01206880) and a pointer to someArg as a temporary buffer
            FUN_004b8730(&someArg, (void *)DAT_01206880, this, gSlotData[i], someArg);
            // Second function: applies or finalizes the slot processing
            FUN_004b86e0(this, gSlotData[i], someArg);
        }
    }
}