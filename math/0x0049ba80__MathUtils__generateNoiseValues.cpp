// FUNC_NAME: MathUtils::generateNoiseValues
void MathUtils::generateNoiseValues(void* this, int unused, int* param_3)
{
    // Retreive initial noise sample (via XMM0 register return)
    float sample1;
    MathUtils::getNoiseSample();                 // FUN_0049b9e0
    sample1 = XMM0_return;                        // uVar1 = in_XMM0_Da

    // Retrieve second noise sample
    float sample2;                               // via XMM0
    MathUtils::getNoiseSample();                 // FUN_0049b9e0
    sample2 = XMM0_return;

    // Blend first two samples with flag=1, output stored via param_3
    MathUtils::interpolateNoise(sample2, sample1, 1, param_3); // FUN_0049bb20

    // Retrieve a third sample (used only to trigger state update?)
    float sample3;
    MathUtils::getNoiseSample();                 // FUN_0049b9e0
    sample3 = XMM0_return;

    // Reuse the first sample as both arguments for the second blend (flag=3)
    MathUtils::interpolateNoise(sample1, sample1, 3, param_3); // FUN_0049bb20 (degenerate pair)
}