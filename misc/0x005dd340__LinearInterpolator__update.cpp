// FUNC_NAME: LinearInterpolator::update
// Function address: 0x005dd340
// Updates a linear interpolation timer and computes interpolated values.
// Called with deltaTime in XMM0 (__fastcall: this in ECX, float dt in XMM0).
// Returns 1 (true) always.

class LinearInterpolator {
public:
    // Offsets relative to this:
    float startValueA;          // +0x00 (param_1[0])
    float startValueB;          // +0x04 (param_1[1])
    float duration;             // +0x08 (param_1[2]) max time
    // padding? 0x0C-0x20 unknown
    float timer;                // +0x24 (param_1[9]) accumulated time
    // +0x28 (param_1[10]) source for interpolation A start (maybe same as startValueA?)
    float targetA;              // +0x30 (param_1[0xc]) end value for A
    float targetB;              // +0x34 (param_1[0xd]) end value for B
    float currentA;             // +0x38 (param_1[0xe]) output interpolated A
    float currentB;             // +0x3C (param_1[0xf]) output interpolated B
    int integerStart;           // +0x40 (param_1[0x10]) starting integer (cast to float)
    int integerEnd;             // +0x44 (param_1[0x11]) final integer value
    float integerSpeed;         // +0x48 (param_1[0x12]) multiplier for integer interpolation
    int currentInteger;         // +0x4C (param_1[0x13]) output integer

    bool finished;              // +0x23 (byte flag, 1 if done)
    bool started;               // +0x22 (byte flag, maybe used for one-time initialization)

    int update(float dt) {
        if (!finished) {
            timer += dt;
            if (duration <= timer) {
                // Interpolation complete
                if (!started) {
                    // Snap to final values on first frame of completion
                    currentA = startValueA;
                    currentInteger = integerEnd;
                    currentB = startValueB;
                }
                finished = true;
                return 1;
            }

            // Linear interpolation for A and B
            float t = timer;
            currentA = targetA * t + startValueA;   // Actually param_1[10] is startA? Looks like param_1[10] is used as start, not startValueA.
            // Wait, decompiled: param_1[0xe] = (float)param_1[0xc] * fVar2 + (float)param_1[10];
            // So currentA = targetA * t + param_1[10]; param_1[10] is offset 0x28.
            // Similarly currentB = targetB * t + startValueB (param_1[1] is startValueB).
            // So there is a separate start for A at offset 0x28, not startValueA.
            currentB = targetB * t + startValueB;   // startValueB is offset 0x04

            // Integer interpolation: integerStart + integerSpeed * t, rounded
            float integerTemp = static_cast<float>(integerStart);
            if (integerStart < 0) {
                integerTemp += extern_float_00e44578; // some constant offset for negatives? Probably to fix rounding direction.
            }
            currentInteger = static_cast<int>(std::round(integerTemp + integerSpeed * t));
        }
        return 1;
    }

private:
    // Global constant used for negative integer interpolation
    extern float extern_float_00e44578;
};

// Note: The exact assignments for startA and currentA differ from simplistic interpretation.
// The decompiled code uses param_1[10] (offset 0x28) as the starting value for A interpolation,
// not param_1[0] (startValueA). So we add a field startA at +0x28.
// Also, on completion, it copies startValueA to currentA, not necessarily startA.
// This suggests startValueA might be a separate "from" value for the entire motion, while startA is the initial value when the interpolation began.
// We'll restructure with proper fields:

// Reconstructed version with correct offsets:

class LinearInterpolator {
public:
    // Offsets (all floats unless noted)
    float initialValueA;        // +0x00 (param_1[0]) - original start, used as default when finishing
    float initialValueB;        // +0x04 (param_1[1]) - original start B
    float duration;             // +0x08 (param_1[2])

    // Unknown gaps: +0x0C to +0x20 (6 floats or 24 bytes)
    // Maybe reserved or other fields

    float timer;                // +0x24 (param_1[9])

    float startA;               // +0x28 (param_1[10]) - actual start for A at time zero
    // +0x2C? Not used directly? Maybe another field

    float targetA;              // +0x30 (param_1[0xc]) - end for A
    float targetB;              // +0x34 (param_1[0xd]) - end for B

    float currentA;             // +0x38 (param_1[0xe]) - output interpolated A
    float currentB;             // +0x3C (param_1[0xf]) - output interpolated B

    int integerBase;            // +0x40 (param_1[0x10]) - base integer value
    int integerFinal;           // +0x44 (param_1[0x11]) - final integer value (when finished)
    float integerFactor;        // +0x48 (param_1[0x12]) - multiplier for integer interpolation

    int currentInteger;         // +0x4C (param_1[0x13]) - output integer

    bool flagStarted;           // +0x22 (byte)
    bool finished;              // +0x23 (byte)

    // Update with delta time
    // Returns 1 always (bool true)
    int __fastcall update(float dt) {
        if (finished) {
            return 1;
        }

        timer += dt;
        if (timer >= duration) {
            // Animation complete
            if (!flagStarted) {
                currentA = initialValueA;
                currentInteger = integerFinal;
                currentB = initialValueB;
            }
            finished = true;
            return 1;
        }

        // Interpolation
        float t = timer;
        currentA = targetA * t + startA;         // +0x28 is startA
        currentB = targetB * t + initialValueB;  // +0x04 is initialValueB (used as start for B)

        // Compute integer interpolation
        float intTemp = static_cast<float>(integerBase);
        if (integerBase < 0) {
            intTemp += extern_float_00e44578; // constant for negative rounding
        }
        currentInteger = static_cast<int>(std::round(intTemp + integerFactor * t));

        return 1;
    }

private:
    static float extern_float_00e44578; // defined elsewhere
};

// Note: The function always returns 1, suggesting it is a success/continue indicator.
// The mapping of fields is speculative but consistent with offset usage.
// The class likely corresponds to a simple tween/interpolator in the EA EARS engine.