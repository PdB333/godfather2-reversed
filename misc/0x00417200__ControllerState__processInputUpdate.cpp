// FUNC_NAME: ControllerState::processInputUpdate
void __thiscall ControllerState::processInputUpdate(int thisPtr, int messageId, uint64_t* messageData)
{
    uint64_t rawValue;
    uint32_t newStateMask;
    uint32_t clearMask;
    uint32_t setValue;

    // Only handle the specific input state update message ID
    if ((messageId == 0x20e5862) && (messageData != (uint64_t*)0x0)) 
    {
        rawValue = *messageData;  // 64-bit packed: low 32 = set bits, high 32 = clear bits
        setValue = (uint32_t)(rawValue & 0xFFFFFFFF);
        clearMask = (uint32_t)(rawValue >> 32);
        
        // Check the 'useCapabilityMask' flag at offset 8 of message data
        // messageData points to uint64_t, so messageData+1 is 8 bytes later
        if (*((int8_t*)(messageData + 1)) == 0) 
        {
            // Apply capability mask to both set and clear masks
            setValue = setValue & *(uint32_t*)(thisPtr + 0x58);   // +0x58 = capabilityMask
            clearMask = clearMask & *(uint32_t*)(thisPtr + 0x58); // +0x58 = capabilityMask
        }

        // Update state: (oldState | setValue) & ~clearMask
        uint32_t oldState = *(uint32_t*)(thisPtr + 0x5c);  // +0x5c = stateMask
        newStateMask = (oldState | setValue) & ~clearMask;
        *(uint32_t*)(thisPtr + 0x5c) = newStateMask;

        // If the state changed and a 'dirty' flag (bit 2) is set, notify low-level handler
        if (((*(uint8_t*)(thisPtr + 0x62) & 4) != 0) && (newStateMask != oldState)) 
        {
            // Pass only the lower 16 bits of the new state
            FUN_004b8480(thisPtr, newStateMask & 0xFFFF);
        }
    }
    return;
}