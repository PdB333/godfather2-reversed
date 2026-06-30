// FUNC_NAME: Timer::Update
// Address: 0x0071f120
// This function updates a timer (cooldown) and calculates a new random value when the timer expires.
// The class at param_1 (this) contains:
//   +0x00: vtable pointer
//   +0x04: m_state (int) - state ID; compared to 0 and 0x48 (likely a "dead" or "inactive" state)
//   +0x0c: m_timer (float) - remaining time before next action
//   +0x14: m_currentValue (float) - computed random value used by the owner
//   +0x20: m_flags (uint) - bit3 enables update; other bits undefined

void __thiscall Timer::Update(float deltaTime)
{
    float fVar1;
    char bFlag;
    int pGlobalObject;
    float10 fVar4;
    float10 fVar5;
    float10 fVar6;

    // Check if timer is active (bit3 of flags set)
    if ((*(uint *)(this + 0x20) >> 3 & 1) != 0)
    {
        // Decrease timer by delta time
        float newTimer = *(float *)(this + 0x0c) - deltaTime;
        *(float *)(this + 0x0c) = newTimer;

        // If timer expired and state is not null/none, proceed to compute new value
        if (newTimer <= 0.0f &&
            *(int *)(this + 0x04) != 0 &&
            *(int *)(this + 0x04) != 0x48) // 0x48 probably means "dead" or "inactive"
        {
            // Get a global behavior data object (maybe from a manager singleton)
            pGlobalObject = FUN_0043b870(DAT_0112afb8); // returns pointer to some global data (e.g., AIBehaviorData)
            if (pGlobalObject != 0)
            {
                // Reset timer to a fixed value (stored in global constant)
                *(undefined4 *)(this + 0x0c) = _DAT_00d5c458;

                // Random chance check 1 (50%?)
                bFlag = FUN_0078af40();
                if (bFlag != '\0')
                {
                    // First random value: interpolate between global constants using two random numbers
                    fVar4 = (float10)FUN_0078ae90(); // rand1
                    fVar5 = (float10)FUN_0078aee0(); // rand2
                    // Compute: value = ( (globalData->m_param - rand1) / (rand2 - rand1) ) + constant
                    *(float *)(this + 0x14) =
                        (float)(((float10)*(float *)(pGlobalObject + 0x40) - fVar4) / (fVar5 - fVar4) +
                                (float10)_DAT_00d5780c);
                    return;
                }

                // Random chance check 2 (another probability)
                bFlag = FUN_0078b010();
                if (bFlag != '\0')
                {
                    // Second formula: value = globalData->m_param / rand1
                    *(float *)(this + 0x14) = *(float *)(pGlobalObject + 0x40) / (float)FUN_0078ae90();
                    return;
                }

                // Default formula: use three random numbers and two constants
                fVar5 = (float10)FUN_0078aee0(); // rand3
                fVar4 = (float10)DAT_00d5e288;    // constant A
                fVar1 = *(float *)(pGlobalObject + 0x40); // global param
                fVar6 = (float10)FUN_0078aee0(); // rand4
                *(float *)(this + 0x14) =
                    (float)(((float10)fVar1 - fVar6) / ((float10)(float)(fVar4 - fVar5)) +
                            (float10)DAT_00d5eee4); // constant B
            }
        }
    }
    return;
}