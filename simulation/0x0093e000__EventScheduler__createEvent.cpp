// FUNC_NAME: EventScheduler::createEvent
// Function at 0x0093e000 initializes a timed event structure
// This appears to be a constructor or initializer for an event object used by EventScheduler.
// Parameters:
//   this - pointer to event struct (0x20+ bytes)
//   eventFlags - word flags (stored at +4 eventually, but overwritten? see note)
//   callbackId - some identifier for the callback/handler
//   userDataOffset - offset relative to a global base (DAT_01205224) if non-zero
//   timeoutMs - time in milliseconds (defaults to 5000 if zero)
//   context - additional context data (probably a pointer or handle)
// Note: The decompiled code shows an apparent overwrite of the word at +4, but this is likely due to
// Ghidra's pointer casting; actual struct layout may have a dword at offset 4 that stores the flags in its low word.

void __thiscall EventScheduler::createEvent(EventScheduler::Event *this,
                                            uint16_t eventFlags,
                                            uint32_t callbackId,
                                            int userDataOffset,
                                            int timeoutMs,
                                            uint32_t context)
{
    // These initial writes are typical for a constructor; the order is preserved from decompiled output.
    *(uint16_t *)((int)this + 4) = eventFlags;  // Set flags word at offset +4
    this->field_0 = 0;                          // Clear first dword (offset 0)
    this->field_4 = 0;                          // Clear dword at offset 4 (overwrites flags word, likely a decompilation artifact)
    this->field_8 = 0;                          // Clear dword at offset 8
    *(uint16_t *)((int)this + 0x12) = 0;        // Clear word at offset 0x12

    // Default timeout to 5 seconds if not specified
    if (timeoutMs == 0) {
        timeoutMs = 5000;
    }

    // Store timeout as a short (likely milliseconds)
    *(int16_t *)((int)this + 0x14) = (int16_t)timeoutMs;  // offset +0x14

    // Store context (e.g., repeat count, data pointer)
    this->field_6 = context;   // offset 0x18 (param_1[6])

    // Store callback identifier
    this->field_8 = callbackId; // offset 0x20 (param_1[8])

    // Clear another field
    this->field_7 = 0;          // offset 0x1C (param_1[7])

    // If user provides an offset, add it to a global base pointer (DAT_01205224 is a static address)
    // This is likely used to access some manager or global state.
    if (userDataOffset != 0) {
        this->field_3 = (void*)((int)userDataOffset + (int)DAT_01205224);  // offset 0x0C
    } else {
        this->field_3 = 0;
    }
}