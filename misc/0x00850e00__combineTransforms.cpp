// FUNC_NAME: combineTransforms
void combineTransforms(uint param_1, uint param_2, uint param_3, uint param_4, uint param_5)
{
    // Temporary buffer (44 bytes = 0x2C) – likely stores an intermediate transform/matrix
    byte tempBuffer[44];

    // Combine param_4 and param_2 into tempBuffer
    FUN_00850be0(param_4, param_2, tempBuffer);

    // Combine param_1 and param_3, using tempBuffer as additional input, result stored via param_5
    FUN_00850d00(param_1, param_3, tempBuffer, param_5);
}