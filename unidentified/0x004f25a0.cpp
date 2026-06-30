// FUNC_ADDRESS: 0x004f25a0 - TweenController::update (interpolation/timer update)
// This function appears to be part of EA EARS tween system. It processes a timed interpolation
// between start and end values (m_startX..W and m_endX..W), updates current/target positions,
// checks for completion, and clamps/blends values stored in a config block. The deltaTime is
// accumulated and scaled by a global speed factor against a duration. When total elapsed exceeds
// a global threshold, it calls a virtual callback (likely OnFinished). Two interpolation sets are
// computed: one for the current frame (remainder after the full increment) and one for the full
// increment, but the target values are subsequently overwritten (possibly for later use?).

class TweenController {
public:
    // +0x00: vtable
    // +0x04: m_stateIndex (used in flag check)
    // +0x10: m_stateIndex (same as above? decompiler shows param_1[4])
    // +0x0C..0x0F: m_startX, m_startY, m_startZ, m_startW (stored as float via int cast)
    // +0x0C: (float*) start positions
    // +0x24: m_pConfig (pointer to config block)
    // +0x14: m_startTime? (absolute start time?)
    // +0x15: m_elapsedTime (accumulated)
    // +0x16: m_duration (in some unit)
    // +0x17: m_currentClamped (byte: clamped interpolated value)
    // +0x18: m_currentBlended1 (int: first blend result)
    // +0x19: m_currentBlended2 (int: second blend result)
    // +0x1C..0x1F: m_currentX, m_currentY, m_currentZ, m_currentW (current interpolation)
    // +0x20..0x23: m_targetX, m_targetY, m_targetZ, m_targetW (target interpolation, but overwritten?)
    // +0x5D: m_extraByte (byte: second clamped value)

    struct TweenConfig {
        float m_blendMin;    // +0x24: lower clamp bound
        float m_blendSpeed;  // +0x28: used in interpolation step
        float m_clampLower;  // +0x2C: clamp minimum
        float m_clampUpper;  // +0x30: clamp maximum
        float m_blendA;      // +0x34: weight A
        float m_blendB;      // +0x38: weight B
    };

    // Global constants (inferred from DAT_ references)
    static constexpr float kSpeedFactor = 0.0f; // DAT_00e2b1a4 (unknown value)
    static constexpr float kMaxTime = 0.0f;     // DAT_00e446d8 (completion threshold)
    static constexpr float kScaleFactor = 0.0f; // DAT_00e44584 (scale for integer output)

    // Check if a global flag (based on thread-local storage) is enabled for state index
    bool isFlagEnabled(int stateIndex) const {
        // Simplified: actual code dereferences FS segment + 0x2C, then adds stateIndex
        // We'll just return true for reconstruction (original game logic unknown)
        return true;
    }

