// 0x00409f80
// Frame-timing update for The Godfather II (EA / EARS engine).
//
// The function always refreshes the high-resolution performance-counter delta.
// Only when the incoming message is iMsgSystemTick does it advance the frame
// pacing state and publish the derived timing / profiling accumulators.

#include <Windows.h>
#include <mmsystem.h>

#include <cmath>
#include <cstdint>

struct FrameTimerState
{
    void* vtable;                 // 0x00
    std::uint32_t unknown_04;     // 0x04
    std::uint32_t unknown_08;     // 0x08
    std::uint32_t unknown_0C;     // 0x0C
    std::uint32_t lastTickMs;     // 0x10
    std::uint32_t targetTickMs;   // 0x14
    float fractionalMs;           // 0x18

    void __thiscall onSystemTick(const std::uint32_t* messageId);
};

extern "C" {
    // High-resolution performance counter tracking.
    extern std::uint32_t g_LastQpcLow;           // DAT_01205240
    extern std::uint32_t g_LastQpcHigh;          // DAT_01205244
    extern float g_QpcDeltaSeconds;              // DAT_01205218
    extern float g_QpcToSeconds;                 // DAT_01163ec8

    // Message id used by the engine's system-tick event.
    extern std::uint32_t g_SystemTickMessageId;  // DAT_01206940

    // Global timing mode and pacing parameters.
    extern unsigned char g_TimingEnabled;        // DAT_0110accb
    extern float g_TimeScale;                    // DAT_01206a30
    extern float g_SecondsPerMs;                // DAT_00e2e210
    extern float g_DefaultStepBudgetMs;         // DAT_00e2b1a4
    extern float g_AutoStepClampScale;          // DAT_00e2dd14
    extern float g_FrameBiasMs;                 // DAT_00e2cd54
    extern float g_MinStepMs;                   // DAT_012067fc
    extern std::uint32_t g_MaxAutoStepMs;       // DAT_012067f0
    extern std::uint32_t g_MinAutoStepMs;       // DAT_012067f4
    extern std::uint32_t g_FixedStepMode;       // DAT_0110ae75
    extern std::uint32_t g_MaxFixedSteps;       // DAT_0110ae7c
    extern float g_FixedStepScale;              // DAT_0110ae80
    extern std::uint32_t g_FrameRateDivisor;    // DAT_0110ae4c

    // Variable-step clamp state.
    extern float g_MaxAutoStepBudgetMs;         // DAT_01225d48
    extern std::uint32_t g_MaxAutoStepBudgetInit; // DAT_01225d4c

    // Derived timing accumulators.
    extern std::uint32_t g_SimulatedMs;         // DAT_01205210
    extern std::uint32_t g_StepCount;            // DAT_01205208
    extern float g_SimulatedSeconds;             // DAT_01205214
    extern std::uint32_t g_UpdateCount;          // DAT_0120521c
    extern std::uint32_t g_FrameUpdateCount;     // DAT_01205220
    extern std::uint32_t g_FrameSkewMs;          // DAT_0120522c
    extern std::uint32_t g_LastStepCount;        // DAT_01205238
    extern std::uint32_t g_ProfileAccumulatorLo; // DAT_01205230
    extern std::uint32_t g_ProfileAccumulatorHi; // DAT_01205234
    extern std::uint32_t g_ProfileGate;          // DAT_01205254
    extern float g_CurrentStepSeconds;           // DAT_01206800
    extern float g_ScaledFrameMs;                // DAT_012067e8
    extern std::uint32_t g_ProfileFrameMs;       // DAT_01206804
    extern std::uint32_t g_ProfileSampleMs;      // DAT_01205224
    extern float g_ProfileSampleSeconds;         // DAT_01205228

    extern std::uint64_t FUN_00b9a1f6(void);
}

static inline std::uint64_t PackQpc(const LARGE_INTEGER& value)
{
    return static_cast<std::uint64_t>(value.QuadPart);
}

static inline float SignedToFloat(std::uint32_t value)
{
    return static_cast<float>(static_cast<std::int32_t>(value));
}

static inline std::uint32_t RoundToU32(float value)
{
    return static_cast<std::uint32_t>(std::lround(value));
}

static inline std::uint32_t RoundToU32(double value)
{
    return static_cast<std::uint32_t>(std::lround(value));
}

