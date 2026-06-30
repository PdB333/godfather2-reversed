// FUNC_NAME: Timer::update
// Address: 0x00754a60
// Updates a timer by a delta time, clamps to zero, and recomputes progress.

class Timer {
public:
    // Offsets from this:
    // +0x60 float m_duration     (total duration)
    // +0x84 float m_progress     (remaining / duration, computed)
    // +0x88 float m_remaining    (time left before timer fires)

    void __thiscall update(float dt) {
        // Decrease remaining time by dt
        float newRemaining = m_remaining - dt;

        if (newRemaining <= 0.0f) {
            // Timer has expired or overshot – handle clamping to zero
            float overshoot = m_remaining + dt; // sum (same as original + dt)
            if (overshoot >= 0.0f) {
                m_remaining = 0.0f;         // snap to zero
            } else {
                m_remaining = overshoot;    // keep negative value
            }
        } else {
            m_remaining = newRemaining;     // still ticking
        }

        // Update progress ratio only if duration is positive
        if (m_duration > 0.0f) {
            m_progress = m_remaining / m_duration;
        }
    }

private:
    // Offset: +0x60 (4 bytes)
    float m_duration;
    // Offset: +0x84 (4 bytes)
    float m_progress;
    // Offset: +0x88 (4 bytes)
    float m_remaining;
};