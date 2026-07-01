// FUNC_NAME: DayNightController::computeTimeBlendFactors
// Function address: 0x00823910
// Computes two additive blend factors for dawn/dusk transitions given two time ranges.
// Structure offsets:
//   +0x14: m_startHours[0] (byte)
//   +0x15: m_startHours[1] (byte)
//   +0x16: m_startMinutes[0] (byte)
//   +0x17: m_startMinutes[1] (byte)
//   +0x18: m_durations[0] (byte) // duration in minutes
//   +0x19: m_durations[1] (byte)

extern bool g_dayNightEnabled;            // DAT_0112a53c
extern float g_maxTransitionFactor;       // DAT_00d5780c (usually 1.0f)
extern float g_dayLengthMinutes;          // DAT_00e44578 (1440.0f)

// Forward declaration for getting current time (assumed from global or system)
void getCurrentTimeHoursMinutes(int &outHours, int &outMinutes); // FUN_00826540

class DayNightController {
public:
    byte m_startHours[2];   // +0x14, +0x15
    byte m_startMinutes[2]; // +0x16, +0x17
    byte m_durations[2];    // +0x18, +0x19

    // Computes two blend factors for transitions.
    // param_2[0] receives the first transition factor (up to maxTransitionFactor)
    // param_2[1] receives the second transition factor (or a sentinel if inactive)
    void computeTimeBlendFactors(float *outFactors) {
        if (!g_dayNightEnabled) {
            outFactors[0] = 0.0f;
            outFactors[1] = 4.2039e-45f; // Very small sentinel indicating inactive
            return;
        }

        int currentHour, currentMinute;
        getCurrentTimeHoursMinutes(currentHour, currentMinute);

        // Current time in minutes from midnight
        int currentTimeMinutes = currentHour * 60 + currentMinute; // uVar1

        // First transition range
        int start1 = m_startMinutes[0] + m_startHours[0] * 60; // uVar2
        int end1 = start1 + m_durations[0]; // uVar6: start + duration

        float factor1 = 0.0f;
        if (start1 < end1 && start1 <= currentTimeMinutes) {
            int rawDiff = currentTimeMinutes - start1; // uVar1 - uVar2
            float diff = (float)rawDiff;
            if (rawDiff < 0) {
                diff += g_dayLengthMinutes; // wrap around if crossing midnight
            }
            int rangeLen = end1 - start1; // iVar7
            float rangeLenF = (float)rangeLen;
            if (rangeLen < 0) {
                rangeLenF += g_dayLengthMinutes;
            }
            float progress = diff / rangeLenF; // local_1c
            if (progress > 0.0f) {
                if (progress > g_maxTransitionFactor) {
                    progress = g_maxTransitionFactor;
                }
            } else {
                progress = 0.0f;
            }
            factor1 = progress;
        }

        // Second transition range
        int start2 = m_startMinutes[1] + m_startHours[1] * 60; // uVar2 (second)
        int end2 = start2 + m_durations[1]; // uVar6 (second)

        if (start2 < end2 && start2 <= currentTimeMinutes) {
            int rawDiff2 = currentTimeMinutes - start2; // uVar1 - uVar2
            float diff2 = (float)rawDiff2;
            if (rawDiff2 < 0) {
                diff2 += g_dayLengthMinutes;
            }
            int rangeLen2 = end2 - start2; // iVar7 (second)
            float rangeLenF2 = (float)rangeLen2;
            if (rangeLen2 < 0) {
                rangeLenF2 += g_dayLengthMinutes;
            }
            float progress2 = diff2 / rangeLenF2; // fVar3
            if (progress2 > 0.0f) {
                if (progress2 < g_maxTransitionFactor) {
                    outFactors[1] = 1.4013e-45f; // Sentinel for valid second factor
                    outFactors[0] = progress2;
                    return;
                } else {
                    outFactors[1] = 1.4013e-45f;
                    outFactors[0] = g_maxTransitionFactor;
                    return;
                }
            } else {
                outFactors[1] = 1.4013e-45f;
                outFactors[0] = 0.0f;
                return;
            }
        }

        // No second transition active; return first factor only
        outFactors[1] = 0.0f;
        outFactors[0] = factor1;
    }
};