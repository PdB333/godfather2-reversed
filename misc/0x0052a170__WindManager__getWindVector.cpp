// FUNC_NAME: WindManager::getWindVector
void __fastcall getWindVector(float* outWindForce)
{
    // Global wind state variables
    // DAT_00e2b1a4: base wind magnitude
    // DAT_01125240: burst active flag/magnitude (0 = no active burst)
    // DAT_00e2af44: current time within burst
    // DAT_0112523c: total burst duration
    // DAT_01125230,34,38: burst force components (x,y,z)
    float baseMagnitude = DAT_00e2b1a4;
    float burstActive = DAT_01125240;
    float burstCurrentTime = DAT_00e2af44;
    float burstDuration = DAT_0112523c;

    if ((burstActive != 0.0f) && (burstCurrentTime <= burstDuration))
    {
        // Compute interpolation factor and progress
        float invBurstActive = baseMagnitude / burstActive;          // fVar1
        float progress = invBurstActive * burstDuration;             // fVar2

        // Scale burst force by progress and inverse burst active
        outWindForce[0] = invBurstActive * DAT_01125230 * progress;  // fVar3
        outWindForce[1] = invBurstActive * DAT_01125234 * progress;  // fVar4
        outWindForce[2] = invBurstActive * DAT_01125238 * progress;  // fVar5

        // If progress hasn't reached base magnitude, add an offset
        if (progress < baseMagnitude)
        {
            float offset = baseMagnitude - progress;                  // fVar6
            outWindForce[0] += offset;
            outWindForce[1] += offset;
            outWindForce[2] += offset;
        }

        // Clear burst state (forces become zero, duration resets)
        DAT_01125230 = 0.0f;
        DAT_01125234 = 0.0f;
        DAT_01125238 = 0.0f;
        DAT_0112523c = 0.0f;
        DAT_01125240 = 0.0f;
    }
    else
    {
        // No active burst: constant wind in all components
        outWindForce[0] = baseMagnitude;
        outWindForce[1] = baseMagnitude;
        outWindForce[2] = baseMagnitude;
        outWindForce[3] = baseMagnitude;  // Fourth component used elsewhere?
    }
}