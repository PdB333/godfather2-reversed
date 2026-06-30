// FUNC_NAME: TimerController::updateTimer
// Function at 0x006c54e0: Updates an interpolation timer for UI/animation, 
// using a dynamic method call (by hash) to query a condition.

#include <cstdint>

// Forward declaration for the object that provides the dynamic method.
class StateMachineBase;

class TimerController {
public:
    // +0xE8: Pointer to a state machine or behavior object.
    void* m_stateMachine;
    // +0x2BC (700): Active flag (byte).
    bool m_isActive;
    // +0x2D8: Tick counter (0-2 internally).
    int32_t m_tick;
    // +0x2DC: Interpolated value (smoothed result).
    float m_interpolation;

    // Global constants (from .data section, approximate).
    static constexpr float kThreshold = 0.0f;   // DAT_00e44598
    static constexpr float kMask = 0.0f;        // DAT_00e44680
    static constexpr float kSmooth = 0.0f;      // _DAT_00d5cf70
    static constexpr float kMaxClamp = 0.0f;    // DAT_00d5eee4

    // Reconstructed method.
    void* updateTimer() {
        void* conditionResult = nullptr;
        StateMachineBase* baseObj = nullptr;

        // Derive base object pointer from state machine member.
        if (m_stateMachine != nullptr) {
            baseObj = reinterpret_cast<StateMachineBase*>(
                reinterpret_cast<char*>(m_stateMachine) - 0x48
            );
        }

        // Call virtual method #4 (vtable offset 0x10) with hash 0xa5975eb2.
        // This corresponds to something like "isEnabled()" or "isVisible()".
        // The hash identifies the method; the function returns a pointer to a bool.
        if (baseObj != nullptr) {
            conditionResult = reinterpret_cast<void* (*)(void*, uint32_t)>(
                (*reinterpret_cast<void***>(baseObj))[4]
            )(baseObj, 0xa5975eb2);
        }

        // If the method returned a pointer to a non-zero byte, reset tick to 1.
        // (The casting to char checks the low byte of the pointer – a common
        // decompilation artifact; probably meant to dereference the pointer.)
        if (conditionResult != nullptr && *reinterpret_cast<uint8_t*>(conditionResult)) {
            m_tick = 1;
        }

        // Advance tick if active and condition is met.
        if (m_isActive && conditionResult != nullptr) {
            m_tick = (m_tick + 1) % 3;
        }

        // Compute interpolation: difference between tick and current interpolation.
        float diff = static_cast<float>(m_tick) - m_interpolation;

        // Apply smoothing if the masked difference exceeds a threshold.
        uint32_t diffBits = reinterpret_cast<uint32_t&>(diff);
        uint32_t maskBits = reinterpret_cast<uint32_t&>(kMask);
        float maskedDiff = reinterpret_cast<float&>(diffBits & maskBits);
        if (kThreshold < maskedDiff) {
            m_interpolation = diff * kSmooth + m_interpolation;
        }

        // Clamp the interpolation to [0, kMaxClamp].
        if (m_interpolation <= 0.0f) {
            m_interpolation = 0.0f;
        } else if (m_interpolation >= kMaxClamp) {
            m_interpolation = kMaxClamp;
        }

        // Return the condition pointer (used by caller).
        return conditionResult;
    }
};