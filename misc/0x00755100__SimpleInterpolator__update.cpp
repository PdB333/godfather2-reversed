// FUNC_NAME: SimpleInterpolator::update
// Function at 0x00755100: Updates a smooth interpolation with speed/target, 
// using absolute value comparisons and firing a changed callback.
void __thiscall SimpleInterpolator::update(int thisPtr, float deltaTime)
{
    float step;
    float newCurrent;
    float remaining;
    float absStep;
    float absChange;
    bool bVar1;
    int* vtable;
    float current;
    float target;
    float speed;
    float local_14;
    float local_10;

    // Global max delta time clamp (avoid huge jumps)
    if (DAT_00d577a0 >= deltaTime) {
        speed = *(float*)(thisPtr + 0x84);     // +0x84: m_speed (rate per second)
        target = *(float*)(thisPtr + 0x88);    // +0x88: m_targetValue
        current = *(float*)(thisPtr + 0x8c);   // +0x8c: m_currentValue

        // If speed is near zero (using absolute value via bitwise mask)
        if (fabsFloat(speed) <= EPSILON_SPEED) {
            // Compare absolute values of target and current
            if (fabsFloat(target) <= fabsFloat(current)) {
                goto set_done;
            }
            // Speed is zero but we need to jump directly to target?
            absStep = fabsFloat(target); // Actually fabs on target? Code: fabs on uint of target
            vtable = (int*)(thisPtr + 0x48); // +0x48: vtable pointer? Actually accessed as int*
            if (*(int*)(thisPtr + 0x48) == 0) {
                vtable = 0;
            } else {
                vtable = (int*)(*(int*)(thisPtr + 0x48) - 0x48); // Offset to base of object?
            }
            // Call a virtual function at offset 0x60 with a global constant and absolute change
            (**(code**)(*vtable + 0x60))(&DAT_00d64c6c, absStep);
            // Set current to target and mark done
            *(float*)(thisPtr + 0x8c) = target;
            *(unsigned char*)(thisPtr + 0x90) = 1; // +0x90: m_reachedTarget
        } else {
            step = speed * deltaTime;
            newCurrent = current + step;
            // If already at target, just mark done
            if (current == target) {
set_done:
                *(unsigned char*)(thisPtr + 0x90) = 1;
                return;
            }
            // Compare absolute value of newCurrent vs target
            if (fabsFloat(newCurrent) < fabsFloat(target)) {
                // Not yet reached target
                absStep = fabsFloat(step);
                vtable = (int*)(thisPtr + 0x48);
                if (*(int*)(thisPtr + 0x48) == 0) {
                    vtable = 0;
                } else {
                    vtable = (int*)(*(int*)(thisPtr + 0x48) - 0x48);
                }
                (**(code**)(*vtable + 0x60))(&DAT_00d64c6c, absStep);
                // Update current to new value (note: unaff_ESI is used in original, likely newCurrent)
                *(float*)(thisPtr + 0x8c) = newCurrent;
                remaining = target - newCurrent;
            } else {
                // Overshoot or exactly reach
                absChange = fabsFloat(target - current);
                vtable = (int*)(thisPtr + 0x48);
                if (*(int*)(thisPtr + 0x48) == 0) {
                    vtable = 0;
                } else {
                    vtable = (int*)(*(int*)(thisPtr + 0x48) - 0x48);
                }
                (**(code**)(*vtable + 0x60))(&DAT_00d64c6c, absChange);
                *(float*)(thisPtr + 0x8c) = target;
                remaining = target - newCurrent;
            }
            // If there's remaining change, apply to some vector/math structure
            if (remaining != 0.0f) {
                // These functions likely operate on a temporary vector (local_14, local_10)
                // Possibly start a math operation, multiply by scalar, and finish
                FUN_00754a10(&local_14);  // Initialize?
                FUN_004a0370(&local_14, &local_14, &DAT_00d64c6c, remaining); // Multiply/apply
                FUN_00754c90(&local_14);  // Finalize?
            }
        }
    }
}