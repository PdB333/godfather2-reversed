// FUNC_NAME: ChaseCamera::lerpToTarget
class ChaseCamera {
public:
    // Updates camera state towards target, using factor (0..1) for interpolation.
    // state layout: [0-3] quaternion, [4-5] position (x,y)
    static const float kLerpConstant = 1.0f; // from DAT_00e2b1a4 (assumed 1.0)

    void lerpToTarget(const float* target, float factor) {
        float t0 = target[0];
        float t1 = target[1];
        float t2 = target[2];
        float t3 = target[3];

        // Interpolate first 4 components (quaternion)
        state[0] = (t0 - state[0]) * factor + state[0];
        state[1] = (t1 - state[1]) * factor + state[1];
        state[2] = (t2 - state[2]) * factor + state[2];
        state[3] = (t3 - state[3]) * factor + state[3];

        // Interpolate last 2 components (position)
        state[4] = target[4] * factor + state[4] * (kLerpConstant - factor);
        state[5] = target[5] * factor + state[5] * (kLerpConstant - factor);
    }

private:
    float state[6]; // +0x00: quaternion (4 floats), +0x10: position (2 floats)
};