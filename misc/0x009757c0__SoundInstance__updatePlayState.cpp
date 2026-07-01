// FUNC_NAME: SoundInstance::updatePlayState
// Reconstructed from 0x009757c0
// Likely part of EARS::Modules::AudioEvent or similar sound instance class
// Class offsets: this+0x80: byte flag - probably m_bPendingPlay
//                this+0x81: byte flag - probably m_bPlaying
//                this+0x82: byte flag - probably m_bPaused or m_bQueued
// Global g_soundManager = DAT_01129828  (singleton)
// Global g_gameSettings = DAT_0112fe08  (game config, offset 0x48,0x49 bit flags)

int __thiscall SoundInstance::updatePlayState(SoundInstance* this, bool bRequested)
{
    int* pSoundManager = DAT_01129828;  // pointer to sound manager singleton

    if (bRequested)
    {
        this->m_bPlaying = 1;  // +0x81

        if (this->m_bPaused == 0)  // +0x82
        {
            // Check if playback is allowed: m_bPendingPlay set, sound manager says ok, and bit 7 of some flag is clear
            if ((this->m_bPendingPlay != 0) &&                                        // +0x80
                ((*(code **)(*pSoundManager + 0x24))() != 0) &&                       // vtable 0x24: isSoundEnabled()
                ((~((uint)pSoundManager[4] >> 7) & 1) != 0))                         // bit test on some control flag
            {
                this->m_bPlaying = 0;  // stop playing
                FUN_00911b00();        // probably stop current sound

                pSoundManager = DAT_01129828;
                if (DAT_01129828[0xb] != 0)  // check if sound bank is loaded
                {
                    FUN_008f1e70(0x20);      // play sound group/bank with ID 0x20
                }

                // Post the sound event with a static label and no parameters
                (*(void (__thiscall **)(int, char*))(*(int*)pSoundManager + 0x18))(pSoundManager, &LAB_009752f0, 0);
            }
        }
        else
        {
            this->m_bPaused = 0;  // clear pause flag
        }
    }

    // Return 1 if still playing and global settings allow; else 0
    if ((this->m_bPlaying == 0) || (*(char*)(DAT_0112fe08 + 0x48) != 0) ||
        ((*(char*)(DAT_0112fe08 + 0x49) & 0x0A) != 0))
    {
        return 0;
    }
    return 1;
}