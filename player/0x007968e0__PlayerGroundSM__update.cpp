//FUNC_NAME: PlayerGroundSM::update

void __thiscall PlayerGroundSM::update(int *this, float deltaTime)
{
    uint flags;
    char checkResult;
    int *somePtr;
    int posIndex1;
    int posIndex2;
    float10 distance;
    int *localPtr;

    int state = this[0xae]; // +0x2B8: m_state (0=idle, 1=active, 3=recovery)
    localPtr = this;
    if (state != 0) {
        if (state != 1) {
            if (state != 3) {
                return;
            }
            // State 3: recovery/stagger
            int subState = this[0xb0]; // +0x2C0: m_subState
            if ((((subState != 1) && (subState != 2)) && (subState != 3)) &&
               ((float)(this[0xad] & DAT_00e44680) < DAT_00d5f00c)) { // +0x2B4: m_someFlag & globalMask < threshold
                // Call virtual function on sub-object at +0x100 (m_subStateMachine)
                (**(code **)(*this + 0x1c))(this + 0x100);
            }
        }
        // State 1 or 3: common flag checks
        flags = this[0xaf]; // +0x2BC: m_flags
        if ((((flags >> 0x1b & 1) != 0) || (-1 < (int)flags)) || ((flags >> 0x1c & 1) != 0)) {
            int subState = this[0xb0];
            if (((subState == 1) || (subState == 2)) || (subState == 3)) {
                // Movement function for specific substates
                FUN_00796510(CONCAT31((int3)((uint)subState >> 8), this[0xae] == 1), deltaTime);
            } else {
                // Default movement function
                FUN_00796370(this[0xae] == 1, deltaTime);
            }
            // Notify controller (hash 0xd444da9d)
            (**(code **)(*(int *)this[0x4c] + 0x40))(0xd444da9d, 0); // +0x130: m_controller
        }
        this[0xaf] = this[0xaf] & 0x7fffffff; // Clear sign bit
        return;
    }

    // State 0: idle
    flags = this[0xaf];
    if (((((flags >> 0x1a & 1) == 0) && ((flags >> 0x1b & 1) == 0)) &&
        (((flags >> 0x1d & 1) == 0 || (checkResult = FUN_007943a0(), checkResult == '\0')))) &&
       (((uint)this[0xaf] >> 0x1c & 1) == 0)) {
        // Check distance to some target
        localPtr = (int *)0x0;
        somePtr = (int *)(**(code **)(*(int *)**(undefined4 **)(DAT_012233a0 + 4) + 0xc))(); // Get player manager
        (**(code **)(*somePtr + 0x10))(0x55859efa, &localPtr); // Get some object by hash
        if (localPtr == (int *)0x0) {
            return;
        }
        posIndex1 = FUN_00471610(); // Get position index 1
        posIndex2 = FUN_00471610(); // Get position index 2
        distance = (float10)FUN_0045c470(posIndex2 + 0x30, posIndex1 + 0x30); // Distance between positions
        if (distance <= (float10)DAT_00d6a0bc) { // If too close, return
            return;
        }
        if ((float)this[0xa9] < 0.0) { // +0x2A4: m_timer
            return;
        }
        deltaTime = (float)this[0xa9] - deltaTime;
        this[0xa9] = (int)deltaTime;
        if (0.0 <= deltaTime) {
            return;
        }
    }

    // Fallthrough: timer expired or conditions met
    if ((((uint)this[0xaf] >> 0x1b & 1) == 0) &&
       (((checkResult = FUN_007967a0(), checkResult == '\0' || (checkResult = FUN_007943a0(), checkResult == '\0')) &&
        (((uint)this[0xaf] >> 0x1c & 1) == 0)))) {
        // Reset timer to initial value
        this[0xa9] = this[0xab]; // +0x2AC: m_timerReset
        return;
    }

    // Transition to recovery state
    this[0xaf] = this[0xaf] & 0xfbffffff; // Clear bit 0x1a
    if (((uint)this[0xaf] >> 4 & 1) != 0) {
        this[0xaf] = this[0xaf] & 0xf7ffffff; // Clear bit 0x1c
    }
    this[0xae] = 3; // Set state to recovery
    this[0xa9] = 0; // Reset timer
    return;
}