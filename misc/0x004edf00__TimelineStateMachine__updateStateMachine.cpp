// FUNC_NAME: TimelineStateMachine::updateStateMachine

void __thiscall TimelineStateMachine::updateStateMachine(TimelineStateMachine* this, void* externalData, bool loopEnabled)
{
    float currentTime = this->elapsed;           // +0x00
    float globalTime = DAT_00e2eff4;             // Global time or delta time
    float one = DAT_00e2b1a4;                    // Presumably 1.0f
    
    // State machine using integer states stored as float bit patterns
    int state = *(int*)&this->stateAsFloat;       // +0x08 (actual integer state)
    
    switch (state) {
        case 1: // State 1: Initial waiting or direct transition
            if (currentTime <= this->param0 || currentTime == this->param0) {
                // Blend complete, output end value
                this->blendedValue = this->param5; // +0x14
                return;
            }
            if (globalTime < this->param1) {       // +0x04
                this->stateAsFloat = 2;             // Move to state 2
                this->elapsed = 0.0f;
                return;
            }
            if (this->param2 <= globalTime) {       // +0x08
                goto setState3AndReset;             // Actually goes to state 3
            }
            // Otherwise fall through to state 3? But code sets state=3 and resets
            // Fallthrough to state 3?
            this->stateAsFloat = 3;
            this->elapsed = 0.0f;
            return;
        case 2: // State 2: Interpolate from param5 to param6 over duration param1
        {
            float duration = this->param1;          // +0x04
            if (currentTime <= duration) {
                float ratio = 0.0f;
                if (duration > 0.0f) {
                    ratio = currentTime / duration;
                }
                // Lerp: (1 - ratio) * param5 + ratio * param6
                this->blendedValue = (one - ratio) * this->param5 + this->param6 * ratio;
                return;
            }
            // If currentTime > duration, break out of switch (no state change)
            break;
        }
        case 3: // State 3: Waiting region between stage durations
        {
            if (currentTime <= this->param2 || currentTime == this->param2) {
                // Still in the first blended segment, param6 is output
                this->blendedValue = this->param6;
                return;
            }
            if (globalTime < this->param3) {        // +0x0c
                this->stateAsFloat = 4;
                this->elapsed = 0.0f;
                return;
            }
            if (globalTime < this->param4) {        // +0x10
                this->stateAsFloat = 5;
                this->elapsed = 0.0f;
                return;
            }
            goto setState6;
        }
        case 4: // State 4: Interpolate from param6 to param7 over duration param3
        {
            float duration = this->param3;
            if (currentTime <= duration) {
                float ratio = 0.0f;
                if (duration > 0.0f) {
                    ratio = currentTime / duration;
                }
                this->blendedValue = (one - ratio) * this->param6 + this->param7 * ratio;
                return;
            }
            if (globalTime < this->param4) {
                this->stateAsFloat = 5;
                this->elapsed = 0.0f;
                return;
            }
            goto setState6;
        }
        case 5: // State 5: Hold until external condition or time
        {
            float* extData = (float*)externalData;
            if (extData[0x11] < this->param4 || extData[0x11] == this->param4) {
                // extData[0x44] as float (at offset 0x44)
                this->blendedValue = this->param7;
                return;
            }
            // Fall through to setState6
            goto setState6;
        }
        case 6: // State 6: Final hold and loop handling
        {
            if (!loopEnabled) {
                return;
            }
            if (globalTime < this->param0) {
                this->stateAsFloat = 1;
                this->blendedValue = this->param5;  // same as label LAB_004ee09e
                return;
            }
            if (globalTime < this->param1) {
                float outVal = this->param5;
                this->stateAsFloat = 2;
                this->blendedValue = outVal;
                return;
            }
            if (this->param2 <= globalTime) {
                return; // Stay in state 6? No state change, just output param6?
                // Actually code jumps to LAB_004ee0d2 which sets state 3? Let's re-evaluate.
            }
            this->stateAsFloat = 3;
            this->blendedValue = this->param6;
            return;
        }
        // default: just return
    }
    return;

setState3AndReset:
    this->stateAsFloat = 3;
    this->elapsed = 0.0f;
    return;

setState6:
    this->stateAsFloat = 6;
    this->elapsed = 0.0f;
    return;
}