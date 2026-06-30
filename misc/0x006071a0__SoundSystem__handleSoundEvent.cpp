// FUNC_NAME: SoundSystem::handleSoundEvent
// Address: 0x006071a0
// This function processes a sound event: checks the current sound state, invokes the appropriate method on the sound object,
// then releases the event if it's not a stopping event.

// Offsets in SoundEvent structure:
// +0x0c : flags (uint)
// +0x14 : soundIndex (uint, used as index into global sound state/object arrays)
// +0x18 : extraFlags (byte)
// +0x1c : parameter (int, passed to sound object method)

extern char* gSoundStateTable;        // array of SoundState entries, each 0x38 bytes
extern int*  gSoundObjectTable;        // array of SoundObject entries, each 0x38 bytes; first int is object pointer

// Forward declaration of the function that releases/updates the sound event (address 0x00606830)
void releaseSoundEvent(int soundIndex, char* stateEntry);

void SoundSystem::handleSoundEvent(SoundEvent* event)
{
    uint soundIndex = *(uint*)(event + 0x14);       // +0x14 : event's sound ID/index
    if (soundIndex >= 0x1000)
        return;

    char* stateEntry = gSoundStateTable + soundIndex * 0x38;

    // Only process if the state is active (0x04) or if stopping (0x05) when extraFlags allow it
    if (stateEntry != nullptr &&
        (*stateEntry == 0x04 ||
         ((*(byte*)(event + 0x18) & 8) != 0 && *stateEntry == 0x05)))
    {
        // Get the sound object pointer from the object table (first int of the entry)
        int* soundObject = (int*)(gSoundObjectTable + soundIndex * 14); // offset = index * 0xe ints = 0x38 bytes
        int objectPtr = *soundObject;  // object vtable pointer (first field of the object)

        uint flags = *(uint*)(event + 0x0c);   // +0x0c : event flags
        if ((flags & 2) == 0)
        {
            // Non-two-shot: call method at vtable+0x50 with one argument
            if ((flags & 4) == 0)
                (**(code**)(objectPtr + 0x50))(objectPtr, *(int*)(event + 0x1c));
            else
                (**(code**)(objectPtr + 0x50))(objectPtr, 0);
        }
        else
        {
            // Two-shot: call method at vtable+0x50 with two arguments (extra 0)
            (**(code**)(objectPtr + 0x50))(objectPtr, *(int*)(event + 0x1c), 0);
        }

        // If the state is not "stopping" (0x05), release the event
        if (*stateEntry != 0x05)
        {
            int idx = *(int*)(event + 0x14);
            if (idx == -1)
                releaseSoundEvent(-1, stateEntry);
            else
                releaseSoundEvent(idx, stateEntry);
        }
    }
}