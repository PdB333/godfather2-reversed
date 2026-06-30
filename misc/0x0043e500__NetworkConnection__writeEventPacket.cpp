// FUNC_NAME: NetworkConnection::writeEventPacket
uint __thiscall NetworkConnection::writeEventPacket(int thisPtr, int eventId)
{
    int bufferDesc;
    int *puVar3;
    int iVar2;
    char *currentPtr;
    int local_10[3];
    
    // Validate that the connection has a non-empty name/identifier (stored in EAX from caller)
    if ( (in_EAX != (char *)0x0) && (*in_EAX != '\0') )
    {
        bufferDesc = *(int *)(thisPtr + 0x18);           // +0x18: Buffer descriptor
        if (bufferDesc != 0)
        {
            FUN_00625ca0(bufferDesc);                    // Begin buffer operation (maybe lock)
            puVar3 = (int *)FUN_00633cb0(                 // Copy header from current-8 to buffer start
                        bufferDesc, bufferDesc + 0x40,    // +0x40: buffer start address
                        *(int *)(bufferDesc + 8) + -8, 0);
            iVar2 = *(int *)(bufferDesc + 8);            // +0x08: current write pointer
            *(int *)(iVar2 + -8) = puVar3[0];            // Restore header[0]
            *(int *)(iVar2 + -4) = puVar3[1];            // Restore header[1]
            currentPtr = *(char **)(bufferDesc + 8);     // Re-fetch current pointer
            if ( (int *)(currentPtr + -8) != (int *)0x0 &&
                 *(int *)(currentPtr + -8) == 6 )        // Check if previous packet type is 6
            {
                currentPtr[0] = '\x02';                  // Write new packet type 0x02 (event)
                currentPtr[1] = '\0';
                currentPtr[2] = '\0';
                currentPtr[3] = '\0';
                *(int *)(currentPtr + 4) = eventId;      // Write event ID
                *(int *)(bufferDesc + 8) = *(int *)(bufferDesc + 8) + 8; // Advance write pointer by 8 bytes
                local_10[0] = *(int *)(bufferDesc + 8) + -0x10; // Start of this event packet
                local_10[1] = 0;
                // Queue/packet completion:
                currentPtr = (char *)FUN_00636570(&LAB_006261e0, local_10,
                                                  local_10[0] - *(int *)(bufferDesc + 0x1c)); // +0x1c: buffer end limit
                if (currentPtr == (char *)0x0)
                {
                    return 1;  // Success (1)
                }
            }
        }
    }
    return (uint)currentPtr & 0xffffff00;  // Return low byte masked (used for error status)
}