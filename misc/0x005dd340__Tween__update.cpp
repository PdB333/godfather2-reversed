// FUNC_NAME: Tween::update
// Address: 0x005dd340
// Role: Updates a 2D linear motion with rotation tween. Moves from start position to target at constant velocity,
//       and rotates from base angle to target angle. The Y component may return to start if one-shot is false.

struct Tween {
    // Field offsets:
    float m_targetPosX;          // +0x00 (final X)
    float m_targetPosY;          // +0x04 (final Y, also used as start Y if no vertical movement)
    float m_duration;            // +0x08 (time to complete motion)
    // Padding bytes from +0x0C to +0x21
    bool m_bOneShot;             // +0x22 (if true, don't snap to target on completion)
    bool m_bDone;                // +0x23 (set to true when duration reached)
    float m_elapsed;             // +0x24 (accumulated time)
    float m_startPosX;           // +0x28 (interpolation base X)
    // +0x2C unknown/unused?
    float m_velocityX;           // +0x30 (units per second in X)
    float m_velocityY;           // +0x34 (units per second in Y)
    float m_currentPosX;         // +0x38 (output interpolated X)
    float m_currentPosY;         // +0x3C (output interpolated Y)
    int m_baseAngle;             // +0x40 (integer degrees, adjusted if negative)
    float m_targetAngle;         // +0x44 (final angle)
    float m_angularVelocity;     // +0x48 (degrees per second)
    float m_currentAngle;        // +0x4C (output interpolated angle)
};

// Global constant used for angle wrapping (360 degrees)
extern const float g_angleWrap = 360.0f;   // DAT_00e44578

bool Tween::update(float deltaTime) {
    // If already done, nothing to update
    if (m_bDone) {
        return true;
    }

    m_elapsed += deltaTime;

    // Check if we have reached the duration
    if (m_elapsed >= m_duration) {
        // Snap to final values only if not a one-shot tween
        if (!m_bOneShot) {
            m_currentPosX   = m_targetPosX;
            m_currentAngle  = m_targetAngle;
            m_currentPosY   = m_targetPosY;   // returns to start Y (same as stored in targetPosY)
        }
        m_bDone = true;
        return true;
    }

    // Interpolate position and angle linearly over time
    float currentTime = m_elapsed;   // raw time, not normalized

    m_currentPosX = m_velocityX * currentTime + m_startPosX;
    m_currentPosY = m_velocityY * currentTime + m_targetPosY;   // base Y is same as target

    // Handle angle with possible negative base
    float baseAngleFloat = (float)m_baseAngle;
    if (m_baseAngle < 0) {
        baseAngleFloat += g_angleWrap;
    }
    m_currentAngle = baseAngleFloat + m_angularVelocity * currentTime;

    return true;
}