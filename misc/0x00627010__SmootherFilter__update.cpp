// FUNC_NAME: SmootherFilter::update
// Address: 0x00627010
// Role: Updates a smoothing/rate-limiting filter. Implements:
//   - Threshold-based check (if m_currentCount < m_maxThreshold/4 and m_maxThreshold > 64 → call threshold handler)
//   - Factor halving when factor > 64 (with intermediate value stored via FUN_006279a0)
//   - Output computed as 2*previousOutput - inputValue (second-order prediction)

#include <cstdint>

// Forward declarations of called functions
extern void FUN_00638740();           // Handles threshold exceed (e.g., reset or adjust)
extern uint32_t FUN_006279a0(uint32_t a, uint32_t b); // Some clamp/interpolation

class SmootherFilter {
public:
    struct State {
        int32_t  m_maxThreshold;   // +0x04  (threshold for count)
        int32_t  m_currentCount;   // +0x08  (current count for comparison)
        // padding or other fields (offsets 0x0C, 0x10, 0x14)
        uint32_t m_smoothedValue;  // +0x18  (intermediate smoothed value)
        uint32_t m_factor;         // +0x1C  (rate factor, halved when > 64)
        int32_t  m_currentOutput;  // +0x20  (new output after update)
        int32_t  m_previousOutput; // +0x24  (previous output, used in 2*prev - input)
    };
    State* m_pState; // +0x10

    void update(int32_t inputValue) {
        State* state = m_pState;

        // Condition: if (m_currentCount < floor(m_maxThreshold / 4)) and threshold > 64
        // The expression: (maxThreshold + (maxThreshold >> 31 & 3)) >> 2 implements signed division rounding to -inf
        int32_t thresholdDiv4 = (state->m_maxThreshold + ((state->m_maxThreshold >> 31) & 3)) >> 2;
        if (state->m_currentCount < thresholdDiv4 && state->m_maxThreshold > 64) {
            FUN_00638740();  // e.g., increase threshold or reset counter
        }

        // If factor exceeds 64, halve it and compute intermediate smoothed value
        if (state->m_factor > 64) {
            uint32_t oldFactor = state->m_factor;
            uint32_t halfFactor = oldFactor >> 1;
            state->m_smoothedValue = FUN_006279a0(oldFactor, halfFactor);
            state->m_factor = halfFactor;
        }

        // Update output using a linear prediction: new = 2*previous - input (overshoot correction)
        state->m_currentOutput = 2 * state->m_previousOutput - inputValue;
    }
};