// FUNC_NAME: Vector4::transformAndClamp
// Function address: 0x005c48a0
// Transforms a 4D vector by scaling, offsetting, then clamping to a range.
// Uses SSE intrinsics for SIMD operations.
// The transformation is only applied if a global flag (likely debug or enable) is false.

#include <xmmintrin.h> // for SSE intrinsics

// Global constants (scale factors, offsets, clamp bounds)
extern float gScaleX;   // _DAT_0119d0b0
extern float gScaleY;   // _DAT_0119d0b4
extern float gScaleZ;   // _DAT_0119d0b8
extern float gScaleW;   // DAT_0119d0bc
extern float gOffsetX;  // DAT_0119d0c0
extern float gOffsetY;  // _DAT_0119d0c4
extern float gOffsetZ;  // _DAT_0119d0c8
extern float gOffsetW;  // _DAT_0119d0cc
extern __m128 gClampMax; // _DAT_00e2b2e0 (upper bound)
extern __m128 gClampMin; // _DAT_00e2b2d0 (lower bound)
extern volatile char* gTransformEnabled; // PTR_DAT_00f17650 (pointer to flag)

class Vector4 {
public:
    float x, y, z, w; // 16-byte aligned typically

    void transformAndClamp() {
        // Check if transformation is enabled (flag non-zero means skip)
        if (*gTransformEnabled != '\0') {
            return;
        }

        // Load current vector components
        __m128 vec = _mm_loadu_ps(&x); // or aligned load if guaranteed

        // Scale each component
        __m128 scale = _mm_set_ps(gScaleW, gScaleZ, gScaleY, gScaleX);
        vec = _mm_mul_ps(vec, scale);

        // Store scaled values back (temporary, but original code does this)
        _mm_storeu_ps(&x, vec);

        // Add offset
        __m128 offset = _mm_set_ps(gOffsetW, gOffsetZ, gOffsetY, gOffsetX);
        vec = _mm_add_ps(vec, offset);

        // Clamp to [gClampMin, gClampMax]
        vec = _mm_min_ps(vec, gClampMax); // ensure <= max
        vec = _mm_max_ps(vec, gClampMin); // ensure >= min

        // Store final result
        _mm_storeu_ps(&x, vec);
    }
};