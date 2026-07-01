// FUNC_NAME: TimedInterpolator::update
void __thiscall TimedInterpolator::update(uint newTarget) {
    float currentTime = DAT_01205228; // global game time
    float fVar1;
    
    // Interpolation based on mode (1 = exponential, else linear)
    if (this->mode == 1) {
        fVar1 = ((float)this->targetValue / (float)this->speedA) * (currentTime - this->lastTime) + this->currentValue;
    } else {
        fVar1 = this->currentValue - (currentTime - this->lastTime) / (float)this->speedB;
    }
    
    this->currentValue = fVar1;
    
    // Clamp/state logic based on global minimum threshold
    float fVar2 = _DAT_00d5780c;
    if (fVar1 < _DAT_00d5780c) {
        fVar2 = 0.0f;
        if (fVar1 > 0.0f) {
            goto update_timestamps; // skip state change, keep value at 0?
        }
        this->state = 0;   // finished
    } else {
        this->state = 1;   // still active
    }
    this->currentValue = fVar2;
    
update_timestamps:
    this->lastTime = currentTime;
    this->targetValue = (float)newTarget; // offset 0x14
}