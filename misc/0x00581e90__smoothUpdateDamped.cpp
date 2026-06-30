// FUNC_NAME: smoothUpdateDamped

// Address: 0x00581e90
// Role: Applies smooth damping interpolation using parameters passed in EAX register
// Called from multiple locations (e.g. 0x0058b530, 0x0058bba0)

extern float DAT_00e2b1a4; // Threshold / time step constant

// Parameters structure accessed via EAX (fastcall second argument convention)
struct SmoothParams {
    float a;      // +0x00
    float b;      // +0x04
    float c;      // +0x08 (threshold check target)
    float d;      // +0x0C (difference reference)
    float e;      // +0x10 (scale factor)
    float flags;  // +0x14 (bitfield: bit7 used as enable flag)
};

// Object receiving updates, passed in ECX
struct SmoothTarget {
    // +0x1C
    float field_1C;
    // +0x28
    float field_28;
};

void __fastcall smoothUpdateDamped(SmoothTarget* obj, SmoothParams* params)
{
    // Check if bit7 of flags == 0 (enabled condition)
    uint32_t flagBits = *reinterpret_cast<uint32_t*>(&params->flags);
    if (flagBits & 0x80) {
        // Bit7 is 1 -> skip
        return;
    }

    // Only process if params->c > threshold
    if (DAT_00e2b1a4 < params->c) {
        float cVal = params->c;
        float tRatio = DAT_00e2b1a4 / (cVal - DAT_00e2b1a4);    // fVar4
        float dDiff = params->d - DAT_00e2b1a4;                // fVar7
        float eRatio = DAT_00e2b1a4 / params->e;                // fVar5

        float newA = params->a * tRatio * dDiff;                // fVar6

        // Update target fields
        obj->field_28 += (params->d - cVal) * eRatio;
        obj->field_1C += (newA - params->a) * eRatio;

        // Update input parameters
        params->a = newA;
        params->b = tRatio * params->b * dDiff;
    }
}