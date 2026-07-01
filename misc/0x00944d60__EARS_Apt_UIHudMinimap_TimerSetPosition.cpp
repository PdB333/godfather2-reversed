// Xbox PDB: EARS_Apt_UIHudMinimap_TimerSetPosition
// FUNC_NAME: updateTimerDisplay
void updateTimerDisplay(float timeLeft)
{
    bool bTimerActive;
    char cUrgentFlag;
    uint32_t local_120;
    float leftRotation;
    uint32_t local_118;
    uint32_t local_110;
    uint32_t local_10c;
    float rightRotation;
    uint32_t local_104;
    char rotationName[256];

    // Clamp time to valid range
    if (timeLeft > 0.0f) {
        if (timeLeft > maxTimerValue) {
            timeLeft = maxTimerValue;
        }
    } else {
        timeLeft = 0.0f;
    }

    bTimerActive = false;
    leftRotation = 0.0f;
    rightRotation = 0.0f;
    local_118 = 0;
    local_110 = 0;
    local_104 = 0;
    local_10c = 0;
    local_120 = 0;
    cUrgentFlag = 0;

    // Check if timer should be displayed
    if (timeLeft >= timerActiveThreshold) {
        bTimerActive = true;
        local_118 = 1; // timer_track_right visible
        local_120 = 1; // timer_right visible

        if (timeLeft > timerUrgentThreshold) {
            // Urgent phase: left side fully rotated, right side rotates extra
            rightRotation = (timeLeft - timerUrgentThreshold) * timerRotationSpeed * timerRotationScale;
            local_110 = 1; // timer_track_left visible
            leftRotation = timerRotationScale;
            cUrgentFlag = 1;
            local_10c = 1; // timer_mask_left visible
        } else {
            // Normal phase: left side rotates linearly
            leftRotation = timeLeft * timerRotationSpeed * timerRotationScale;
            local_104 = 1; // timer_mask_right visible
        }
    }

    // Update visibility/flags for timer parts
    setTimerObjectFlag(sTimerTrackRight, 2, local_118);
    setTimerObjectFlag(sTimerTrackLeft, 4, local_110);
    setTimerObjectFlag(sTimerMaskRight, 8, local_104);
    setTimerObjectFlag(sTimerMaskLeft, 0x10, local_10c);
    setTimerObjectFlag(sTimerRight, 0x20, local_120);

    // If timer is active, set rotation for right side
    if (bTimerActive) {
        formatString(rotationName, sTimerRight, "_rotation");
        setFloatProperty(rotationName, leftRotation);
    }

    // Update left side flag and rotation
    setTimerObjectFlag(sTimerLeft, 0x40, cUrgentFlag);
    if (cUrgentFlag != 0) {
        formatString(rotationName, sTimerLeft, "_rotation");
        setFloatProperty(rotationName, rightRotation);
    }

    // Always show background parts
    setTimerObjectFlag(sTimerBgRight, 0x100, 1);
    setTimerObjectFlag(sTimerBgLeft, 0x80, 1);
}