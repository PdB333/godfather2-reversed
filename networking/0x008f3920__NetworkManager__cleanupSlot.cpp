// FUNC_NAME: NetworkManager::cleanupSlot
void NetworkManager::cleanupSlot(int slotIndex, int resourceHandle, char bSkipFinalization)
{
    // If a resource handle is provided, release it
    if (resourceHandle != 0) {
        releaseResource();           // FUN_009823b0
        deleteResource(resourceHandle); // FUN_009c8eb0
    }

    // If finalization is not skipped, do final cleanup and call virtual method
    if (bSkipFinalization == '\0') {
        stopProcessing(0);           // FUN_0068c590

        // Get the global manager's vtable pointer (stored at g_pManager + 0x2098)
        // Call the 4th virtual function (vtable+0x10) with (slotIndex+1)
        void (*vtableFunc)(int) = (** (int (**)[2]) (*(int**)(g_pManager + 0x2098) + 0x10));
        vtableFunc(slotIndex + 1);
    }
}