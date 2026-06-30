// FUNC_NAME: evaluateCurve (global function, likely from animation system)
// Address: 0x0057c390
// This function evaluates a curve at a given time, supporting multiple interpolation types.
// It takes an index, interpolation type, time, a data pointer (passed in EAX), and an output pointer (passed in ESI).
// The data pointer points to a buffer containing keyframe data in various formats.

enum InterpolationType {
    kLinear = 1,
    kCubic = 2,
    kUnknown3 = 3,
    kRawFloat = 4,
    kCompressed6 = 6,
    kCompressed7 = 7
};

// External globals
extern float g_constant1;          // DAT_00e445d0 (some scaling factor)
extern float g_constant2;          // DAT_00e2b1a4 (time offset)
extern float g_lookupTable[256];   // DAT_00e2c320 (lookup table for compressed values)

// Helper interpolation functions (addresses: 0x0057c110, 0x0057c160, 0x0057c1d0)
float linearInterpolate(float t);   // FUN_0057c110
float cubicInterpolate();           // FUN_0057c160 (no args? may use internal state)
float unknownInterpolate();         // FUN_0057c1d0 (no args? may use internal state)

// Helper to read a 3-byte little-endian integer and convert to float
inline float read3ByteAsFloat(const uint8_t* ptr) {
    uint32_t val = (uint32_t)ptr[0] | ((uint32_t)ptr[1] << 8) | ((uint32_t)ptr[2] << 16);
    return (float)(val << 8); // shift left by 8 (original code: (uint)*(uint3 *)(ptr) << 8)
}

void evaluateCurve(int index, int interpolationType, float time, const uint8_t* data, float* out) {
    switch (interpolationType) {
        case kLinear: {
            // Linear interpolation: evaluate at time and time+offset
            out[0] = linearInterpolate(time);
            float t2 = time + g_constant2;
            out[1] = linearInterpolate(t2);
            break;
        }
        case kCubic: {
            // Cubic interpolation (no time parameter? possibly uses internal state)
            out[0] = cubicInterpolate();
            out[1] = cubicInterpolate();
            break;
        }
        case kUnknown3: {
            // Unknown interpolation type
            out[0] = unknownInterpolate();
            out[1] = unknownInterpolate();
            break;
        }
        case kRawFloat: {
            // Direct float values from data buffer (4 bytes each)
            // Data at offset: data + 2 + index*4 and data + 6 + index*4
            const uint8_t* base = data + 2 + index * 4;
            // Reinterpret bytes as float (little-endian)
            float f0, f1;
            memcpy(&f0, base, 4);
            memcpy(&f1, base + 4, 4);
            out[0] = f0;
            out[1] = f1;
            break;
        }
        case kCompressed6:
        case kCompressed7: {
            // Compressed format: 3-byte integer + byte-indexed lookup
            float baseVal = read3ByteAsFloat(data + 2);   // from data+2 (3 bytes)
            float scale = read3ByteAsFloat(data + 5);     // from data+5 (3 bytes)
            float f0, f1;
            if (interpolationType == kCompressed6) {
                // Stride = 1 byte per index
                uint8_t idx0 = data[8 + index];
                uint8_t idx1 = data[9 + index];
                f0 = baseVal + g_lookupTable[idx0] * scale;
                f1 = baseVal + g_lookupTable[idx1] * scale;
            } else { // kCompressed7
                // Stride = 2 bytes per index
                uint8_t idx0 = data[8 + index * 2];
                uint8_t idx1 = data[9 + index * 2];
                uint8_t idx2 = data[10 + index * 2];
                uint8_t idx3 = data[11 + index * 2];
                // Note: original code uses g_constant1 for the second pair
                f0 = (g_lookupTable[idx0] + g_lookupTable[idx1] * g_constant1) * scale + baseVal;
                f1 = (g_lookupTable[idx2] + g_lookupTable[idx3] * g_constant1) * scale + baseVal;
            }
            out[0] = f0;
            out[1] = f1;
            break;
        }
        default:
            break;
    }
}