// FUNC_NAME: SoundInstance::setStream
void __thiscall SoundInstance::setStream(int this, int newStream) {
    float fVar1;
    float fTemp0;
    float fStack_94;
    undefined1 local_90[4];
    float fStack_8c;
    float fStack_84;
    float fStack_7c;
    undefined4 uStack_74;
    undefined4 uStack_70;
    undefined4 uStack_6c;
    undefined4 uStack_68;
    undefined4 uStack_64;
    undefined4 uStack_60;
    undefined4 uStack_5c;
    undefined4 uStack_58;
    undefined4 uStack_54;
    undefined4 uStack_50;
    undefined4 uStack_44;
    undefined4 uStack_40;
    undefined4 uStack_3c;
    undefined4 uStack_38;
    undefined4 uStack_34;
    undefined4 uStack_30;
    undefined4 uStack_2c;
    undefined4 uStack_28;
    float fStack_24;
    undefined4 uStack_20;
    undefined1 uStack_1c;

    // Release the previous stream
    FUN_009e7530(*(int *)(this + 0x18));
    // Store the new stream and add reference
    *(int *)(this + 0x18) = newStream;
    FUN_009e7450(newStream);

    // Virtual call to get stream info (likely returns a struct with format details)
    (*(code **)(**(int **)(this + 0x18) + 0x18))(local_90); // sampleInfo

    // Compute the playback duration from the sample info
    // fStack_84 and fStack_94 are likely start and end sample indices or times
    fVar1 = 0.0f;
    fTemp0 = fStack_84 - fStack_94;
    if (fTemp0 >= 0.0f) {
        fVar1 = fTemp0;
    }
    if (fVar1 <= (fStack_7c - fStack_8c)) {
        fVar1 = fStack_7c - fStack_8c;
    }

    // Build a command structure for the sound system
    uStack_74 = 0;
    uStack_70 = 0;
    uStack_6c = 0;
    uStack_68 = 0;
    uStack_64 = 0;
    uStack_60 = 0;
    uStack_5c = 0;
    uStack_58 = 0;
    uStack_50 = 0;
    uStack_44 = 0;
    uStack_3c = 0;
    uStack_38 = 0;
    uStack_34 = 0;
    uStack_30 = 0;
    uStack_2c = 0;
    uStack_1c = 0;

    // Fill in known fields with global constants and computed values
    uStack_54 = DAT_00e2b1a4; // some format constant
    uStack_40 = DAT_00e2b1a4;
    uStack_28 = DAT_00e2b334; // other constant
    fStack_24 = (float)DAT_00e2b1a4; // float version of constant
    uStack_20 = 4; // command type = 4 (likely "set stream" command)

    // Start the command
    FUN_00552340();

    // Set the stream pointer and computed duration
    uStack_2c = *(int *)(this + 0x18);
    fStack_24 = fVar1 * DAT_00e2cd54 * *(float *)(this + 0x80); // duration = computedLength * globalRate * instanceFactor

    // Send the command
    FUN_005523c0();
    return;
}