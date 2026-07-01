// FUNC_NAME: DialogManager::handleDialogStep
// Address: 0x0089de40
// Purpose: Handles a dialog playback step – decides whether to start, continue, or stop a dialog based on game state and dialog object validity.

void __thiscall DialogManager::handleDialogStep(DialogManager* this, DialogObject* dialogObj)
{
    bool bCanPlay = true;

    // Check if dialog object is valid and its dialog ID matches the one currently expected by the game manager
    if (dialogObj != nullptr && 
        *(int*)(g_gameManager + 0xc4) != dialogObj->dialogID) // dialogID at offset 0x7bd (bytes) from dialogObj base? Actual offset via int[] indexing would be 0x1f74; we assume a large struct.
    {
        bCanPlay = false;
    }

    // If dialog is not currently playing (this->isPlaying at +0x14)
    if (this->isPlaying == 0) // +0x14
    {
        if (dialogObj != nullptr && bCanPlay)
        {
            int* audioStream = (**(code**)(*dialogObj + 0x1d4))(); // Virtual: getAudioStreamHandle()
            int* someAudioData = g_audioManager; // DAT_0112a878
            if (*(int*)(audioStream + 4) != 0) // Check stream validity
            {
                // Build a local audio state struct (4 dwords) from globals
                undefined4 localState[4];
                localState[0] = *(undefined4*)(g_audioManager + 0x1e4);
                localState[1] = *(undefined4*)(g_audioManager + 0x1e8);
                localState[2] = *(undefined4*)(g_audioManager + 0x1ec);
                localState[3] = *(undefined4*)(g_audioManager + 0x1f0);

                // Check if dialog is currently playing and not paused
                bool isDialogPlaying = FUN_00445250();
                bool isGamePaused = FUN_00420980();
                if (isDialogPlaying && !isGamePaused)
                {
                    // Start the dialog audio playback
                    int soundHandle = FUN_00471610(0x1ff, 0, dialogObj, 0xffffffff, 0); // Sound ID 0x1ff
                    int playResult = FUN_004df330(&dialogObj, localState, soundHandle);
                    FUN_00414db0(playResult); // Set volume or attach to channel
                    FUN_00414df0(); // Start playback
                }

                // Notify derived class that dialog has finished (set flag and call virtual callback)
                *(char*)((int)this + 0x171) = 0; // Clear dialogFinished flag
                ((void (__thiscall *)(DialogManager*, int*, int*))(**(int**)this + 0x1c))(this, dialogObj, audioStream); // Call onDialogFinished virtual
            }
        }
    }
    else // Dialog is already playing (this->isPlaying != 0)
    {
        if (dialogObj == nullptr || !bCanPlay)
        {
            // Stop the current dialog
            FUN_004df600(); // StopPlayback()
            return;
        }

        // Dialog is valid; get its audio stream
        int* audioStream = (**(code**)(*dialogObj + 0x1d4))();
        if (*(int*)(audioStream + 4) != 0)
        {
            // Call the same virtual callback (e.g., onDialogUpdate) with stream info
            ((void (__thiscall *)(DialogManager*, int*, int*))(**(int**)this + 0x1c))(this, dialogObj, audioStream);
        }
    }
}