// FUNC_NAME: PlayerGroundSM::update
void __fastcall PlayerGroundSM::update(PlayerGroundSM* this, int currentTimeMs)
{
    int speedDiff;
    float deltaTimeFloat;
    bool isTransitReady;
    int currentSpeed;
    uint newAccumulatedTime;
    
    // Check if state is not paused (bits 2 and 3 are clear)
    if ((*(byte*)((int)&this->flags + 0x2e) & 0xc) == 0) {
        // Check if accumulated time minus threshold plus current time is below a limit
        if ((uint)((this->accumulatedTime - this->lastTransitionTime) + currentTimeMs) < (uint)this->thresholdTime) {
            return;
        }
        // Compute new accumulated time and clamp to 1000ms
        newAccumulatedTime = ((this->accumulatedTime - this->lastTransitionTime) - this->thresholdTime) + currentTimeMs;
        this->accumulatedTime = newAccumulatedTime;
        if (1000 < newAccumulatedTime) {
            this->accumulatedTime = 1000;
        }
    }
    
    // Call virtual update function (state-specific logic)
    (*(void (**)(PlayerGroundSM*))(*((int*)this) + 0x34))(this);
    
    // Check if transition condition is met
    isTransitReady = FUN_00653da0();
    if (!isTransitReady) {
        isTransitReady = (*(bool (**)(PlayerGroundSM*))(*((int*)this) + 0x54))(this);
    }
    if (isTransitReady) {
        // Perform transition: set last transition time, call transition functions
        this->lastTransitionTime = currentTimeMs;
        FUN_006530a0(0);
        FUN_00653df0();
        FUN_0064b440();
        return;
    }
    
    // If flags indicate acceleration/deceleration is active (bits 2 or 3 set)
    if ((*(byte*)((int)&this->flags + 0x2e) & 0xc) != 0) {
        currentSpeed = this->currentSpeed;
        speedDiff = currentSpeed - this->previousSpeed;           // +0x24 - +0x70
        deltaTimeFloat = (float)(currentTimeMs - this->lastUpdateTime); // +0x71
        if (currentTimeMs - this->lastUpdateTime < 0) {
            deltaTimeFloat = deltaTimeFloat + 4294967296.0f; // Wrap-around compensation
        }
        // Check if acceleration exceeds threshold (speedDiff * rate * delta > 1.0) or speedDiff exceeds global max
        if (((1.0 < (float)speedDiff * DAT_00e35654 * deltaTimeFloat * DAT_00e3ac54) ||
            ((double)speedDiff > _DAT_00e44960)) &&
            (this->previousSpeed != currentSpeed)) {
            this->previousSpeed = currentSpeed;
            this->lastUpdateTime = currentTimeMs;
            FUN_00653a60();  // Apply acceleration smoothing
        }
    }
}