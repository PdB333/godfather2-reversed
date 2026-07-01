// FUNC_NAME: ControllerManager::packControllerState
void ControllerManager::packControllerState(byte* outBuffer)
{
    // Global pointer to the current controller state (likely for player 1)
    // DAT_01129938 -> g_controllerState (assumed to be a pointer to a ControllerState struct)
    ControllerState* state = (ControllerState*)DAT_01129938;

    // Extract button bits from the bitfield at offset +0x14
    // Bits: 0 = buttonA, 1 = buttonB, 2 = buttonX, 3 = buttonY, 4 = leftBumper, 5 = rightBumper? (adjust as needed)
    uint buttonFlags = *(uint*)((byte*)state + 0x14);

    outBuffer[0] = (byte)((buttonFlags >> 1) & 1);  // Button B
    outBuffer[1] = (byte)((buttonFlags >> 2) & 1);  // Button X
    outBuffer[2] = (byte)((buttonFlags >> 3) & 1);  // Button Y
    outBuffer[3] = (byte)((buttonFlags >> 4) & 1);  // Left bumper
    outBuffer[4] = (byte)((buttonFlags >> 5) & 1);  // Right bumper

    // Analog stick values (likely left stick X, left stick Y, right stick X, right stick Y, triggers)
    *(uint*)(outBuffer + 8)  = *(uint*)((byte*)state + 0x20);  // Left stick X
    *(uint*)(outBuffer + 0xc)= *(uint*)((byte*)state + 0x24);  // Left stick Y
    outBuffer[0x10] = (byte)(buttonFlags & 1);                 // Button A (bit 0)
    *(uint*)(outBuffer + 0x14)= *(uint*)((byte*)state + 0x18); // Right stick X
    *(uint*)(outBuffer + 0x18)= *(uint*)((byte*)state + 0x1c); // Right stick Y
    *(uint*)(outBuffer + 0x1c)= *(uint*)((byte*)state + 0x2c); // Left/right trigger combined? (or other)
}