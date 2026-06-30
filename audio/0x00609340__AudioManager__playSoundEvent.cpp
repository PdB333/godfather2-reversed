// FUNC_NAME: AudioManager::playSoundEvent
void __fastcall AudioManager::playSoundEvent(int thisPtr, int param_2, int param_3, int *param_4, int param_5)
{
    int iVar1;
    uint uVar2;
    int *piVar3;
    uint in_EAX;
    undefined4 uVar4;
    undefined1 *puVar5;
    int *unaff_retaddr;
    
    piVar3 = gAudioManager;
    if (((int *)in_EAX != param_4) || (param_2 != param_5)) {
        if (in_EAX == 0) {
            // Stop all sounds or stop specific category
            if (param_3 == 4) {
                // Stop all sounds
                (**(code **)(*gAudioManager + 0x9c))(gAudioManager, 0);
                return;
            }
            if (param_3 != 0) {
                // Stop sounds for specific category
                (**(code **)(*gAudioManager + 0x94))(gAudioManager, param_3, 0);
                return;
            }
            // Play new sound event with generated ID
            iVar1 = *gAudioManager;
            uVar4 = FUN_00609260(); // generateSoundEventID
            (**(code **)(iVar1 + 0x94))(piVar3, 0, uVar4);
            gSoundEventPending = 1;
            return;
        }
        if (in_EAX < 0x1000) {
            puVar5 = &gSoundEventTable + in_EAX * 0x38; // Sound event table, 0x38 bytes per entry
        }
        else {
            puVar5 = (undefined1 *)0x0;
        }
        if ((param_3 != 4) && (uVar2 = *(uint *)(puVar5 + 0x1c), uVar2 != 0)) {
            if (uVar2 < 0x1000) {
                puVar5 = &gSoundEventTable + uVar2 * 0x38;
            }
            else {
                puVar5 = (undefined1 *)0x0;
            }
        }
        param_4 = (int *)0x0;
        if ((*(uint *)(puVar5 + 0xc) & 2) == 0) {
            if ((*(uint *)(puVar5 + 0xc) & 4) == 0) {
                piVar3 = *(int **)(puVar5 + 0x14); // +0x14 sound callback or data
                if (piVar3 == (int *)0x0) {
                    piVar3 = *(int **)(puVar5 + 0x18); // +0x18 alternative sound data
                    if (piVar3 != (int *)0x0) {
                        param_4 = piVar3;
                        (**(code **)(*piVar3 + 4))(piVar3); // Init sound data
                    }
                }
                else {
                    // Play sound with callback
                    (**(code **)(*piVar3 + 0x48))(piVar3, param_2, &param_4); // prepareSoundData
                }
            }
        }
        else {
            // Play sound with positional audio
            (**(code **)(**(int **)(puVar5 + 0x14) + 0x48))
                      (*(int **)(puVar5 + 0x14),(&gPositionalAudioArray)[param_2], 0, &param_4);
        }
        if (param_3 == 4) {
            // Play as 3D sound
            (**(code **)(*gAudioManager + 0x9c))(gAudioManager, param_4);
            piVar3 = gAudioManager;
            if (gSoundEventPending != '\0') {
                iVar1 = *gAudioManager;
                uVar4 = FUN_00609260();
                (**(code **)(iVar1 + 0x94))(piVar3, 0, uVar4);
            }
        }
        else {
            if (param_3 == 0) {
                gSoundEventPending = '\0';
            }
            // Play sound on specified bus/category
            (**(code **)(*gAudioManager + 0x94))(gAudioManager, param_3, param_4);
        }
        if (unaff_retaddr != (int *)0x0) {
            // Release temporary sound data
            (**(code **)(*unaff_retaddr + 8))(unaff_retaddr);
        }
    }
    return;
}