// FUNC_NAME: AnimationEventPlayer::processEvent
// Address: 0x00894410
// Processes an animation event (bone transform or sound trigger).
// param_3: event data (hash, flag, value)
// param_4: context data (flags)
void __thiscall AnimationEventPlayer::processEvent(void* this,
                                                      int unusedParam2,
                                                      AnimEventData* eventData,
                                                      AnimContext* context)
{
    uint hashID;
    char success;
    float currentValue;
    float targetValue;
    int* objectPtr;
    uint flags;
    byte contextFlags;
    ulonglong roundedValue;

    roundedValue = 0; // Initialize lower 32 bits

    // Attempt to read or validate the event value (function 0x00893e70 likely reads a field)
    success = FUN_00893e70(&roundedValue,
                            *(undefined4*)(eventData + 1), // offset +4: maybe a field index or parameter
                            context,
                            1,
                            1,
                            0);
    if (success == 0) {
        return;
    }

    // Convert the value and check if it matches the stored value (0x00851500 likely conversion)
    targetValue = (float)FUN_00851500((float)roundedValue,
                                       *(undefined4*)(eventData + 2)); // offset +8: target value
    currentValue = (float)roundedValue;
    if (currentValue == targetValue) {
        return;
    }

    // Extract flags from event and context
    flags = (eventData->flags & 3); // +3: flags byte, low 2 bits
    contextFlags = *(byte*)(context + 0x10) & 5; // bit0 and bit2

    if (contextFlags != 0) {
        flags |= 0x80000000; // Set high bit to indicate context active
    }

    hashID = eventData->hash; // +4: hash identifier

    // Handle known hash IDs that are ignored or have special handling
    if (hashID < 0x61d5bbab) {
        if (hashID == 0x61d5bbaa) return; // Ignored
        if (hashID == 0x1722f6a0) return; // Ignored
        if (hashID == 0x471e201b) return; // Ignored
        if (hashID == 0x4ea8b900) return; // Ignored
    } else {
        if (hashID == 0xe7ad7581) return; // Ignored
        if (hashID == 0xe83af06c) {
            // Special case: set a float value on an object
            if (*(int*)(this + 0x38) == 0) return; // Null pointer check
            if (*(int*)(this + 0x38) == 0x48) return; // Another state check (maybe a sentinel)
            objectPtr = (int*)(*(int*)(this + 0x38) - 0x48); // Adjust pointer
            roundedValue = (ulonglong)ROUND(targetValue); // Round to integer
            (*(void(__thiscall**)(float))(*(int*)objectPtr + 0x1dc))((float)roundedValue); // Vtable call (likely setTime/play)
            return;
        }
    }

    // General case: if context flags indicate playing/active and hash matches,
    // dispatch to another handler
    if (((*(byte*)(context + 0x10) & 1) != 0 || contextFlags != 0) &&
        (int specificHandler = FUN_00893470(hashID), specificHandler != 0)) {
        FUN_00894d00(specificHandler,
                     (float)targetValue,
                     flags,
                     0);
    }
    return;
}