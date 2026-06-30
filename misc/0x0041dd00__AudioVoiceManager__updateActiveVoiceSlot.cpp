// FUNC_NAME: AudioVoiceManager::updateActiveVoiceSlot
unsigned int AudioVoiceManager::updateActiveVoiceSlot(void)
{
    unsigned char state;
    unsigned int resourceIndex;
    unsigned int *puVar2;
    int iVar4;
    unsigned char localBuffer[68]; // size from local_50 [68]
    unsigned int *pDest; // local_c originally uninitialized, but used in pointer arithmetic

    // Check if current time is less than time limit (DAT_01206a7c)
    if (currentTime < MAX_UPDATE_TIME) {
        // Get current resource handle from the 3-slot array (DAT_01206b08)
        resourceIndex = resourceHandles[currentSlotIndex];

        // Validate resource index: must be < 0x1000, and the resource pointer must be non-null
        if ((resourceIndex < 0x1000) && 
            (resourcePtrBase + resourceIndex * RESOURCE_STRIDE != (unsigned char *)0x0) &&
            ((state = (resourcePtrBase + resourceIndex * RESOURCE_STRIDE)->firstByte, state > 1) && 
             (state != 5 && state != 4))) 
        {
            // Set resource state to 2 (e.g., "Ready" or "Processing")
            FUN_006064b0(resourceIndex, 2);
        }

        // Copy data for the resource into local buffer (size 68 bytes)
        // FUN_00606fd0 likely reads resource data
        FUN_00606fd0(resourceHandles[currentSlotIndex], 2, 0, localBuffer);

        // Copy 0x80 dwords from global data (DAT_01162388) to local buffer? 
        // Actually original decompiler shows weird pointer arithmetic.
        // Likely copies from &DAT_01162388 to localBuffer, but buffer too small.
        // Assuming memcpy(localBuffer, &DAT_01162388, 0x200) is intended.
        iVar4 = 0x80;
        pDest = (unsigned int *)localBuffer; // overwrite local_c usage
        do {
            iVar4--;
            *pDest = *(unsigned int *)((DAT_01162388_addr - (int)pDest) + (int)pDest);
            pDest++;
        } while (iVar4 != 0);

        // Start playback or process the data
        FUN_006071a0(localBuffer);

        // Store the processed handle for external use
        lastProcessedHandle = resourceHandles[currentSlotIndex];

        // Rotate to next slot (0,1,2) modulo 3
        currentSlotIndex = (currentSlotIndex + 1) % 3;

        // Return the resource index divided by 3 (likely an internal ID mapping)
        return resourceIndex / 3;
    }
    else {
        // Fallback: use default handle
        lastProcessedHandle = DEFAULT_HANDLE;
        // Return value from caller's EAX (uninitialized in decompiler) – 
        // this is likely the return from a previous call, but we return current EAX? 
        // In practice, this function returns a default value.
        return currentEAX; // placeholder – actual behavior undefined
    }
}