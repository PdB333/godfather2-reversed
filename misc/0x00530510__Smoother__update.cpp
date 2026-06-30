//FUNC_NAME: Smoother::update
// Function address: 0x00530510
// Role: Exponential smoothing filter with variable time step (used for camera/character smoothing)

extern float DAT_00e2b1a4; // global smoothing factor (likely 1.0f)

class Smoother {
public:
    float m_state[9]; // +0x00: state array (0-3: position/quaternion, 4-5: velocity/scale, 8: accumulated time)

    void __fastcall update(float* target) {
        float kSmoothFactor = DAT_00e2b1a4;
        float target1 = target[1];
        float target2 = target[2];
        float target3 = target[3];
        float newAccum = m_state[8] + kSmoothFactor;
        float alpha = kSmoothFactor / newAccum; // interpolation weight

        // Lerp for first 4 components (position/quaternion)
        m_state[0] = (target[0] - m_state[0]) * alpha + m_state[0];
        m_state[1] = (target1 - m_state[1]) * alpha + m_state[1];
        m_state[2] = (target2 - m_state[2]) * alpha + m_state[2];
        m_state[3] = (target3 - m_state[3]) * alpha + m_state[3];

        // Different blend for components 4 and 5 (velocity/scale?)
        m_state[4] = target[4] * alpha + m_state[4] * (kSmoothFactor - alpha);
        m_state[5] = target[5] * alpha + m_state[5] * (kSmoothFactor - alpha);

        m_state[8] = newAccum; // update accumulator
    }
};