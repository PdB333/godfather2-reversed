// FUNC_NAME: SmoothAngleInterpolator::update

#include <cmath>

class SmoothAngleInterpolator {
public:
    // +0x00: float m_startValue;      // initial value for x interpolation
    // +0x04: float m_endValue;        // target value for y interpolation
    // +0x08: float m_duration;        // total interpolation time
    // +0x22: bool m_resetFlag;        // if true, skip resetting outputs on completion
    // +0x23: bool m_completed;        // interpolation finished flag
    // +0x24: float m_elapsed;         // current accumulated time
    // +0x28: float m_offsetConst;     // constant offset for x interpolation
    // +0x30: float m_rateX;           // rate multiplier for x interpolation
    // +0x34: float m_rateY;           // rate multiplier for y interpolation
    // +0x38: float m_resultX;         // interpolated x output
    // +0x3c: float m_resultY;         // interpolated y output
    // +0x40: int m_angleIndex;        // integer angle index (for wrapping)
    // +0x44: float m_angleEnd;        // target angle value
    // +0x48: float m_angleRate;       // angle rate multiplier
    // +0x4c: float m_angleResult;     // computed angle result

    int __thiscall update(float dt) {
        if (!m_completed) {
            m_elapsed += dt;

            if (m_elapsed >= m_duration) {
                if (!m_resetFlag) {
                    m_resultX = m_startValue;
                    m_angleResult = m_angleEnd;
                    m_resultY = m_endValue;
                }
                m_completed = true;
                return 1;
            }

            float baseAngle = static_cast<float>(m_angleIndex);
            m_resultX = m_rateX * m_elapsed + m_offsetConst;
            m_resultY = m_rateY * m_elapsed + m_endValue;

            if (m_angleIndex < 0) {
                baseAngle += DAT_00e44578; // angle wrap constant (likely 360.0f or 2π)
            }

            m_angleResult = static_cast<float>(static_cast<int>(
                roundf(baseAngle + m_angleRate * m_elapsed)
            ));
        }
        return 1;
    }

private:
    // Data layout assumed to match offsets above; actual members not declared
    // due to the binary structure. Use placement new or reinterpret_cast.
};