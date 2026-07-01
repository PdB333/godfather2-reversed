// FUNC_NAME: PathFollower::evaluateAtTime
// Function address: 0x0082fd00
// Role: Interpolates between two path keyframe points based on a given time-of-day input.
// The "this" object stores a list of time-keyed points (indices into mPoints array)
// and updates mCurrentIndex to the point immediately before the query time.

#include <cstdint>

// Forward declarations for external functions and globals.
extern float g_interpolationDefault;          // _DAT_00d5780c (e.g., 1.0f)
extern float g_floatAdjust;                   // DAT_00e44578 (likely 4294967296.0f)
extern int* g_defaultVtable;                  // PTR_LAB_00d73448

extern uint32_t findTimeIndex(const void* timeInput); // FUN_0082c690
extern void logError(void);                            // FUN_008334a0
extern void initializeFromPoint(void* point);          // FUN_0081f9f0 (takes PointData*)
extern void finalizeResult(void** temp);               // FUN_0081f9f0 (takes &local_60)
extern void interpolateBetweenPoints(void** output, float t, 
                                      const void* pointA, const void* pointB); // FUN_0082b890

// Per-point data structure (incomplete, only relevant offsets shown)
struct PointData {
    // +0x00 - +0x0F: other fields (not used)
    int hour;      // +0x10
    int minute;    // +0x14
    int second;    // +0x18
    // +0x1C - +0x4B: other fields
    int someValue; // +0x4C   (stored in final output)
};

// PathFollower class (partial structure)
class PathFollower {
public:
    // +0x00: vtable pointer (inherited)
    int mCurrentIndex;    // +0x04
    PointData** mPoints;  // +0x08  (array of pointers to PointData)
    int mNumPoints;       // +0x0C

    // Evaluate the path at the given time and fill the output structure.
    // 'outResult' receives the interpolated state (vtable at [0], value at [0x13]).
    // 'inTime' points to a 6‑uint structure (indices 3,4,5 are hour, minute, second).
    // 'outInterval' (optional) receives [prevIndex, nextIndex, interpolationFactor].
    int* evaluateAtTime(int* outResult, const int* inTime, uint32_t* outInterval);
};

int* PathFollower::evaluateAtTime(int* outResult, const int* inTime, uint32_t* outInterval)
{
    // Local temporary object used for interpolation output
    int* local_60;       // Will point to g_defaultVtable initially
    int  local_14;       // Final combined value (copied from PointData::someValue)
    int  local_5c, local_58, local_54, local_50, local_4c, local_48; // input time copy

    uint32_t uVar7 = findTimeIndex(inTime);

    if (uVar7 == 0xFFFFFFFF) {
        // Time not found – fill outInterval with error sentinel and log
        if (outInterval) {
            outInterval[0] = 0xFFFFFFFF;
            outInterval[1] = 0xFFFFFFFF;
            outInterval[2] = 0;
        }
        logError();
        local_60 = &g_defaultVtable;
        local_14 = 0;
    } else {
        // Valid time index found – update internal current index
        this->mCurrentIndex = uVar7;
        float fDefaultFactor = g_interpolationDefault; // saved for outInterval

        // Determine the next index (wrap around if at end)
        uint32_t uVar9 = (uVar7 < (uint32_t)(this->mNumPoints - 1)) ? (uVar7 + 1) : 0;

        PointData* pointA = this->mPoints[uVar7];
        PointData* pointB = this->mPoints[uVar9];

        // Convert point times to total seconds
        int totalSecondsA = pointA->hour * 3600 + pointA->minute * 60 + pointA->second;
        int totalSecondsQuery = inTime[3] * 3600 + inTime[4] * 60 + inTime[5];

        int timeDiff, totalTimeSpan;
        if (uVar9 == 0) {
            // Wrap case: treat pointB as next day
            int totalSecondsB = pointB->hour * 3600 + pointB->minute * 60 + pointB->second + 86400;
            if (totalSecondsQuery < totalSecondsA) {
                timeDiff = totalSecondsQuery + 86400 - totalSecondsA;
            } else {
                timeDiff = totalSecondsQuery - totalSecondsA;
            }
            totalTimeSpan = totalSecondsB - totalSecondsA;
        } else {
            int totalSecondsB = pointB->hour * 3600 + pointB->minute * 60 + pointB->second;
            timeDiff = totalSecondsQuery - totalSecondsA;
            totalTimeSpan = totalSecondsB - totalSecondsA;
        }

        if (totalTimeSpan == 0) {
            // No time span – no interpolation needed, use pointB directly
            if (outInterval) {
                outInterval[0] = uVar7;
                outInterval[1] = uVar9;
                outInterval[2] = (uint32_t)fDefaultFactor;
            }
            initializeFromPoint(pointB); // copies pointB’s data into the temporary output
            local_14 = pointB->someValue; // +0x4C
            local_60 = &g_defaultVtable;
        } else {
            // Compute interpolation factor t (with sign handling for float conversion)
            float fTimeDiff = (float)timeDiff;
            if (timeDiff < 0) {
                fTimeDiff += g_floatAdjust;
            }
            float fTimeSpan = (float)totalTimeSpan;
            if (totalTimeSpan < 0) {
                fTimeSpan += g_floatAdjust;
            }
            float t = fTimeDiff / fTimeSpan;

            if (outInterval) {
                outInterval[0] = uVar7;
                outInterval[1] = uVar9;
                outInterval[2] = (uint32_t)(fDefaultFactor - t);
            }

            // Perform interpolation between pointA and pointB
            interpolateBetweenPoints(&local_60, t, pointA, pointB);
        }

        // Copy the input time structure into local variables (if not already the same)
        if (&local_5c != inTime) {
            local_5c = inTime[0];
            local_58 = inTime[1];
            local_54 = inTime[2];
            local_50 = inTime[3];
            local_4c = inTime[4];
            local_48 = inTime[5];
        }
    }

    // Finalize the temporary result and write to the output structure
    finalizeResult(&local_60);
    outResult[0]  = (int)&g_defaultVtable;
    outResult[0x13] = local_14; // combined value from interpolation or pointB
    return outResult;
}