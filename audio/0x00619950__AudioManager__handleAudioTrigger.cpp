// FUNC_NAME: AudioManager::handleAudioTrigger
void __thiscall handleAudioTrigger(void)
{
    // The function receives a value in EAX (likely a hash/ID) and stores it globally
    // This appears to be part of the audio trigger/hook system in EARS engine
    // Globals:
    // _DAT_01127808 - current/hooked audio parameter (EAX value stored as global)
    // DAT_012058e8 - current audio state manager pointer
    // PTR_PTR_01127760 - base/initial audio state pointer constant
    // DAT_01127774 - current audio state ID
    // DAT_01127878 - stopped/idle audio state ID
    // DAT_01127848 - flag indicating audio is playing
    // DAT_01127884 - paused audio state ID
    // _DAT_01127870 - audio position/parameter data

    // Store the incoming audio parameter (hash or trigger value)
    _DAT_01127808 = in_EAX;
    
    // Check if we're in the default audio state manager
    if (DAT_012058e8 == &PTR_PTR_01127760) {
        // Check current audio state
        if (DAT_01127774 == DAT_01127878) {
            // Audio is stopped/idle
            if (DAT_01127848 != 0) {
                // If audio is still flagged as playing, stop it
                FUN_006063b0(); // StopAudio
            }
        }
        else if (DAT_01127774 == DAT_01127884) {
            // Audio is paused - resume from paused position
            FUN_0060b2f0(DAT_01127774, _DAT_01127870); // ResumeAudio(state, position)
        }
    }
}