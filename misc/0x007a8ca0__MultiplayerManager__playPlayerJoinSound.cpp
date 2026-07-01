// FUNC_NAME: MultiplayerManager::playPlayerJoinSound
void __fastcall MultiplayerManager::playPlayerJoinSound(int thisPtr)
{
    char isActive;
    int soundObj;
    int *localPtr;
    undefined4 uVar4;
    undefined *teamText;
    undefined1 *local_74; // buffer for sound data
    int local_90;
    int callbackArray[3];
    code *callbackFunc;
    int local_7c;
    undefined1 local_78[4]; // some struct
    undefined1 local_74_buf[116];

    isActive = FUN_0089c630(); // likely isGameActive() or isMultiplayer()
    local_7c = DAT_011298a0; // some singleton manager

    // Check conditions: game active, a flag at this+0x2b4 false, audio enabled (DAT_011298a0+0x88), etc.
    if (((((isActive == '\0') && (*(int *)(thisPtr + 0x2b4) == 0)) &&
         (*(char *)(DAT_011298a0 + 0x88) != '\0')) &&
        ((soundObj = FUN_004025a0(*(undefined4 *)(thisPtr + 0x2918)), soundObj != 0 &&
         (*(int *)(soundObj + 0x24) == 3)))) && (*(int *)(thisPtr + 0x1ef4) != -1))
    {
        isActive = '\0';
        local_90 = 0;
        if (*(int *)(DAT_0112b9b4 + 0x34) != -1)
        {
            local_90 = *(int *)(*(int *)(DAT_0112b9b4 + 0x28) + *(int *)(DAT_0112b9b4 + 0x34) * 4);
            soundObj = FUN_004461c0(local_90, 0); // likely loadAudioStream
            if (soundObj != 0)
            {
                FUN_0043aff0(soundObj, 0xd7e44d6a); // start sound with ID
                isActive = FUN_0043b120(); // check if sound finished (yield?)
                while (isActive == '\0')
                {
                    FUN_0043b210(); // resume sound system?
                    soundObj = FUN_0043ab70(); // get current sound state
                    if (soundObj == 1)
                    {
                        FUN_00401ea0(); // stop sound?
                        local_74 = local_74_buf;
                        FUN_0043b210(local_74); // get sound data
                        FUN_0043ad10(local_74); // decode?
                        localPtr = (int *)FUN_00445210(local_78);
                        soundObj = *localPtr;
                        if (((soundObj != -0x1e98fd1) && (soundObj != 0)) && (soundObj = FUN_00446290(soundObj), soundObj != 0))
                        {
                            FUN_0043aff0(soundObj, 0x7081ed5); // start another sound
                            isActive = FUN_0043b120();
                            goto joined_r0x007a8e13;
                        }
                        break;
                    }
                    FUN_0043b1a0(); // update sound system
                    isActive = FUN_0043b120();
                }
            }
LAB_007a8ea0:
            isActive = FUN_009bca20(*(undefined4 *)(local_90 + 0x28)); // check some condition
        }
        callbackArray[0] = 0;
        callbackArray[1] = 0;
        callbackArray[2] = 0;
        callbackFunc = (code *)0x0;
        teamText = PTR_s_MultiPlayerBlue_00e5280c; // "MultiPlayerBlue"
        if (*(int *)(thisPtr + 0x1ef4) == 0)
        {
            teamText = PTR_s_MultiPlayerRed_00e5280c; // "MultiPlayerRed"
        }
        if (isActive == '\0')
        {
            *(undefined **)(DAT_0112990c + 0xc) = teamText; // set UI text
        }
        else
        {
            FUN_004d3e20(thisPtr + 0x2b0); // start transition?
            FUN_004d3f10(0, 0, 0);
            *(undefined4 *)(DAT_0112990c + 0xc) = 0;
        }
        FUN_007a60c0(1); // fade in?
        if (isActive != '\0')
        {
            FUN_004d3e20(callbackArray); // start callback
            *(undefined **)(DAT_0112990c + 0xc) = teamText;
            FUN_009bf2f0(*(undefined4 *)(local_90 + 0x28), thisPtr); // network related?
            FUN_004d3e20(callbackArray);
        }
        *(undefined4 *)(DAT_0112990c + 0xc) = 0;
        if (callbackArray[0] != 0)
        {
            (*callbackFunc)(callbackArray[0]); // invoke callback
        }
    }
    return;
joined_r0x007a8e13:
    if (isActive != '\0') goto LAB_007a8ea0;
    FUN_0043b210();
    soundObj = FUN_0043ab70();
    if (soundObj == 0) {
        FUN_0043b210();
        uVar4 = FUN_0043ab90();
LAB_007a8e84:
        FUN_004d3d90(uVar4);
    }
    else {
        if (soundObj == 1) {
            FUN_0043b210();
            uVar4 = FUN_0043ab90();
            goto LAB_007a8e84;
        }
        if (soundObj == 2) {
            FUN_0043b210();
            uVar4 = FUN_0043ab90();
            goto LAB_007a8e84;
        }
    }
    FUN_0043b1a0();
    isActive = FUN_0043b120();
    goto joined_r0x007a8e13;
}