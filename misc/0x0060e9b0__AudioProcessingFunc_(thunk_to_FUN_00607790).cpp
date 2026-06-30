// FUNC_NAME: AudioProcessingFunc (thunk to FUN_00607790)
// Address: 0x0060e9b0
// Role: Processes audio/sample data with optional divisor normalization and copies to global buffer.
// Likely part of EARS audio stream handling.

#include <stdint.h>

// Global variables (from data sections)
extern uint32_t gSampleRateDivisor; // DAT_00f15a70 - divisor for sample rate conversion
extern uint32_t gProcessedBuffer[14]; // DAT_011d9188 - destination buffer for processed data

// Helper functions (declared elsewhere)
extern int8_t someProcessingFunction(uint32_t* p1, uint32_t* p2, uint32_t* p3, uint32_t flag, uint32_t data); // FUN_006073e0
extern void finalProcessingFunction(uint32_t p3, uint32_t flag, uint32_t data); // FUN_00607730

void AudioProcessingFunc(uint32_t param1, uint32_t param2, uint32_t param3, uint32_t param4, uint32_t param5)
{
    int8_t result;
    uint32_t buffer[15]; // local stack buffer, filled by someProcessingFunction

    // Call helper with addresses of param1, param2, param3 (likely writes to them and/or buffer)
    result = someProcessingFunction(&param1, &param2, &param3, param4, param5);

    if (result != 0) {
        // If flag is zero and divisor > 1, divide first two buffer entries by divisor
        if ((char)param4 == 0 && gSampleRateDivisor > 1) {
            buffer[0] = buffer[0] / gSampleRateDivisor;
            buffer[1] = buffer[1] / gSampleRateDivisor;
        }

        // Copy 14 entries from buffer to global processed buffer
        for (int i = 0; i < 14; i++) {
            gProcessedBuffer[i] = buffer[i];
        }

        // Call final processing
        finalProcessingFunction(param3, param4, param5);
    }
}