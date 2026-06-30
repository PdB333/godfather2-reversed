// FUNC_NAME: updateInputDeviceSlots

// Global variables (declared elsewhere)
extern int* g_devicePtrArray;           // DAT_012233b0 - array of pointers to device objects (offset-based)
extern char* g_deviceStateArray;        // DAT_01163840 - array of device state structures (size 0x210 each)
extern char g_deviceIndices[];          // DAT_011285a4 - array of per-slot device indices (3 bytes per slot)
extern int* g_threadLockArray;          // DAT_011f6be8 - per-thread lock flags
extern int g_currentDeviceHandle;       // DAT_01205378 - currently active device handle
extern void processDeviceCallback(int callbackId); // FUN_0041f080

void updateInputDeviceSlots()
{
    int* tlsBlock = *(int**)(*(int*)(__readfsdword(0x2c)) + 0x2c); // Get TLS block +0x2c offset, deref twice
    uint flag = (*(int*)(tlsBlock + 0x34) != 0); // Some thread-specific flag
    int savedLock = *(int*)(&g_threadLockArray[flag]); // Save old lock value
    int* currentDevice = &g_currentDeviceHandle;      // Will store the incoming EAX

    // Acquire lock (set lock flag to -1)
    g_threadLockArray[flag] = -1;

    // Iterate over 3 device slots (offsets 0x30, 0x34, 0x38 from base)
    char* states = g_deviceStateArray;  // Start of state array
    char* indices = g_deviceIndices;    // Start of index array
    for (int slotOffset = 0x30; slotOffset < 0x3c; slotOffset += 4)
    {
        int* devicePtr = *(int**)((char*)g_devicePtrArray + slotOffset); // Pointer to device object
        char active = 0;

        // Check if device exists and has valid type (1 or 0x12) and state[4] == 3
        if (devicePtr != nullptr)
        {
            int deviceType = *(int*)(devicePtr + 0x20); // Type field at +0x20
            int stateField = *(int*)(states + 4);       // State field at offset 4
            if ((deviceType == 1 || deviceType == 0x12) && stateField == 3)
            {
                active = 1;
            }
        }

        *states = active; // Store active flag at start of state structure

        // If active, call processDeviceCallback for first and third index bytes
        if (active)
        {
            int count = 2; // Two callbacks: index 0 and index 2
            for (int i = 0; i < count; i++)
            {
                processDeviceCallback((int)indices[i]); // Call with byte value
            }
        }

        // Advance to next slot
        indices += 3;
        states += 0x210;
    }

    // Restore lock
    g_threadLockArray[flag] = savedLock;

    return;
}