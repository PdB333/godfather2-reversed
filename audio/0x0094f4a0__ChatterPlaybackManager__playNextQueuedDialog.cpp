// FUNC_NAME: ChatterPlaybackManager::playNextQueuedDialog
void __fastcall ChatterPlaybackManager::playNextQueuedDialog(int thisPtr)
{
    // Check if queue is empty (+0x1c = remaining count)
    if (*(int *)(thisPtr + 0x1c) == 0) {
        // Queue finished – log or stop (DAT_012069c4 likely a debug string)
        FUN_004086d0(&DAT_012069c4);
        return;
    }

    // Calculate pointer to next queue item (each item is 0x14 bytes)
    int itemPtr = *(int *)(thisPtr + 0x10) + *(int *)(thisPtr + 0x18) * 0x14;

    // Local structure for output string (pointer + vtable/func)
    char *outputStr = nullptr;
    int someFlag = 0;
    int unused = 0;
    void (*releaseFunc)(void *) = nullptr;

    // Process the queue item (likely start sound/animation)
    FUN_004d3e20(itemPtr);

    // Read float at offset 0x10 of the item (might be duration or text ID)
    float durationOrTextId = *(float *)(itemPtr + 0x10);

    // Advance queue index, wrap around if necessary
    int newIndex = *(int *)(thisPtr + 0x18) + 1;
    if (*(int *)(thisPtr + 0x14) <= newIndex) {
        newIndex = 0;
    }
    *(int *)(thisPtr + 0x18) = newIndex;

    // Decrease remaining count
    *(int *)(thisPtr + 0x1c) = *(int *)(thisPtr + 0x1c) - 1;

    // If flag is 0 (always true here), convert the float to a subtitle/label string
    if (someFlag == 0) {
        FUN_00604000((int)durationOrTextId, &outputStr, 1);
    }

    // Use a default string if conversion failed
    char *displayStr = outputStr;
    if (outputStr == nullptr) {
        displayStr = (char *)&DAT_0120546e;
    }

    // Display the string (likely subtitle text or debug overlay)
    FUN_00939fd0(displayStr);

    // Release dynamically allocated string if present
    if (outputStr != nullptr) {
        releaseFunc(outputStr);
    }
}