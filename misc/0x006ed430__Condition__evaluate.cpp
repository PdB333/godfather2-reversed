// FUNC_NAME: Condition::evaluate
// Address: 0x006ed430
// Role: Evaluates a generic condition based on stored type (0=byte distance, 1=int distance, 2=float distance) and threshold.

bool Condition::evaluate(Condition* this, int param) {
    int type = this->type; // +0x00
    bool result = false;

    if (type == 0) {
        // Byte comparison: call byte distance function with param and compare to threshold byte
        byte raw = FUN_006ebff0(this->param1, this->param2, param); // +0x04, +0x08
        result = raw <= *(byte*)&this->threshold; // +0x0C, low byte used
    } else if (type == 1) {
        // Integer comparison
        int val = FUN_006eb7b0(this->param1, this->param2, param);
        return val <= this->threshold; // +0x0C
    } else if (type == 2) {
        // Float comparison
        float10 fVal = (float10)FUN_006eb7c0(this->param1, this->param2, param);
        if (fVal <= (float10)(float)this->threshold) { // +0x0C cast to float
            return true;
        }
        return false;
    }

    return result;
}