    void update(float deltaTime) {
        // Skip if global flag disallows this state
        if (!isFlagEnabled(/*param_1[4]*/ m_stateIndex)) {
            return;
        }

        // Accumulate total elapsed time
        float totalElapsed = static_cast<float>(m_elapsedTime); // read current
        m_elapsedTime = static_cast<int>(totalElapsed + deltaTime);
        float newElapsed = (totalElapsed + deltaTime) - static_cast<float>(m_startTime);
        float remainder = newElapsed - deltaTime;
        if (remainder < 0.0f) {
            remainder = 0.0f;
        }

        // Scale times by global speed factor
        float fullScaled = (kSpeedFactor / static_cast<float>(m_duration)) * newElapsed;
        float remScaled = (kSpeedFactor / static_cast<float>(m_duration)) * remainder;

        // Check if complete
        if (kMaxTime <= fullScaled) {
            // Call virtual function at vtable+0x1C (e.g., onComplete)
            (*(void(__thiscall**)(TweenController*))(*reinterpret_cast<int*>(this) + 0x1C))();
            return;
        }

        TweenConfig* config = m_pConfig;

        // Clamp current value for remainder
        float clampedRem = remScaled * config->m_blendSpeed + config->m_blendMin;
        float clampedFull = fullScaled * config->m_blendSpeed + config->m_blendMin;

        // Apply lower/upper bounds
        if (clampedRem < config->m_clampLower) clampedRem = config->m_clampLower;
        if (config->m_clampUpper < clampedRem) clampedRem = config->m_clampUpper;

        if (clampedFull < config->m_clampLower) clampedRem = config->m_clampLower; // Note: this overwrites clampedRem
        if (config->m_clampUpper < clampedFull) clampedRem = config->m_clampUpper; // again

        // Compute current interpolation (linear between start and end) using remainder scaled
        // These are written but then overwritten by the original saved values? We keep as-is.
        int saveW = m_targetW; // param_1[0x1F]
        m_currentX = static_cast<int>((static_cast<float>(m_endX) - static_cast<float>(m_startX)) * remScaled + static_cast<float>(m_startX));
        m_currentY = static_cast<int>((static_cast<float>(m_endY) - static_cast<float>(m_startY)) * remScaled + static_cast<float>(m_startY));
        m_currentZ = static_cast<int>((static_cast<float>(m_endZ) - static_cast<float>(m_startZ)) * remScaled + static_cast<float>(m_startZ));
        m_currentW = static_cast<int>((static_cast<float>(m_endW) - static_cast<float>(m_startW)) * remScaled + static_cast<float>(m_startW));
        m_currentW = saveW; // restore original?

        // Compute target interpolation using full scaled time
        saveW = m_targetW; // again but for target
        m_targetX = static_cast<int>((static_cast<float>(m_endX) - static_cast<float>(m_startX)) * fullScaled + static_cast<float>(m_startX));
        m_targetY = static_cast<int>((static_cast<float>(m_endY) - static_cast<float>(m_startY)) * fullScaled + static_cast<float>(m_startY));
        m_targetZ = static_cast<int>((static_cast<float>(m_endZ) - static_cast<float>(m_startZ)) * fullScaled + static_cast<float>(m_startZ));
        m_targetW = static_cast<int>((static_cast<float>(m_endW) - static_cast<float>(m_startW)) * fullScaled + static_cast<float>(m_startW));
        m_targetW = saveW; // restore original?

        // Blend two values from config using weights
        m_currentBlended1 = static_cast<int>((kSpeedFactor - remScaled) * config->m_blendA + remScaled * config->m_blendB);
        m_currentBlended2 = static_cast<int>((kSpeedFactor - fullScaled) * config->m_blendA + fullScaled * config->m_blendB);

        // Write clamped value as byte (scaled)
        float scaledClamp = clampedFull * kScaleFactor;
        m_currentClamped = static_cast<char>(static_cast<int>(clampedRem * kScaleFactor));
        m_extraByte = static_cast<char>(static_cast<int>(scaledClamp));
    }

private:
    // VTable pointer at +0x00
    int m_dummyVtable; // placeholder

    // +0x04: state index for flag check
    int m_stateIndex; 

    // Start values (stored as float but accessed via int cast in decompiler)
    float m_startX;  // +0x0C
    float m_startY;  // +0x10? Actually param_1[4] is +0x10, so careful: offsets are byte-based.
    float m_startZ;  // +0x14? No, we need to be precise. Since param_1 is int*, each index is 4 bytes.
    float m_startW;  // Index 0xC = byte offset 0x30, etc. This is messy.

    // For reconstruction purposes, we'll just declare the fields conceptually.
    // The actual offsets must match. We'll leave the field declarations commented.
    // Real implementation would use pragma pack or explicit offsets.

    // We'll just list member variables logically:
    // int m_vtable;       // +0x00
    // int m_stateIndex;   // +0x04
    // float m_startX;     // +0x0C
    // float m_startY;     // +0x10
    // float m_startZ;     // +0x14
    // float m_startW;     // +0x18
    // ... etc.
    // However, to avoid confusion, we'll use placeholder arrays.

    // Actual members used in the function:
    int field_0x04;       // param_1[1] -> +0x04
    int field_0x10;       // param_1[4] -> +0x10 (state index used in flag)
    TweenConfig* m_pConfig; // param_1[9] -> +0x24
    // Start and end values:
    float m_startX, m_startY, m_startZ, m_startW; // indices 0xC..0xF -> +0x30..0x3C
    float m_endX, m_endY, m_endZ, m_endW;         // indices 0x10..0x13 -> +0x40..0x4C
    int m_startTime;     // param_1[0x14] -> +0x50
    int m_elapsedTime;   // param_1[0x15] -> +0x54
    int m_duration;      // param_1[0x16] -> +0x58
    char m_currentClamped; // param_1[0x17] -> +0x5C
    int m_currentBlended1; // param_1[0x18] -> +0x60
    int m_currentBlended2; // param_1[0x19] -> +0x64
    int m_currentX, m_currentY, m_currentZ, m_currentW; // 0x1C..0x1F -> +0x70..0x7C
    int m_targetX, m_targetY, m_targetZ, m_targetW;     // 0x20..0x23 -> +0x80..0x8C
    char m_extraByte;    // +0x5D
};

// Note: The exact offsets are derived from Ghidra's interpretation of param_1 as int*.
// In the original binary, these might be floats or other types. The decompiler casts to int
// but the arithmetic uses floats, so we keep them as floats in the structure.
// The flag check is simplified; the actual FS segment access is platform-specific.
// The vtable call at +0x1C is likely a completion callback (e.g., TweenController::onComplete).