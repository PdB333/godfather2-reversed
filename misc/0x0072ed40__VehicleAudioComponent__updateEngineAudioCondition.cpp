// FUNC_NAME: VehicleAudioComponent::updateEngineAudioCondition
void __thiscall VehicleAudioComponent::updateEngineAudioCondition(int this_ptr)
{
    int *bankMgr;
    int newSoundHandle;
    // local variables for a temporary sound structure
    int *soundListEntry = 0;
    int soundListNext = 0;
    // This looks like a temporary Sound/Stream object initialized on the stack
    void **vtablePtr = (void**)&PTR_FUN_00d5dbbc; // vtable pointer for sound object
    int soundHash = 0x564418d6; // engine sound event hash (e.g., "engine_loop")
    int someGlobalValue = DAT_01205228; // maybe a global volume or pitch
    int refCount = 0;
    int field_4 = 0;
    int field_8 = 0;
    char padding = 0;
    // End of temporary sound structure

    // Check if engine sound should be active (e.g., engine is on or revving)
    if (*(int *)(this_ptr + 0x1e70) != 0 || *(int *)(this_ptr + 0x1e84) != 0)
    {
        // Get the audio bank manager singleton
        bankMgr = (int *)FUN_0043b870(DAT_01131018); // AudioBankManager::getInstance()

        // Initialize the temporary sound object fields
        soundListEntry = (int *)&vtablePtr; // pointer to the vtable pointer
        // Build the sound structure manually (hash, global data, etc.)
        // The following assignments set up the sound event request
        // local_10 = 0; local_14 = 0; local_18 = 0; etc. are already zeroed
        // The actual sound request is built using the vtable, hash, and global values

        // Call a virtual function on the bank manager (likely createSoundRequest or getSound)
        int result = (**(code **)(*bankMgr + 0x34))(); // BankManager::createSoundRequest()

        // Compare sound handle pointers (ref counting/list manipulation)
        if ((&refCount != (int *)(result + 0xc)) && (result = *(int *)(result + 0xc), refCount != result))
        {
            // Release old sound handle if present
            if (refCount != 0)
            {
                FUN_004daf90(&refCount); // SoundHandle::release()
            }
            // Adopt the new sound handle
            refCount = result;
            if (result != 0)
            {
                field_4 = *(int *)(result + 4);
                *(int **)(result + 4) = &refCount; // intrusive linked list or reference
            }
        }

        // Now call a function to play/update the sound on the vehicle's audio channel (this+0x3c)
        FUN_00408bf0(&vtablePtr, this_ptr + 0x3c, 0); // likely SoundManager::playOnChannel with the temporary sound object

        // Release the temporary sound handle if still held
        if (refCount != 0)
        {
            FUN_004daf90(&refCount);
        }
    }
    return;
}