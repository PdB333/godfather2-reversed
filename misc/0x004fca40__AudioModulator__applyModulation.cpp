// FUNC_NAME: AudioModulator::applyModulation
void __thiscall AudioModulator::applyModulation(AudioModulator* this, int index, AudioSourceParams* sourceParams, uint8_t* initFlag)
{
    float base = sourceParams->baseValue;                                                 // +0x18
    float scaledMod = (float)(this->byteModTable[0x194 + index]) * base;                  // +0x194 array of bytes
    float sum = base + scaledMod;

    if (*(initFlag + 1) == 0) {
        FUN_00535450(0, *initFlag);                                                        // possibly initialization
        *(initFlag + 1) = 1;
    }

    // Allocate structure (size = 5 * 4 = 20? but we write more later – maybe a larger block)
    float* buffer = (float*)FUN_0060cd00(5, 4, 0, 1, 0);
    if (buffer != nullptr) {
        float constant = DAT_00e2b1a4;                                                     // global constant (maybe 1.0f)
        float zero = 0.0f;

        FUN_00414aa0();                                                                    // math helper (e.g., identity reset)
        // First row/group
        buffer[0] = 0.0f;
        buffer[1] = 0.0f;
        buffer[2] = 0.0f;
        buffer[3] = constant;
        buffer[4] = sum;
        buffer[5] = zero;
        buffer[6] = 0.0f;
        buffer[7] = 0.0f;

        FUN_00414aa0();
        // Second row/group
        buffer[8]  = 0.0f;
        buffer[9]  = 0.0f;
        buffer[10] = 0.0f;
        buffer[11] = constant;
        buffer[12] = scaledMod;
        buffer[13] = zero;
        buffer[14] = 0.0f;
        buffer[15] = 0.0f;

        FUN_00414aa0();
        // Third row/group
        buffer[16] = 0.0f;
        buffer[17] = 0.0f;
        buffer[18] = 0.0f;
        buffer[19] = constant;
        buffer[20] = sum;
        buffer[21] = constant;    // note: uses constant again for this position
        buffer[22] = 0.0f;
        buffer[23] = 0.0f;

        FUN_00414aa0();
        // Fourth row/group
        buffer[24] = 0.0f;
        buffer[25] = 0.0f;
        buffer[26] = 0.0f;
        buffer[27] = constant;
        buffer[28] = scaledMod;
        buffer[29] = constant;
        buffer[30] = 0.0f;
        buffer[31] = 0.0f;

        FUN_0060cde0();                                                                    // push buffer to audio command queue
    }
}