// FUNC_NAME: HandleManager::validateAndCall
// Table of 0x200 entries, each entry is 0x30 bytes.
// Entry structure:
//   +0x2c: full ID (uint) used for validation.
// The table base is DAT_012234bc, with actual entries starting at base+0x10.
// On successful lookup, calls inner routine with the given data parameter.
// Returns the previous EAX value with low byte cleared if validation fails,
// otherwise returns the result of the inner call.

uint HandleManager::validateAndCall(uint id, undefined4 data)
{
    uint prevResult = in_EAX & 0xffffff00;  // capture previous function's return value with low byte cleared
    if ( ((id & 0xffff) < 0x200) )
    {
        // Compute pointer to entry: base + 0x10 + (index * 0x30)
        int entryIndex = id & 0xffff;
        void* entry = (void*)((int)DAT_012234bc + 0x10 + entryIndex * 0x30);
        if (entry != 0)
        {
            // Validate that the ID stored in the entry matches the full ID
            if (*(uint*)((int)entry + 0x2c) == id)
            {
                prevResult = FUN_005e5fe0(data);  // inner function with provided data
            }
            else
            {
                // ID mismatch: entry invalid; return the masked previous result
            }
        }
        else
        {
            // entry pointer null, return masked previous result
        }
    }
    else
    {
        // index out of range, return masked previous result
    }
    return prevResult;
}