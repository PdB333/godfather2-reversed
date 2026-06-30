// FUNC_NAME: ProgressState::isFinished

struct ProgressState {
    // +0x54: flag indicating if this progress is active
    char active;
    // +0x58: flag to invert the comparison logic
    int invertFlag;
    // +0x5c: current progress value (e.g., elapsed time, completion ratio)
    float current;
    // +0x70: target value at which progress is considered complete
    float target;
};

// Global constant at 0x00d5780c, likely 1.0f
extern float _DAT_00d5780c;

bool __fastcall ProgressState::isFinished(ProgressState* this) {
    if (this->active) {
        if (this->current <= this->target) {
            // Within normal range: if no inversion, finished
            if (this->invertFlag == 0) {
                return true;
            }
        } else {
            // Current exceeds target: compute ratio of target/current
            float ratio = this->target / this->current;
            if (this->invertFlag != 0) {
                // Invert ratio: 1.0 - ratio
                ratio = _DAT_00d5780c - ratio;  // _DAT_00d5780c is 1.0f
            }
            // If ratio >= 1.0, consider finished
            if (_DAT_00d5780c <= ratio) {
                return true;
            }
        }
    }
    return false;
}