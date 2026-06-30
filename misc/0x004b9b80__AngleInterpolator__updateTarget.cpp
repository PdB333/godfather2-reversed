// FUNC_NAME: AngleInterpolator::updateTarget
// Address: 0x004b9b80
// Role: Updates current angle toward a target angle with wrapping and quantization
// Note: Uses EARS engine's fast floating-point operations with sign-magnitude trick

// Global constants (guessed based on typical game math)
#define TWOPI 6.283185307f
#define PI 3.141592654f
#define SCALE_FACTOR 0.000095873f   // 1/10430.378? Derived from (float)(int)(delta*_DAT_00e44774)*_DAT_00e2af34
// Actual values would be loaded from globals at runtime

class AngleInterpolator {
private:
    float currentAngle; // +0x00

public:
    // __fastcall with this in ECX, target angle in XMM0
    void __fastcall updateTarget(float targetAngle) {
        float delta = targetAngle - this->currentAngle;
        
        // Compute absolute value using bitwise mask (clear sign bit, keep magnitude)
        // DAT_00e44680 = 0x7FFFFFFF (mask for float sign bit)
        uint32_t absBits = *(uint32_t*)&delta & 0x7FFFFFFF;
        float absDelta = *(float*)&absBits;
        
        if (TWOPI < absDelta) {
            if (delta <= PI) {
                delta -= TWOPI;
            } else {
                delta += TWOPI;
            }
            // Quantize and scale the delta, then add to current angle
            // _DAT_00e44774 is a quantization factor (e.g., 1 / step_size)
            // _DAT_00e2af34 is a scaling factor (e.g., angular speed * dt)
            this->currentAngle += (float)(int)(delta * 10430.378f) * 0.000095873f;
        }
        // Otherwise, no change (delta already small)
    }
};