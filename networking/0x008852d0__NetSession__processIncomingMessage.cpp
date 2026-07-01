// FUNC_NAME: NetSession::processIncomingMessage
void __fastcall NetSession::processIncomingMessage(int thisObj)
{
    char isValid;
    int result;
    int* vtablePtr;
    undefined4** packetInfo;
    undefined4 packetType;
    undefined4 localBuffer[4]; // used for some packet data

    localBuffer[0] = 0;
    localBuffer[1] = 0;
    localBuffer[2] = 0;
    localBuffer[3] = 0;

    // Get vtable pointer from subobject at +0x50 (likely a PacketSink/EventHandler)
    if (*(int*)(thisObj + 0x50) == 0) {
        vtablePtr = (int*)0x0;
    }
    else {
        // Adjust by -0x48 to get the vtable of the parent object (multiple inheritance)
        vtablePtr = (int*)(*(int*)(thisObj + 0x50) - 0x48);
    }

    packetInfo = (undefined4**)&localBuffer[2]; // will point to &localBuffer[2] (local_8)
    packetType = *(undefined4*)(thisObj + 0x58); // incoming packet/event type

    // Static type information (likely a debug string or class descriptor)
    undefined4* staticTypeInfo = (undefined4*)0x885316; // some static data

    // Virtual call on subobject: probably "beginPacket" or "startProcessing"
    (**(code**)(*vtablePtr + 0x1f8))(); // vtable index 126

    // Check if we have a valid packet by calling into the subobject
    vtablePtr = ...; // re-fetched after potential changes
    packetInfo = &localBuffer; // was previously set to &localBuffer, now reassign
    (**(code**)(*vtablePtr + 0x1d8))(&localBuffer[0]); // vtable index 118, pass buffer

    isValid = FUN_00543270(&packetInfo); // checks if the packet is valid/complete
    if (isValid != '\0') {
        // If valid, dispatch to handler (e.g., deliver packet)
        if (*(int*)(thisObj + 0x50) != 0) {
            // But we already know not null? Actually check again
            FUN_005430c0(*(undefined4*)(thisObj + 0x58), &packetInfo); // handle packet
            return;
        }
        FUN_005430c0(*(undefined4*)(thisObj + 0x58), &packetInfo);
        return;
    }

    // If packet not valid, check a flag at +0x70 (bit 0)
    if ((*(byte*)(thisObj + 0x70) & 1) != 0) {
        // Virtual call: probably "getErrorCode" or "getStatus"
        result = (**(code**)(*vtablePtr + 500))(&packetInfo); // vtable index 125
        FUN_00543160(*(undefined4*)(thisObj + 0x58), result); // handle error

        if ((result != 0) && (FUN_00625050(0x55662773, 0) != 0)) {
            // May trigger some debug/error handling
            FUN_007773e0(); // likely a log or assert
        }
    }
    return;
}