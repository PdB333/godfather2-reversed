// FUNC_NAME: Player::update

// Function at 0x00807ee0: Main per-frame update for the player character.
// Calls several subsystem updates, handles a timer-based interpolation/force application,
// and sanitizes many float fields to prevent NaN propagation.

void __thiscall Player::update(float deltaTime)
{
    // Subsystem updates
    updateAnimation(deltaTime);           // FUN_007fc5d0
    updatePhysics(deltaTime);             // FUN_007f7640
    updateStateMachine();                 // FUN_00805250

    // Check flags at +0x970 and +0x974 (bit 8) – possibly conditional update
    if (((*(uint*)(this + 0x970) >> 8 & 1) == 0) || ((*(uint*)(this + 0x974) >> 8 & 1) == 0))
    {
        updateAlternative(deltaTime);     // FUN_00804340
    }

    // Timer handling – fields at +0xa56 (bool active), +0xa70 (current value),
    // +0xa74 (rate), +0xa78 (elapsed time)
    if (*(bool*)(this + 0xa56))
    {
        if (*(float*)(this + 0xa70) <= *(float*)(this + 0xa78))
        {
            timerLerp((float*)(this + 0xa70), (float*)(this + 0xa74)); // FUN_007f5900
        }

        float current = *(float*)(this + 0xa70);
        if (current <= 0.0f)
        {
            current = 0.0f;
        }
        else
        {
            double d = (double)((*(float*)(this + 0xa78) * DAT_00d5d70c) / (current * DAT_00d5eee4));
            randomInternal(); // FUN_00b99fcb – possibly seed or random call
            current = (float)d * *(float*)(this + 0xa74);
        }

        applyForce(current * DAT_00e445c8, this + 0xa60); // FUN_0056d750
        *(float*)(this + 0xa78) += deltaTime;
    }

    finalUpdate(deltaTime); // FUN_007f5c90

    // ---------- NaN sanitization for many float fields ----------
    // These offsets likely represent state arrays for animation, physics, etc.

    if (NAN(*(float*)(this + 0x994))) *(undefined4*)(this + 0x994) = 0;
    if (NAN(*(float*)(this + 0x998))) *(undefined4*)(this + 0x998) = 0;
    if (NAN(*(float*)(this + 0x99c))) *(undefined4*)(this + 0x99c) = 0;
    if (NAN(*(float*)(this + 0x9a0))) *(undefined4*)(this + 0x9a0) = 0;
    if (NAN(*(float*)(this + 0x9a4))) *(undefined4*)(this + 0x9a4) = 0;
    if (NAN(*(float*)(this + 0x9a8))) *(undefined4*)(this + 0x9a8) = 0;
    if (NAN(*(float*)(this + 0x9ac))) *(undefined4*)(this + 0x9ac) = 0;
    if (NAN(*(float*)(this + 0x9f0))) *(undefined4*)(this + 0x9f0) = 0;
    if (NAN(*(float*)(this + 0x9f4))) *(undefined4*)(this + 0x9f4) = 0;
    if (NAN(*(float*)(this + 0x9f8))) *(undefined4*)(this + 0x9f8) = 0;
    if (NAN(*(float*)(this + 0x9fc))) *(undefined4*)(this + 0x9fc) = 0;
    if (NAN(*(float*)(this + 0xa00))) *(undefined4*)(this + 0xa00) = 0;
    if (NAN(*(float*)(this + 0xa04))) *(undefined4*)(this + 0xa04) = 0;
    if (NAN(*(float*)(this + 0xa08))) *(undefined4*)(this + 0xa08) = 0;
    if (NAN(*(float*)(this + 0xa0c))) *(undefined4*)(this + 0xa0c) = 0;
    if (NAN(*(float*)(this + 0xa10))) *(undefined4*)(this + 0xa10) = 0;
    if (NAN(*(float*)(this + 0xa14))) *(undefined4*)(this + 0xa14) = 0;
    if (NAN(*(float*)(this + 0xa18))) *(undefined4*)(this + 0xa18) = 0;
    if (NAN(*(float*)(this + 0xa1c))) *(undefined4*)(this + 0xa1c) = 0;
    if (NAN(*(float*)(this + 0xa34))) *(undefined4*)(this + 0xa34) = 0;
    if (NAN(*(float*)(this + 0xa38))) *(undefined4*)(this + 0xa38) = 0;
    if (NAN(*(float*)(this + 0xa40))) *(undefined4*)(this + 0xa40) = 0;
    if (NAN(*(float*)(this + 0xa44))) *(undefined4*)(this + 0xa44) = 0;
    if (NAN(*(float*)(this + 0xa48))) *(undefined4*)(this + 0xa48) = 0;
    if (NAN(*(float*)(this + 0xa4c))) *(undefined4*)(this + 0xa4c) = 0;
    if (NAN(*(float*)(this + 0xac0))) *(undefined4*)(this + 0xac0) = 0;
    if (NAN(*(float*)(this + 0xac4))) *(undefined4*)(this + 0xac4) = 0;
    if (NAN(*(float*)(this + 0xac8))) *(undefined4*)(this + 0xac8) = 0;
    if (NAN(*(float*)(this + 0xacc))) *(undefined4*)(this + 0xacc) = 0;
    if (NAN(*(float*)(this + 0xad0))) *(undefined4*)(this + 0xad0) = 0;
    if (NAN(*(float*)(this + 0xad4))) *(undefined4*)(this + 0xad4) = 0;
    if (NAN(*(float*)(this + 0xad8))) *(undefined4*)(this + 0xad8) = 0;
    if (NAN(*(float*)(this + 0xadc))) *(undefined4*)(this + 0xadc) = 0;
    if (NAN(*(float*)(this + 0xb20))) *(undefined4*)(this + 0xb20) = 0;
    if (NAN(*(float*)(this + 0xb24))) *(undefined4*)(this + 0xb24) = 0;
    if (NAN(*(float*)(this + 0xb28))) *(undefined4*)(this + 0xb28) = 0;
    if (NAN(*(float*)(this + 0xb2c))) *(undefined4*)(this + 0xb2c) = 0;
    if (NAN(*(float*)(this + 0xb30))) *(undefined4*)(this + 0xb30) = 0;
    if (NAN(*(float*)(this + 0xb34))) *(undefined4*)(this + 0xb34) = 0;
    if (NAN(*(float*)(this + 0xb38))) *(undefined4*)(this + 0xb38) = 0;
    if (NAN(*(float*)(this + 0xb3c))) *(undefined4*)(this + 0xb3c) = 0;
    if (NAN(*(float*)(this + 0xb50))) *(undefined4*)(this + 0xb50) = 0;
    if (NAN(*(float*)(this + 0xb54))) *(undefined4*)(this + 0xb54) = 0;
    if (NAN(*(float*)(this + 0xb58))) *(undefined4*)(this + 0xb58) = 0;
    if (NAN(*(float*)(this + 0xb5c))) *(undefined4*)(this + 0xb5c) = 0;
    if (NAN(*(float*)(this + 0xb60))) *(undefined4*)(this + 0xb60) = 0;
    if (NAN(*(float*)(this + 0xb64))) *(undefined4*)(this + 0xb64) = 0;
    if (NAN(*(float*)(this + 0xb68))) *(undefined4*)(this + 0xb68) = 0;
    if (NAN(*(float*)(this + 0xb6c))) *(undefined4*)(this + 0xb6c) = 0;
}