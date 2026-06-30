// FUNC_NAME: ControllerSlot::updateButtonState
// Function address: 0x00496aa0
// Role: Updates button state for a controller slot based on raw input data from a device.
// Called from FUN_00496010 (likely input manager update loop).
// Parameters:
//   - device: Pointer to a controller device object (e.g., XInput device) with vtable at offset +4.
//   - slotIndex: Index of the controller slot (0-15).
//   - buttonId: Identifier of the button/axis being processed.
// Registers: EDI (unaff_EDI) points to a global or context structure with button state bitfield at +0x10 and per-slot button states at +0x16+slotIndex.

void ControllerSlot::updateButtonState(void* device, int slotIndex, uint buttonId)
{
    // Extract 8-byte value from device's virtual function (likely device->getRawState(buttonId))
    // vtable offset: device[0x4][0x0C] (device->vtable->func3)
    unsigned long long raw8Bytes = ((unsigned long long (*)(uint))(**(int**)(*(int*)device + 4) + 0x0C))(buttonId);

    uint resultFlag = 0;

    // Unpack the 8-byte value into bytes
    char byte0 = (char)raw8Bytes;
    unsigned short bytes1_2 = (unsigned short)(raw8Bytes >> 8);
    unsigned char byte3 = (unsigned char)(raw8Bytes >> 24);
    unsigned char byte4 = (unsigned char)(raw8Bytes >> 32);
    unsigned char byte5 = (unsigned char)(raw8Bytes >> 40);
    unsigned short bytes6_7 = (unsigned short)(raw8Bytes >> 48);

    // Process first two bytes (indices 0 and 1 of the byte array)
    int i = 0;
    do {
        if (resultFlag != 0) break;
        unsigned char currentByte = *((unsigned char*)&bytes1_2 + i); // Access bytes1_2 as array
        if (currentByte != 0xFF && currentByte != 0xFE) {
            if (currentByte < 3) {
                // Direct button/axis mapping
                resultFlag = FUN_00b93170(currentByte);
                resultFlag = resultFlag & 0xFF; // Mask to byte
            } else {
                // Extended button/axis mapping (combine byte3 and byte4)
                resultFlag = FUN_00496a00( (unsigned short)( (byte4 << 8) | byte3 ) );
            }
            if ((resultFlag != 0) && (byte0 == 0x03)) { // 0x03 likely means "pressed" or "active"
                // Additional check: call FUN_00496c40 with context
                int param1 = (int)( (bytes6_7 << 16) | (byte5 << 8) | 2 ); // Reconstruct parameter
                char checkResult = FUN_00496c40(/* return address placeholder? */ 0, device, 0, /* EDI context */ globalState);
                if (checkResult == '\0') {
                    resultFlag = 0; // Clear result if check fails
                }
            }
        }
        i++;
    } while (i < 2);

    // Update slot's button state bitfield (at offset +0x10) and per-slot byte array (at +0x16+slotIndex)
    unsigned short bitMask = (unsigned short)(1 << (slotIndex & 0x1F));
    if (resultFlag != 0) {
        // Set bit and mark button as pressed (0xFF)
        *(unsigned short*)(globalState + 0x10) |= bitMask;
        *(unsigned char*)(slotIndex + 0x16 + globalState) = 0xFF;
    } else {
        // Clear bit and mark button as released (0x00)
        *(unsigned short*)(globalState + 0x10) &= ~bitMask;
        *(unsigned char*)(slotIndex + 0x16 + globalState) = 0x00;
    }
    return;
}