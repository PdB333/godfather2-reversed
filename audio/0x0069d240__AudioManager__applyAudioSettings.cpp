// FUNC_NAME: AudioManager::applyAudioSettings
void AudioManager::applyAudioSettings(char forceDefault)
{
    AudioManager* audioMgr = (AudioManager*)DAT_012233b4;
    if (!audioMgr) return;

    int category3Volume = 6;  // default volume for category 3 (dialog?)
    if (DAT_01129fad != 0)    // global subtitle flag enabled?
    {
        category3Volume = 0x16; // 22 = some other volume
    }

    int configHandle = FUN_0069d500();            // get current audio config handle
    audioMgr->currentConfig = configHandle;        // +0x540

    if (forceDefault == 0)
    {
        category3Volume = 6;  // override back to default if forced
    }

    FUN_0040f900(3, category3Volume);             // set audio category 3 volume

    int speechMode = 2;                           // default mode
    if (forceDefault != 0)
    {
        char isDonMode = FUN_00496940();          // check if player is Don
        if (isDonMode != 0)
        {
            speechMode = 1;                       // don mode -> different speech handling
        }
    }

    char isCutscene = FUN_004969c0();             // check if cutscene active
    int category2Volume = (isCutscene != 0) ? 4 : 0; // -(-(uint)(isCutscene!=0) & 0xfffffffc) + 8
    category2Volume += speechMode;                // combine with speech mode
    FUN_0040f900(2, category2Volume);             // set audio category 2 volume

    DAT_01129faf = 1;  // mark audio settings as applied
}