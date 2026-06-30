// FUNC_NAME: MathUtils::smoothDamp
// Address: 0x006c8c10
// Role: Smooths a value towards a target with spring-like damping, updating velocity.
// Implementation: Uses critically damped spring formula with (1 - smoothTime * deltaTime) damping factor.
// Parameters:
//   current   - current value (modified to new position)
//   target    - target value (also modified to new position, overwritten)
//   velocity  - current velocity (modified)
//   smoothTime - smoothing factor (stiffness-like)
//   deltaTime  - time step

void MathUtils::smoothDamp(float* current, float* target, float* velocity,
                            float smoothTime, float deltaTime)
{
    float currentVal = *current;          // +0x00
    float targetVal = *target;            // +0x00 (same offset, param2)
    float vel = *velocity;                // +0x00

    // Compute intermediate velocity:
    // v = ((target - current) * smoothTime + velocity) * deltaTime
    float v = ( (targetVal - currentVal) * smoothTime + vel ) * deltaTime;

    // Damping factor: 1.0 - smoothTime * deltaTime (global constant assumed 1.0)
    float damping = 1.0f - smoothTime * deltaTime;

    // Call debug assert (likely checks for NaN/inf)
    debugAssertFinite();

    // Update current position:
    // newPos = current + (v + (target - current)) * damping
    float newPos = (v + (targetVal - currentVal)) * damping + currentVal;
    *current = newPos;
    *target = newPos;               // Overwrites target with the new position (odd but observed)

    // Update velocity:
    // newVel = (velocity - v * smoothTime) * damping
    *velocity = (vel - v * smoothTime) * damping;

    return;
}