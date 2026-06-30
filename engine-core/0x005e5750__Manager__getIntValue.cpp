// FUNC_NAME: Manager::getIntValue
int __cdecl getIntValueFromManager()
{
    // Global manager instance (likely a singleton)
    void* manager = (void*)DAT_01223514;
    // Local variable for output type/index
    uint8_t type = 0;
    // Buffer pointer
    uint32_t* buffer = (uint32_t*)getManagerBuffer(manager, &type);
    if (buffer != nullptr) {
        // Extract value from buffer
        return extractManagerValue(manager, *buffer);
    }
    return 0;
}