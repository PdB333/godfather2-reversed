// FUNC_NAME: AudioManager::playRandomAmbientSound
void AudioManager::playRandomAmbientSound(uint soundSetIndex, float param_2)
{
    uint uVar1;
    uint soundId;
    int local_8;
    
    uVar1 = DAT_010c2678 & DAT_012054b4;
    DAT_012054b4 = DAT_012054b4 + 1;
    soundId = 0;
    local_8 = (int)(longlong)ROUND(*(float *)(&DAT_010c2680 + uVar1 * 4) * DAT_00e445ac);
    if ((param_2 < _DAT_00d577a0) || (DAT_00d5ef88 <= param_2)) {
        if ((param_2 < DAT_00d5ef88) || (DAT_00d5ef6c < param_2)) {
            if (local_8 == 0) {
                soundId = 0x9372c79e;
            }
            else {
                if (local_8 == 1) {
                    FUN_00603330(0x9372c79f, soundSetIndex);
                    return;
                }
                if (local_8 == 2) {
                    FUN_00603330(0x9372c7a0, soundSetIndex);
                    return;
                }
            }
        }
        else {
            if (local_8 == 0) {
                FUN_00603330(0xac5c04c1, soundSetIndex);
                return;
            }
            if (local_8 == 1) {
                FUN_00603330(0xac5c04c2, soundSetIndex);
                return;
            }
            if (local_8 == 2) {
                FUN_00603330(0xac5c04c3, soundSetIndex);
                return;
            }
        }
    }
    else {
        if (local_8 == 0) {
            FUN_00603330(0x828823c0, soundSetIndex);
            return;
        }
        if (local_8 == 1) {
            FUN_00603330(0x828823c1, soundSetIndex);
            return;
        }
        if (local_8 == 2) {
            FUN_00603330(0x828823c2, soundSetIndex);
            return;
        }
    }
    FUN_00603330(soundId, soundSetIndex);
    return;
}