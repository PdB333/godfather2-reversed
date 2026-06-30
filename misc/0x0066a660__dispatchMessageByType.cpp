// FUNC_NAME: dispatchMessageByType
void dispatchMessageByType(int* typePtr, int* dataPtr)
{
    int type = *typePtr;
    if (399 < type) {
        handleLargeMessage(dataPtr);      // FUN_0066b250
        *(dataPtr + 2) = 0;               // +8 bytes: status/flag cleared
        return;
    }
    if (0x7e < type) {                    // type > 126
        handleMediumMessage(typePtr, dataPtr); // FUN_006683b0
        *(dataPtr + 2) = 0;
        return;
    }
    // type <= 126 (and implicitly type < 128, but 127 already handled above)
    if ((type * 2 + 1 < 0x200) && (type < 0x80)) { // always true for type < 128
        handleSmallMessage(typePtr, dataPtr); // FUN_00665500
        *(dataPtr + 2) = 0;
        return;
    }
    // fallback for remaining (type 128-399? Actually none left, but safety)
    handleDefaultMessage(typePtr, dataPtr); // FUN_0066c6d0
    *(dataPtr + 2) = 0;
    return;
}