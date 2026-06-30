// Function: 0x0040fb40
// Role: Applies input masks to 4 controller slots, each with 4 channels.
//       Updates current and previous values to stay within allowed mask.
//       Similar to deadzone or input clamping logic in EA EARS input system.

void __thiscall InputStateManager::ApplyInputMasks(void)
{
    // Slot array starts at offset +0x40 from this
    ushort* slotBase = reinterpret_cast<ushort*>(this + 0x40);

    // Process 4 controller slots (0x110 bytes per slot = 0x88 ushorts)
    for (int slot = 0; slot < 4; ++slot)
    {
        // Process 4 channels per slot (0x22 ushorts per channel)
        for (int ch = 0; ch < 4; ++ch)
        {
            ushort* channel = slotBase + (ch * 0x22);

            // Active flag is stored as low byte of ushort at index +0x15
            if ( ((char)channel[0x15] != 0) && (channel[0] != 0) )
            {
                ushort current = channel[0];      // current value
                ushort mask    = channel[-2];     // allowed mask
                ushort prev    = channel[-1];     // previous value
                ushort masked  = mask & current;

                if (masked != current)
                {
                    // Remove bits not in mask from current, update history
                    prev = prev & (ushort)~((~masked) & current);
                    channel[-1] = prev;
                    channel[0]  = masked;
                }
            }
        }

        // Advance to next slot (0x88 ushorts = 0x110 bytes)
        slotBase += 0x88;
    }
}