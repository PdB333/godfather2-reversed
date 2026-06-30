// FUN_004ef1d0: SafeAreaCalibration::updateCalibration

#include <cstdint>

// Global constants and state (from the game's data section)
extern float g_calibrationThreshold;      // DAT_00e2e780
extern float g_screenMinX;                // DAT_012058d0 (lower bound)
extern float g_screenMaxX;                // DAT_00f15988 (upper bound)
extern float g_screenMinY;                // DAT_012058d0? actually reused, but likely separate
extern float g_screenMaxY;                // DAT_00f15988? also reused
extern int32_t g_calibStateA;            // _DAT_011f3a30
extern int32_t g_calibStateB;            // _DAT_011f39f4
extern int32_t g_calibStateC;            // _DAT_011f3a3c
extern int32_t g_calibStateD;            // _DAT_011f3a38
extern int32_t g_calibStateE;            // _DAT_011f3a14
extern int32_t g_calibStateF;            // _DAT_011f3a44
extern float g_calibrationMaxClamp;       // DAT_00e2cd54
extern float g_calibrationMultiplier;     // DAT_00e2b04c
extern uint32_t g_calibrationColor;       // DAT_00e2eff4 (ARGB color)
extern float g_calibrationOffset;         // DAT_00e2b1a4

// External functions (stubs – actual signatures may vary)
extern void FUN_00530c90();   // e.g., beginFrame() or something
extern void FUN_005311d0();   // e.g., endDraw()
extern void FUN_00530a60();   // e.g., flush
extern void *FUN_0060cd00(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e); // allocate temporary vertex buffer
extern void FUN_0060cde0();   // submit draw call
extern void FUN_00612e00();   // reset or clear state
extern void FUN_00417cf0(int32_t a, int32_t b, int32_t c);  // set calibration parameters

void SafeAreaCalibration::updateCalibration(char isActive) {
    // check if current progress (at +0x0C) exceeds threshold
    if (g_calibrationThreshold < *(float *)((int)this + 0x0C) || 
        g_calibrationThreshold == *(float *)((int)this + 0x0C)) {
        // First phase: set up left/top boundaries
        if (isActive != 0) {
            if (g_screenMinX < 22) g_screenMinX = 22;   // clamp min to 22
            if (22 < g_screenMaxX) g_screenMaxX = 22;   // clamp max to 22
            g_calibStateA = 1;
            if (g_screenMinX < 7) g_screenMinX = 7;
            if (7 < g_screenMaxX) g_screenMaxX = 7;
            g_calibStateB = 0;
            if (g_screenMinX < 25) g_screenMinX = 25;
            if (25 < g_screenMaxX) g_screenMaxX = 25;
            g_calibStateC = 5;
            if (g_screenMinX < 24) g_screenMinX = 24;
            if (24 < g_screenMaxX) g_screenMaxX = 24;
            g_calibStateD = 0;
            if (g_screenMinX < 15) g_screenMinX = 15;
            if (15 < g_screenMaxX) g_screenMaxX = 15;
            g_calibStateE = 0;
            if (g_screenMinX < 27) g_screenMinX = 27;
            if (26 < g_screenMaxX) g_screenMaxX = 27;   // note: upper bound uses 26 for comparison, but sets to 27
            g_calibStateF = 1;
            FUN_00417cf0(1, 2, 1);
        }

        // Update rendering pipeline
        FUN_00530c90();
        FUN_005311d0();
        FUN_00530a60();

        // Compute rectangle dimensions based on progress
        float progress = *(float *)((int)this + 0x0C);
        float clampedProgress = 0.0f;
        if (0.0f < progress && progress < g_calibrationMaxClamp) {
            clampedProgress = progress;
        }
        float rectSize = clampedProgress * g_calibrationMultiplier;
        float offset = g_calibrationOffset;

        // Draw first rectangle (left/top)
        uint32_t *rect1 = (uint32_t*)FUN_0060cd00(5, 4, 0, 1, 0);
        uint32_t color = g_calibrationColor;
        float rectSizeOff = rectSize - offset;
        if (rect1 != nullptr) {
            rect1[0] = color;          // vertex 0 color (or top-left color?)
            rect1[1] = color;          // vertex 1 color
            rect1[2] = offset;         // x1 (left)
            rect1[3] = color;          // vertex 2 color
            rect1[4] = color;          // vertex 3 color
            rect1[5] = rectSizeOff;    // x2 (right) or y? unclear
            rect1[6] = offset;         // y1 (top)
            rect1[7] = rectSizeOff;    // y2 (bottom)
            FUN_0060cde0();
        }

        // Draw second rectangle (right/bottom)
        uint32_t *rect2 = (uint32_t*)FUN_0060cd00(5, 4, 0, 1, 0);
        float negRectSize = g_calibrationOffset - rectSize;
        if (rect2 != nullptr) {
            rect2[0] = color;
            rect2[1] = negRectSize;    // negative offset for opposite side
            rect2[2] = offset;
            rect2[3] = negRectSize;
            rect2[4] = color;
            rect2[5] = offset;
            rect2[6] = offset;
            rect2[7] = offset;
            FUN_0060cde0();
        }

        // Reset some draw state
        FUN_00612e00();
        g_someFlag1 = 0;   // these were zeroed: DAT_01219950, DAT_01219954, etc.
        g_someFlag2 = 0;
        g_otherFlag1 = 0;
        g_otherFlag2 = 0;

        // Second phase: set up right/bottom boundaries
        if (isActive != 0) {
            if (g_screenMinX < 22) g_screenMinX = 22;
            if (22 < g_screenMaxX) g_screenMaxX = 22;
            g_calibStateA = 1;
            if (g_screenMinX < 7) g_screenMinX = 7;
            if (7 < g_screenMaxX) g_screenMaxX = 7;
            g_calibStateB = 1;   // different from first phase
            if (g_screenMinX < 25) g_screenMinX = 25;
            if (25 < g_screenMaxX) g_screenMaxX = 25;
            g_calibStateC = 7;   // different
            if (g_screenMinX < 24) g_screenMinX = 24;
            if (24 < g_screenMaxX) g_screenMaxX = 24;
            g_calibStateD = 0;
            if (g_screenMinX < 15) g_screenMinX = 15;
            if (15 < g_screenMaxX) g_screenMaxX = 15;
            g_calibStateE = 0;
            if (g_screenMinX < 27) g_screenMinX = 27;
            if (26 < g_screenMaxX) g_screenMaxX = 27;
            g_calibStateF = 0;   // different
            FUN_00417cf0(1, 5, 6);
        }
    }
    return;
}