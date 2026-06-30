// FUNC_NAME: Action::tick
undefined4 __fastcall Action::tick(Action *this) {
    int conditionFlag;
    undefined4 returnValue;
    float accumulatedTime;

    // Check if we are already in the middle of an update (bit 5 set)
    if ((this->flags & 0x20) != 0) {
        goto done;
    }

    // Set the updating flag to prevent reentrancy
    this->flags |= 0x20;

    // Dereference pointer at +0x10 to get some object, then read its field at +0xd4
    int obj1Field = *(int*)(*(int*)((char*)this + 0x10) + 0xd4);

    if (obj1Field == 0) {
        // If obj1Field is zero, check if bit 0 is already set
        if ((this->flags & 1) == 0) {
            // Not set? then do nothing (fall through)
        } else {
            // Bit 0 is set, jump into the else branch below
            goto checkCondition;
        }
    } else {
        // obj1Field is non-zero, check bit 0
        if ((this->flags & 1) == 0) {
            // Bit 0 not set, set it
            this->flags |= 1;
        } else {
checkCondition:
            // Bit 0 is set, handle the condition based on obj1Field
            if (obj1Field == 0) {
                // If obj1Field became zero again, clear bit 0 and reset timer
                this->flags &= ~1;
                *(float*)((char*)this + 0x38) = 0.0f;
                // If bit 1 is set, set bit 3
                if ((this->flags & 2) != 0) {
                    this->flags |= 8;
                }
            }
        }
    }

    // Compare two values from two different objects (pointers at +0x10 and +0x14)
    int obj1Val = *(int*)(*(int*)((char*)this + 0x10) + 0x40);
    int obj2Val = *(int*)(*(int*)((char*)this + 0x14) + 0x54);
    if (obj1Val == obj2Val) {
        // Values match, set bit 2 (indicating condition satisfied)
        this->flags |= 4;
    } else {
        // Values differ
        if ((this->flags & 1) == 0) {
            // Not in the initial state (bit 0 clear), accumulate timer
            accumulatedTime = *(float*)((char*)this + 0x38) + frameTime;  // DAT_012067e8 likely frame time
            *(float*)((char*)this + 0x38) = accumulatedTime;
            // Check if timer exceeds threshold
            if (cooldownThreshold < accumulatedTime) {  // _DAT_00e50db0 is threshold
                *(float*)((char*)this + 0x38) = 0.0f;
                // Call timeout callback
                callTimeoutFunction();  // FUN_006bf3d0
            }
        }
    }

    // Generate a new return value by calling some function
    returnValue = generateReturnValue();  // FUN_006bef70
    this->result = returnValue;
    // Pass the value to another function (maybe for side effects)
    useReturnValue(returnValue);  // FUN_006bec70

    // Clear the updating flag
    this->flags &= ~0x20;

done:
    return this->result;
}