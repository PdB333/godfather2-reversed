// FUNC_NAME: CombatKnowledge::GetTimeSinceEvent
// Address: 0x0077dbd0
// Role: Lookup an event by ID and return the elapsed time since its recorded timestamp.

extern float g_currentTime;         // DAT_01205228 - global game time
extern float g_defaultNotFoundValue; // DAT_00d5f6f0 - default value when not found

float __thiscall CombatKnowledge::GetTimeSinceEvent(int eventID)
{
    int numEntries = *(int*)((int)this + 0x11c);            // +0x11c: number of entries
    if (numEntries > 0)
    {
        int* entryArray = (int*)((int)this + 0x5c + (numEntries - 1) * 0xc); // +0x5c: start of array, stride 12 bytes
        for (int i = numEntries - 1; i >= 0; i--)
        {
            if (*entryArray == eventID)                     // +0x0: event ID
            {
                return g_currentTime - (float)entryArray[1]; // +0x4: timestamp (int stored as ms or similar)
            }
            entryArray -= 3;                                 // move to previous entry (12 bytes = 3 ints)
        }
    }
    return g_defaultNotFoundValue;
}