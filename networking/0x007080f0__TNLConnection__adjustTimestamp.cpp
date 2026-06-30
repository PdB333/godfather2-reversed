// FUNC_NAME: TNLConnection::adjustTimestamp
// Address: 0x007080f0
// Role: Adjusts a 64-bit fixed-point timestamp (32.32 format) based on global time synchronization parameters.
// Copies input timestamp to output, then conditionally adjusts the high (integer) part using a timer expiry and threshold check.

#include <cstdint>

// Global timing constants (inferred from data refs)
extern float g_currentTimeFloat;      // _DAT_00d5780c
extern float g_baseTimeFloat;         // DAT_00d5779c
extern float g_timeThreshold;         // _DAT_00d577a0
extern float g_timeScale;             // DAT_00e44634
extern float g_timeOffset;            // DAT_00d58cbc

// Helper functions (unknown implementations)
void interpolateFixedPoint(float *out, float *in, int mode, int flags, int zero1, int zero2); // FUN_005425d0
int  checkTimerExpired(char *buffer, char *flags); // FUN_009e69d0

// Reconstructed function
void TNLConnection::adjustTimestamp(uint64_t *inputTimestamp, uint64_t *outputTimestamp) {
    // Read the 64-bit fixed-point timestamp (32.32: high = integer seconds, low = fractional)
    uint64_t raw = *inputTimestamp;
    uint32_t frac = (uint32_t)(raw & 0xFFFFFFFFu);
    uint32_t intPart = (uint32_t)(raw >> 32);
    
    // Global current time as float (likely seconds)
    float currentFloat = g_currentTimeFloat;
    // Global base time offset
    float baseFloat = g_baseTimeFloat;
    
    // Copy input to output
    *outputTimestamp = raw;
    // Redundant copy of high part (keeps same semantics)
    *(uint32_t *)((uint8_t *)outputTimestamp + 4) = *(uint32_t *)((uint8_t *)inputTimestamp + 4);
    
    // Convert high part to float and compute relative time
    float intPartFloat = (float)intPart;
    float relativeTime = intPartFloat - baseFloat; // local_dc
    
    // Build temporary structures for interpolation? (Signature approach)
    // local_d0, local_e0 likely hold (frac, currentFloat) pairs.
    float tempA[4]; // emulating local_d0, local_d4, local_cc, local_c8 layout
    float tempB[4]; // emulating local_e0, etc.
    
    tempA[0] = (float)frac;               // local_d0 = low part reinterpreted as float?
    tempA[1] = currentFloat;              // local_d4
    tempA[2] = intPartFloat + currentFloat; // local_cc
    tempA[3] = (float)intPart;            // local_c8  (actually intPartFloat again)
    
    tempB[0] = (float)frac;               // local_e0
    tempB[1] = currentFloat;              // local_d4? Actually not sure about the mapping.
    // Other fields set but not fully used? The call passes 2 as mode, 0x80000000 flags.
    
    interpolateFixedPoint(tempA, tempB, 2, 0x80000000, 0, 0);
    
    // Timer expiry check
    char timerBuffer[92]; // local_60
    char timerStruct[16]; // local_c0
    int timerExpired = checkTimerExpired(timerBuffer, timerStruct);
    bool condition = (timerExpired != 0) && (g_timeThreshold < currentFloat);
    
    if (condition) {
        // Compute new high part as float and overwrite output's high 32-bit field
        float newIntPart = (intPartFloat + currentFloat) - (currentFloat * g_timeScale) + g_timeOffset;
        *(float *)((uint8_t *)outputTimestamp + 4) = newIntPart;
    }
}