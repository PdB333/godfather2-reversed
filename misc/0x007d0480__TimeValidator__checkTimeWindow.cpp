// FUNC_NAME: TimeValidator::checkTimeWindow
// Address: 0x007d0480
// This method checks if a given timestamp falls within a valid time window.
// It uses two stored timestamps at +0xA4 and +0xA8, and a pointer to an external object at +0x58.
// Returns a 32-bit value: low bit = 1 if within window, upper 24 bits = time delta from the second timestamp.
// The time window is validated if the delta between the two stored timestamps is small enough,
// and the input timestamp is also close to the second stored timestamp.

uint32 __thiscall TimeValidator::checkTimeWindow(uint32 currentTime)
{
    // 'this' pointer (ecx) -> object with fields at offsets:
    //  +0x58: pointer to another object (e.g., a game state manager)
    //  +0xA4: first stored timestamp (start of window)
    //  +0xA8: second stored timestamp (end of window)
    uint32* object = this;
    uint32* stateObject = *(uint32**)((uint8*)object + 0x58);  // +0x58
    uint32 startTime = *(uint32*)((uint8*)object + 0xA4);      // +0xA4
    uint32 endTime   = *(uint32*)((uint8*)object + 0xA8);      // +0xA8

    // Check if the state object's flag (bit0 at +0x8E8) is clear (0 = enabled?)
    if ((*(uint8*)((uint8*)stateObject + 0x8E8) & 1) == 0 &&
        startTime != 0 && endTime != 0)
    {
        // Compute difference between the two stored timestamps
        int32 diff = endTime - startTime;
        float fDiff = (float)diff;
        if (diff < 0) {
            fDiff += 4294967296.0f;  // DAT_00e44578: wrap around for unsigned subtraction
        }

        // Check if the window duration is below a threshold (converted using multiplier)
        if (fDiff * 0.001f < 5.0f) // Example: DAT_00d5efb8 = 0.001 (ms?), _DAT_00e52fd0 = 5.0
        {
            uint32 timeDelta = currentTime - endTime;
            float fDelta = (float)(int32)timeDelta;
            if ((int32)timeDelta < 0) {
                fDelta += 4294967296.0f;
            }

            // Check if current time is also within threshold of endTime
            if (fDelta * 0.001f < 5.0f)
            {
                // Success: return the time delta (shifted) with low bit set
                return (timeDelta & 0xFFFFFF00) | 0x01;
            }
        }
    }

    // Failure: return startTime (or 0) with low byte cleared
    return startTime & 0xFFFFFF00;
}