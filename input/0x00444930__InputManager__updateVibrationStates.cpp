// FUNC_NAME: InputManager::updateVibrationStates
void __thiscall InputManager::updateVibrationStates(char enable)
{
    // Array of 16 vibration slot structures, each 0x18 bytes, starting at this+0x14
    // VibrationSlot structure:
    //   +0x00: (not used here)
    //   +0x04: int refCount
    //   +0x08: uint flags (bit1 = vibrationPending)
    //   +0x0C to +0x17: unknown

    // Global controller state array at DAT_012233b4 (16 controllers, 0x44 bytes each)
    // Controller structure:
    //   +0x6a: byte isConnected
    //   +0x6b: byte leftMotorSpeed
    //   +0x6c: byte rightMotorSpeed
    //   +0x53d: byte activeControllerSlotIndex
    //   +0x568: byte pendingControllerSlotIndex (or alternative ID)

    int *slotArrayBase = (int *)(this + 0x14);  // Actually address of first slot, but used as pointer to first element
    for (uint slotIndex = 0; slotIndex < 16; slotIndex++)
    {
        int *currentSlot = (int *)(this + 0x14 + slotIndex * 0x18); // Each slot is 0x18 bytes
        if (currentSlot != 0)  // Decompiler artifact; likely checks if first field is non-null, but we keep as-is
        {
            if (enable == 0)
            {
                // Decrement reference count
                int *refCountPtr = (int *)((int)currentSlot + 4);
                *refCountPtr = *refCountPtr - 1;
                if (*refCountPtr == 0)
                {
                    // Clear vibration pending flag
                    *(uint *)((int)currentSlot + 8) &= 0xfffffffd;
                }
            }
            else
            {
                // Increment reference count
                int *refCountPtr = (int *)((int)currentSlot + 4);
                *refCountPtr = *refCountPtr + 1;
                *(uint *)((int)currentSlot + 8) |= 2;

                int *globalControllerBase = (int *)DAT_012233b4;
                byte leftMotor  = *(byte *)(this + 0x195);
                byte rightMotor = *(byte *)(this + 0x196);

                if (FUN_00410af0() != 0) // isGameActive()
                {
                    uint targetSlot = slotIndex & 0xff;
                    // Check if this slotIndex matches the active controller slot
                    if ((char)slotIndex == *(char *)((int)globalControllerBase + 0x53d) &&
                        *(byte *)((int)globalControllerBase + 0x568) != 0x12)
                    {
                        targetSlot = (uint)*(byte *)((int)globalControllerBase + 0x568);
                    }
                    int controllerAddr = (int)globalControllerBase + targetSlot * 0x44;
                    if (*(char *)(controllerAddr + 0x6a) != 0) // controller connected
                    {
                        *(byte *)(controllerAddr + 0x6b) = leftMotor;  // left motor speed
                        *(byte *)(controllerAddr + 0x6c) = rightMotor; // right motor speed
                    }
                }
            }
        }
    }
}