// FUNC_NAME: UIRenderable::updateRectangles

#include <xmmintrin.h>

// Global constants: screen transform and clamp bounds
extern float g_screenScaleX;   // _DAT_0119d0b0
extern float g_screenScaleY;   // _DAT_0119d0b4
extern float g_screenScaleZ;   // _DAT_0119d0b8 (unused?)
extern float g_screenScaleW;   // DAT_0119d0bc? (unused?)
extern float g_screenOffsetX;  // DAT_0119d0c0
extern float g_screenOffsetY;  // _DAT_0119d0c4
extern float g_screenOffsetZ;  // _DAT_0119d0c8
extern float g_screenOffsetW;  // _DAT_0119d0cc

extern __m128 g_screenSizeMin; // _DAT_00e2b2d0
extern __m128 g_screenSizeMax; // _DAT_00e2b2e0
extern volatile bool g_useLinearTransform; // PTR_DAT_00f17650 (byte)

// Helper functions (extern declarations)
void FUN_005c8250(float* rectOut); // Resets rect to zero/identity
void FUN_005c8100(float* rectOut); // Copies from some source or initializes
void FUN_005c69d0(void* container, int param6, int param7, const float* rect);

// Struct representing a 4-float rectangle (left, top, right, bottom)
// The decompiled local arrays are 16-byte each, aligned for SSE
struct Rect {
    float left;
    float top;
    float right;
    float bottom;
};

// Function at address 0x005c8320
// this is passed as param_3
void UIRenderable::updateRectangles(int param4, int param6, int param7) {
    // Offset +4 from this: pointer to source rect data
    Rect* sourceRect = *(Rect**)((char*)this + 4);
    // Offset +0xc: some flag set to 0
    *(int*)((char*)this + 0xc) = 0;

    float left = sourceRect->left;
    float top = sourceRect->top;
    float right = sourceRect->right;
    float bottom = sourceRect->bottom;

    // Four temporary rectangles for quadrants/sorting
    Rect rects[4]; // local_50, local_40, local_30, local_20

    if (param4 == 0) {
        // Initialize all rects to zero
        for (int i = 0; i < 4; ++i)
            FUN_005c8250(&rects[i].left);
    } else {
        int index0, index1, index2, index3;
        // Determine ordering based on source rect orientation
        if (left <= right && top <= bottom) {
            // Normal orientation
            index0 = 0;
            index1 = 1;
            index2 = 2;
            index3 = 3;
        } else if (left > right || top > bottom) {
            // Inverted in one or both axes
            if (left > right && top > bottom) {
                // Both axes inverted
                index0 = 3;
                index1 = 2;
                index2 = 1;
                index3 = 0;
            } else if (left > right) {
                // Horizontally inverted
                index0 = 2;
                index1 = 3;
                index2 = 0;
                index3 = 1;
            } else {
                // Vertically inverted
                index0 = 1;
                index1 = 0;
                index2 = 3;
                index3 = 2;
            }
        } else {
            // The decompiled had nested if-else; fallback
            index0 = 0;
            index1 = 1;
            index2 = 2;
            index3 = 3;
        }
        // Initialize the four rects in the determined order
        FUN_005c8100(&rects[index0].left);
        FUN_005c8100(&rects[index1].left);
        FUN_005c8100(&rects[index2].left);
        FUN_005c8100(&rects[index3].left);
    }

    // Optionally apply linear transformation (screen offset and scale)
    if (!g_useLinearTransform) {
        __m128 scale = _mm_set_ps(0.0f, g_screenScaleZ, g_screenScaleY, g_screenScaleX);
        __m128 offset = _mm_set_ps(0.0f, g_screenOffsetZ, g_screenOffsetY, g_screenOffsetX);

        // Transform each rect
        for (int i = 0; i < 4; ++i) {
            __m128 r = _mm_loadu_ps(&rects[i].left); // load rect (4 floats)
            r = _mm_add_ps(_mm_mul_ps(r, scale), offset);
            r = _mm_min_ps(r, g_screenSizeMax);
            r = _mm_max_ps(r, g_screenSizeMin);
            _mm_storeu_ps(&rects[i].left, r);
        }
    }

    // Final call with the first rect (rects[0]) and extra parameters
    FUN_005c69d0(this, param6, param7, &rects[0].left);
}