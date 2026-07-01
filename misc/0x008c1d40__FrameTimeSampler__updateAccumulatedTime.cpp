// FUNC_NAME: FrameTimeSampler::updateAccumulatedTime
// Address: 0x008c1d40
// Role: Samples elapsed time over multiple substeps, accumulates it to a running total, clamps the total to a valid range, and returns the accumulated time for this call.

#include <cstdint>

// Global time clamping constants (likely from .rdata)
extern const float frameTimeMin;  // DAT_00d7bcac
extern const float frameTimeMax;  // DAT_00d7bca8

// Forward declarations of helper functions (likely from engine layer)
int  getTimeStamp();           // FUN_006b1a40
void processSubstep();         // FUN_006b3220
void debugPrintTime(float, int); // FUN_00892490

class FrameTimeSampler {
public:
    // Offsets:
    // +0x104: accumulated frame time (float)
    // +0x118: number of substeps to sample (int)
    // +0x230: debug flag (int, nonzero enables debug output)

    int updateAccumulatedTime() {
        int accumulatedTime = 0;   // local_4, sum of substep times
        uint32_t substepCount = *(uint32_t*)(this + 0x118);

        if (substepCount > 0) {
            for (uint32_t i = 0; i < substepCount; i++) {
                int startTime = getTimeStamp();   // first call
                processSubstep();
                int endTime = getTimeStamp();     // second call
                accumulatedTime += (endTime - startTime);
            }
        }

        // Optional debug output
        if (*(int*)(this + 0x230) != 0) {
            debugPrintTime((float)accumulatedTime, 2);
        }

        // Add to running total and clamp
        float newTotal = *(float*)(this + 0x104) + (float)accumulatedTime;
        if (newTotal < frameTimeMin) {
            newTotal = frameTimeMin;
        } else if (newTotal > frameTimeMax) {
            newTotal = frameTimeMax;
        }
        *(float*)(this + 0x104) = newTotal;

        return accumulatedTime;
    }
};