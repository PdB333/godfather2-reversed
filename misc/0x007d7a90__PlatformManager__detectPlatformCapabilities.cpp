//FUNC_NAME: PlatformManager::detectPlatformCapabilities
uint __fastcall PlatformManager::detectPlatformCapabilities(PlatformManager* this)
{
    uint result;
    void* alloc;
    uint status;

    // Initialize field at +0x74 to 0 (likely a platform capability flag)
    *(uint*)((int)this + 0x74) = 0;

    // Allocate a temporary object of size 0x38 (56 bytes)
    alloc = (void*)FUN_00798f50(0x38);
    status = FUN_0079e920(alloc); // Initialize the allocated object, returns status

    // Check if initialization succeeded (low byte non-zero)
    if ((char)status != 0) {
        // Query some system state (e.g., hardware info)
        void* systemInfo = (void*)FUN_007ab370();
        status = FUN_007d7970(systemInfo); // Get platform capability code (2 or 3)
        *(uint*)((int)this + 0x74) = status; // Store it

        if (status == 3) {
            // Set flag 0x800000 (e.g., "supports high detail")
            result = FUN_007ab420(0x800000);
            return result;
        }
        if (status == 2) {
            // Set flag 0x1000000 (e.g., "supports medium detail")
            result = FUN_007ab420(0x1000000);
            return result;
        }
        // For other status values, fall through to return masked status
    }
    // Mask off low byte and return
    return status & 0xffffff00;
}