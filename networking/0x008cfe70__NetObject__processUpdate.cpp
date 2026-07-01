// FUNC_NAME: NetObject::processUpdate
uint __thiscall NetObject::processUpdate(int* thisPtr, undefined4* outStatus)
{
    char cVar1;
    int* dataPtr;
    undefined4 uVar3;
    int iVar4;
    uint result;

    // Initialize output status to 0 if provided
    if (outStatus != (undefined4*)0x0) {
        *outStatus = 0;
    }

    // Clear bit 30 (0x40000000) of flags at offset 0x60
    thisPtr[0x18] = thisPtr[0x18] & 0xbfffffff;

    result = 8; // Default status: no update needed

    // Determine data pointer based on flag bit 31
    if (thisPtr[0x18] < 0) {
        // Bit 31 set: use internal buffer at offset 0x20
        dataPtr = thisPtr + 8;
    } else {
        // Bit 31 clear: call virtual function at vtable offset 0x24 to get data pointer
        dataPtr = (int*)(**(code**)(*thisPtr + 0x24))();
    }

    // Check if data pointer is valid and contains non-zero data (16 bytes)
    if ((dataPtr != (int*)0x0) &&
        ((((*dataPtr != 0 || (dataPtr[1] != 0)) || (dataPtr[2] != 0)) || (dataPtr[3] != 0)))) {
        // Get size of the data
        if (thisPtr[0x18] < 0) {
            // Bit 31 set: call virtual function at vtable offset 0x28 to get size handle
            uVar3 = (**(code**)(*thisPtr + 0x28))();
            iVar4 = FUN_008e9cb0(uVar3); // Convert handle to size
        } else {
            // Bit 31 clear: get size directly from data pointer
            iVar4 = FUN_008eadd0(dataPtr);
        }

        if (iVar4 == 0) {
            // Size is zero: clear the data buffer
            FUN_004461c0(dataPtr, 0);
        } else {
            // Size non-zero: attempt to apply update
            result = 4;
            iVar4 = FUN_004461c0(thisPtr + 8, 0); // Clear internal buffer
            if (iVar4 != 0) {
                // Allocate buffer for update
                uVar3 = FUN_008e9ae0(iVar4);
                cVar1 = FUN_008f0bb0(dataPtr, uVar3, thisPtr, 0); // Apply update
                if (cVar1 != '\0') {
                    result = 2; // Update applied successfully
                }
            }
        }
    }

    // If update was not applied and bit 29 is clear, call cleanup function
    if (((result & 2) == 0) && (((uint)thisPtr[0x18] >> 0x1d & 1) == 0)) {
        FUN_004088c0(thisPtr + 0xf); // Offset 0x3c
    }

    return result;
}