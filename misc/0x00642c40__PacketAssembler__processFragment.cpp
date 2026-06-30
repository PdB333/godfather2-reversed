// FUNC_NAME: PacketAssembler::processFragment
void __thiscall PacketAssembler::processFragment(int* this, uint data)
{
    // Get the state object (returned by a helper)
    PacketState* state = (PacketState*)getWriteState();

    uint storedData = state->storedData; // +0x04
    int currentState = state->currentState; // +0x00

    switch (currentState)
    {
    case PS_INITIAL: // 1
        initializeCounter(1); // FUN_00642420(1)
        state->storedData = data;
        state->currentState = PS_FLUSH; // 0xb
        return;

    case PS_WAIT_LOW: // 2
    case PS_WAIT_HIGH: // 3
    {
        uint isLow = (currentState == PS_WAIT_LOW) ? 1 : 0;
        uint selector = 2;
        goto flushBits; // LAB_00642cfd
    }

    case PS_COMBINE: // 4
    {
        // Combine data bits with stored data: (data<<18 | stored)<<6 | 1
        uint combined = ((data << 18) | storedData) << 6 | 1;
        // Write combined value to output stream pointed by this[3] + 8
        flushBitsBlock(combined, *(int*)(this[3] + 8)); // FUN_006438e0
        state->storedData = data;
        state->currentState = PS_FLUSH;
        return;
    }

    case PS_WRITE_BYTE: // 10
    {
        // Write data as top byte into buffer at offset storedData * 4
        // Buffer pointer: *(int*)(*this + 12)
        int* buffer = *(int**)(this[0] + 12);
        buffer[storedData] = (buffer[storedData] & 0x00FFFFFF) | (data << 24);
        state->storedData = data;
        state->currentState = PS_FLUSH;
        return;
    }

    case PS_FLUSH: // 0xb
    {
        if (data != storedData)
        {
            // Data does not match expected, flush with different parameters
            flushPartialBits(0, storedData, 0); // FUN_00643990(0, storedData, 0)
            // Then fall through to common update
        }
        // else fall through
        break;
    }

    default:
        return; // switchD_00642c68_caseD_5: no action
    }

    // Common path for cases 2,3 and successful case 0xb
    state->storedData = data;
    state->currentState = PS_FLUSH;
    return;

flushBits:
    flushPartialBits(selector, isLow, 0); // FUN_00643990
    state->storedData = data;
    state->currentState = PS_FLUSH;
}