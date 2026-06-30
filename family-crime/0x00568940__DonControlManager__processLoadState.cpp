// FUNC_NAME: DonControlManager::processLoadState
void DonControlManager::processLoadState(void)
{
    int loadState = *(int *)(this + 0xC); // +0x0C: current load state (1=loading, 2=loaded, 3=error, 4=done)

    // Only proceed if not already in a completed state
    if (loadState != 2 && loadState != 3 && loadState != 4)
    {
        // Transition to loading state
        *(int *)(this + 0xC) = 1;

        // Check global flag: has save data been loaded?
        if (g_bSaveDataLoaded != 0) // DAT_012234b8
        {
            // Check if save data is actually available
            if (isLoadDataAvailable()) // FUN_00566920
            {
                // Get the save manager singleton
                SaveManager* pSaveMgr = getSaveManager(); // FUN_00ad8d40
                if (pSaveMgr != nullptr)
                {
                    // Get the active profile container (virtual call at vtable+0x04)
                    Profile* pProfile = (Profile*)(*(int (__thiscall**)(SaveManager*))(*(int*)pSaveMgr + 4))(pSaveMgr);
                    if (pProfile != nullptr)
                    {
                        // Set state to "loaded"
                        *(int *)(this + 0xC) = 2;

                        // Prepare a buffer for the profile data
                        char buffer[256]; // auStack_108
                        memset(buffer, 0, sizeof(buffer)); // FUN_00ae9750

                        // Retrieve the profile data as a string (virtual call at vtable+0x34)
                        char profileData[64]; // auStack_148
                        (*(void (__thiscall**)(Profile*, char*))(*(int*)pProfile + 0x34))(pProfile, profileData);

                        // Get the profile name
                        char* pName = (char*)pProfile; // puVar4 (virtual call at vtable+0x00, returns this or a string)
                        pName = (*(char* (__thiscall**)(Profile*))(*(int*)pProfile))(pProfile);

                        // Process the loaded profile
                        processLoadedProfile(pName); // FUN_00568c00

                        // Cleanup profile data buffer
                        cleanupProfileBuffer(); // FUN_00ae97f0
                    }
                }
            }
        }
    }
}