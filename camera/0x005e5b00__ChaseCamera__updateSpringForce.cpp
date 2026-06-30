// FUNC_NAME: ChaseCamera::updateSpringForce
void __thiscall ChaseCamera::updateSpringForce(float target, float current, float deltaTime, float springStiffness) {
    // Global spring data array – each entry 0x18 bytes
    // Offset mapping:
    // +0x00: currentPosition? (used as *springData)
    // +0x04: maxForce? (maxValue)
    // +0x0C: stiffness? (springData[3])
    // +0x14: damping? (springData[5])

    float *springData = (float *)(0x00e2afc8 + (int)this * 0x18);
    float result;
    float var1, var2, var3;

    const float MAX_SPRING_FORCE = *(float *)0x00e2b1a4;
    const float SPRING_THRESHOLD = *(float *)0x00e44598;
    const float SPRING_RATE = *(float *)0x00e39f98;
    const float SPRING_RANGE = *(float *)0x00e44564;

    if (current - target < 0.0f) {
        springStiffness = target - springStiffness;
        result = 0.0f;
        var3 = SPRING_RANGE - (current - target);

        if (springStiffness <= 0.0f) return;
        if (var3 <= 0.0f) return;

        var2 = springData[1]; // +0x04
        var1 = springData[0]; // +0x00
        float limit = MAX_SPRING_FORCE;

        if (SPRING_THRESHOLD < springStiffness) {
            limit = SPRING_RATE / springStiffness;
        }
        limit = limit * var3;

        if (limit <= var2) {
            if (var1 < limit) {
                result = SPRING_RANGE - (limit - var1) * springData[5]; // +0x14
            }
            goto done;
        }
    } else {
        deltaTime = deltaTime - current;
        if (deltaTime <= 0.0f) return;
        if (current - deltaTime <= 0.0f) return;

        var2 = springData[1];
        var1 = springData[0];
        float limit = MAX_SPRING_FORCE;

        if (SPRING_THRESHOLD < deltaTime) {
            limit = SPRING_RATE / deltaTime;
        }
        limit = limit * (current - deltaTime);

        if (limit <= var2) {
            result = MAX_SPRING_FORCE;
            if (var1 < limit) {
                result = MAX_SPRING_FORCE - (limit - var1) * springData[5];
            }
            goto done;
        }
    }

    // Overshoot case
    result = springData[3] - (limit - var2) * springData[5];
    if (result < 0.0f) {
        result = 0.0f;
    }

done:
    // Special case for player index (index 3)
    if ((int)this == 3) {
        if (MAX_SPRING_FORCE - result <= 0.0f) return;
        if (MAX_SPRING_FORCE <= MAX_SPRING_FORCE - result) return;
    }

    return;
}