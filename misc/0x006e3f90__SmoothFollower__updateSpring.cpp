// FUNC_NAME: SmoothFollower::updateSpring
// Function at 0x006e3f90: Smooth follower spring update with damping and clamping
// param_1: this (pointer to SmoothFollower object)
// param_2: index into spring state array (offset +0x128)
// param_3: desired velocity (or acceleration input)
// param_4: threshold distance for spring activation
// param_5: max velocity limit (if > 0.0f)
// Returns: updated velocity (second float of spring state)
struct SpringState {
    float position; // +0x0
    float velocity; // +0x4
};

// Global constants (likely defined elsewhere)
extern float g_targetPosition; // DAT_01205228
extern float g_springConstant; // DAT_00d5f00c (multiplier for spring force)
extern float g_velocityThreshold; // DAT_00e44564 (threshold for velocity clamp)
extern float g_dampingFactor; // DAT_00d5eee4 (damping coefficient)

// External math function (may be sin/cos/easing)
extern double MathEasingFunction(); // FUN_00b99fcb

float SmoothFollower::updateSpring(int index, float desiredVelocity, float threshold, float maxVelocity)
{
    SpringState* state = reinterpret_cast<SpringState*>(*(int*)((uintptr_t)this + 0x128)) + index;
    float diff = g_targetPosition - state->position;

    if (diff < threshold) {
        // Spring is activated: compute new velocity
        desiredVelocity -= state->velocity; // relative velocity
        double ratio = static_cast<double>((diff / threshold) * g_springConstant);
        MathEasingFunction(); // apply easing function (e.g., sin/cos)
        float springForce = static_cast<float>(ratio);
        float newVelocity = springForce * desiredVelocity + state->velocity;
        state->velocity = newVelocity;

        if (maxVelocity > 0.0f) {
            if (desiredVelocity <= maxVelocity) {
                // Clamp to lower bound
                if (desiredVelocity < g_velocityThreshold - maxVelocity) {
                    float dampVel = maxVelocity * g_dampingFactor;
                    state->velocity = dampVel * springForce + newVelocity;
                    if (dampVel <= state->velocity) {
                        state->velocity = state->velocity - dampVel;
                        state->position = g_targetPosition;
                        return state->velocity;
                    }
                }
                goto done;
            }
            // Apply damping when overshooting
            float dampVel = maxVelocity * g_dampingFactor;
            state->velocity = newVelocity - dampVel * springForce;
            if (state->velocity >= 0.0f) {
                goto done;
            }
            desiredVelocity = state->velocity + dampVel;
        }
    }
    state->velocity = desiredVelocity;

done:
    state->position = g_targetPosition;
    return state->velocity;
}