void __thiscall FrameTimerState::onSystemTick(const std::uint32_t* messageId)
{
    LARGE_INTEGER qpcNow{};
    QueryPerformanceCounter(&qpcNow);

    const std::uint64_t currentQpc = PackQpc(qpcNow);
    const std::uint64_t previousQpc =
        (static_cast<std::uint64_t>(g_LastQpcHigh) << 32) | g_LastQpcLow;
    const std::uint64_t qpcDelta = currentQpc - previousQpc;

    g_LastQpcLow = static_cast<std::uint32_t>(currentQpc);
    g_LastQpcHigh = static_cast<std::uint32_t>(currentQpc >> 32);
    g_QpcDeltaSeconds = static_cast<float>(static_cast<double>(qpcDelta) * g_QpcToSeconds);

    // Ignore all other messages. The tick state is still kept current above so
    // callers always get a fresh performance-counter delta.
    if (*messageId != g_SystemTickMessageId)
    {
        return;
    }

    TIMECAPS caps{};
    timeGetDevCaps(&caps, sizeof(caps));
    timeBeginPeriod(caps.wPeriodMin);

    const DWORD currentTickMs = timeGetTime();

    timeEndPeriod(caps.wPeriodMin);

    float stepBudgetMs = g_TimeScale;
    std::uint32_t stepCount = 0;

    if (g_TimingEnabled == '\0')
    {
        // If the timing system is disabled, resync the object to wall-clock
        // time and clear the fractional carry.
        lastTickMs = currentTickMs;
        targetTickMs = currentTickMs;
        fractionalMs = 0.0f;
        return;
    }

    const std::uint32_t maxAllowedTickMs = currentTickMs + g_MaxAutoStepMs;
    const std::uint32_t minAllowedTickMs = currentTickMs - g_MinAutoStepMs;

    if (g_FixedStepMode == '\0')
    {
        // Variable-step mode.
        // The engine advances by the elapsed budget, but clamps large jumps to
        // avoid a sudden simulation spike when the process stalls.
        if ((g_MaxAutoStepBudgetInit & 1U) == 0)
        {
            g_MaxAutoStepBudgetMs = g_TimeScale * g_AutoStepClampScale;
            g_MaxAutoStepBudgetInit |= 1U;
        }

        stepBudgetMs = g_DefaultStepBudgetMs;
        if (targetTickMs < currentTickMs)
        {
            const int overdueMs = static_cast<int>(currentTickMs - targetTickMs);
            float overdueBudgetMs = static_cast<float>(overdueMs);
            if (overdueMs < 0)
            {
                overdueBudgetMs += DAT_00e44578;
            }
            overdueBudgetMs -= fractionalMs;
            if (1.0f <= overdueBudgetMs)
            {
                stepBudgetMs = overdueBudgetMs;
            }
        }

        if (g_MaxAutoStepBudgetMs < stepBudgetMs)
        {
            stepBudgetMs = g_MaxAutoStepBudgetMs;
        }

        const float advancedMs = stepBudgetMs + fractionalMs;
        const std::uint32_t wholeMs = RoundToU32(advancedMs);

        targetTickMs += wholeMs;

        float wholeMsAsFloat = static_cast<float>(static_cast<std::int32_t>(wholeMs));
        if (static_cast<std::int32_t>(wholeMs) < 0)
        {
            wholeMsAsFloat += DAT_00e44578;
        }
        fractionalMs = advancedMs - wholeMsAsFloat;

        if (targetTickMs > maxAllowedTickMs)
        {
            targetTickMs = maxAllowedTickMs;
        }

        if (targetTickMs < minAllowedTickMs)
        {
            targetTickMs = minAllowedTickMs;
            fractionalMs = 0.0f;
        }

        g_FrameSkewMs = targetTickMs - currentTickMs;

        const std::uint32_t roundedBudgetMs = RoundToU32(stepBudgetMs);
        stepCount = roundedBudgetMs;
        g_StepCount += roundedBudgetMs;

        float stepCountAsFloat = static_cast<float>(static_cast<std::int32_t>(g_StepCount));
        if (static_cast<std::int32_t>(g_StepCount) < 0)
        {
            stepCountAsFloat += DAT_00e44578;
        }

        g_CurrentStepSeconds = stepBudgetMs * g_SecondsPerMs;
        g_SimulatedMs = g_StepCount;
        g_SimulatedSeconds = stepCountAsFloat / g_FrameRateDivisor;
    }
    else
    {
        // Fixed-step mode.
        // Convert elapsed time into a bounded step count, then advance the
        // simulation by that many discrete ticks.
        const std::uint32_t previousTickMs = targetTickMs;
        float elapsedMs = 0.0f;
        if (previousTickMs < currentTickMs)
        {
            const int deltaMs = static_cast<int>(currentTickMs - previousTickMs);
            elapsedMs = static_cast<float>(deltaMs);
            if (deltaMs < 0)
            {
                elapsedMs += DAT_00e44578;
            }
            elapsedMs -= fractionalMs;
        }

        if (elapsedMs < DAT_012067fc)
        {
            float previousTickAsFloat = static_cast<float>(static_cast<std::int32_t>(previousTickMs));
            if (static_cast<std::int32_t>(previousTickMs) < 0)
            {
                previousTickAsFloat += DAT_00e44578;
            }

            float currentClampAsFloat = static_cast<float>(static_cast<std::int32_t>(maxAllowedTickMs));
            if (static_cast<std::int32_t>(maxAllowedTickMs) < 0)
            {
                currentClampAsFloat += DAT_00e44578;
            }

            if (previousTickAsFloat + DAT_012067fc <= currentClampAsFloat)
            {
                elapsedMs = DAT_012067fc;
            }
        }

        if (elapsedMs / g_TimeScale <= 0.0f)
        {
            stepCount = 1;
        }
        else
        {
            stepCount = RoundToU32(static_cast<double>(elapsedMs / g_TimeScale) +
                                   static_cast<double>(DAT_00e2cd54));
            if (g_MaxFixedSteps < stepCount)
            {
                stepCount = g_MaxFixedSteps;
            }
            if (stepCount == 0)
            {
                stepCount = 1;
            }
        }

        const float stepCountAsFloat = static_cast<float>(static_cast<std::int32_t>(stepCount));
        const float advancedMs = stepCountAsFloat * g_TimeScale + fractionalMs;
        const std::uint32_t wholeMs = static_cast<std::uint32_t>(advancedMs);

        g_LastStepCount = stepCount;
        targetTickMs += wholeMs;
        fractionalMs = advancedMs - static_cast<float>(wholeMs);

        if (targetTickMs < minAllowedTickMs)
        {
            targetTickMs = minAllowedTickMs;
            fractionalMs = 0.0f;
        }

        g_StepCount += stepCount;
        g_FrameSkewMs = targetTickMs - currentTickMs;

        g_SimulatedMs = RoundToU32(static_cast<double>(g_TimeScale) *
                                   static_cast<double>(g_StepCount) +
                                   static_cast<double>(DAT_00e447f8));

        float stepTotalAsFloat = static_cast<float>(static_cast<std::int32_t>(g_StepCount));
        if (static_cast<std::int32_t>(g_StepCount) < 0)
        {
            stepTotalAsFloat += DAT_00e44578;
        }
        g_SimulatedSeconds = stepTotalAsFloat / g_FrameRateDivisor;
        g_CurrentStepSeconds = stepCountAsFloat * g_TimeScale * g_SecondsPerMs;
    }

    // Global frame counter used by the engine's timing and stats code.
    g_UpdateCount += 1;

    if (g_ProfileGate != 1)
    {
        // The original function keeps extra profiling state here. The x87
        // output is awkward, but the intent is clear: accumulate a 64-bit
        // timing sample and publish derived values for frame pacing telemetry.
        const float scaledFrameMs = g_FixedStepScale * g_CurrentStepSeconds;
        const std::uint64_t telemetrySample = FUN_00b9a1f6();
        const std::uint64_t profileAccumulator =
            (static_cast<std::uint64_t>(g_ProfileAccumulatorHi) << 32) |
            g_ProfileAccumulatorLo;
        const std::uint64_t updatedProfileAccumulator = profileAccumulator + telemetrySample;

        g_ProfileAccumulatorLo = static_cast<std::uint32_t>(updatedProfileAccumulator);
        g_ProfileAccumulatorHi = static_cast<std::uint32_t>(updatedProfileAccumulator >> 32);
        g_ScaledFrameMs = scaledFrameMs;

        if (g_FixedStepMode != '\0')
        {
            stepCountAsFloat = static_cast<float>(static_cast<std::int32_t>(stepCount));
            if (static_cast<std::int32_t>(stepCount) < 0)
            {
                stepCountAsFloat += DAT_00e44578;
            }

            g_FrameUpdateCount += 1;
            g_ProfileFrameMs = RoundToU32(static_cast<double>(stepCountAsFloat) *
                                          static_cast<double>(g_FixedStepScale));
            lastTickMs = currentTickMs;
            return;
        }

        const std::uint64_t dividedSample = telemetrySample / 1000ULL;
        g_FrameUpdateCount += 1;
        g_ProfileSampleMs = RoundToU32(static_cast<double>(dividedSample));
        g_ProfileSampleSeconds = static_cast<float>(dividedSample);
        lastTickMs = currentTickMs;
        return;
    }

    // When the profile gate is closed, only resync the timer object.
    targetTickMs = currentTickMs;
    fractionalMs = 0.0f;
    lastTickMs = currentTickMs;
}
