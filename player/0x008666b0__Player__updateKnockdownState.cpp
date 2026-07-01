// FUNC_NAME: Player::updateKnockdownState
// Address: 0x008666b0
// Role: Updates knockdown/stumble recovery timers and determines which animation to play.
// Offsets: +0xfc4 (mLastHitTime), +0xfc8 (mCurrentHitTime), +0x1008 (mRecoveryTimer), +0xf28 (mFlags bits)
// Called from Player::update (0x00866820)

// External globals (likely constants)
static const uint s_knockdownThreshold = (uint&)DAT_00d58cbc;       // time threshold for knockdown
static const float s_recoveryTimeThreshold = DAT_00d5d7b8;          // min recovery time
static const float s_timeMultiplier = _DAT_00e4486c;                // multiplier for recovery time
static const uint s_timeMask = (uint&)DAT_00e44680;                 // mask used to extract fractional part of time
static const uint s_knockdownAnimId = (uint&)DAT_00e540f0;          // animation ID for knockdown
static const uint s_stumbleAnimId = (uint&)DAT_00e540f4;            // animation ID for stumble

void __thiscall Player::updateKnockdownState(void* this,
                                             float deltaTime,
                                             float* outBlendTime,
                                             uint* outAnimId,
                                             bool* outInterruptFlag)
{
    // Calculate time since last hit (fractional part masked by s_timeMask)
    float timeSinceHit = *(float*)((uint)this + 0xfc8) - *(float*)((uint)this + 0xfc4);
    uint maskedTime = (uint&)timeSinceHit & s_timeMask;
    float diff = *(float*)&maskedTime;

    if (diff < *(float*)&s_knockdownThreshold)
    {
        // Still in hit reaction window – choose animation based on recovery time
        float scaledRecovery = deltaTime * s_timeMultiplier;
        if (s_recoveryTimeThreshold <= scaledRecovery)
        {
            *outBlendTime = 0.0f;
            *outAnimId = s_knockdownAnimId;    // knockdown fall
            *outInterruptFlag = false;
        }
        else
        {
            *outBlendTime = 0.0f;
            *outAnimId = s_stumbleAnimId;      // stumble stagger
            *outInterruptFlag = false;
        }
    }

    // Check recovery timer expiration
    if (*(float*)((uint)this + 0x1008) <= 0.0f)
    {
        *(float*)((uint)this + 0x1008) = 0.0f;                 // clear recovery timer
        *(uint*)((uint)this + 0xf28) &= 0xefffffff;            // clear bit 28 (e.g., kFlag_KnockedDown)
        FUN_008659a0();                                          // reset associated resources
    }
}