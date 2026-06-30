extern "C" void FUN_0040aff0(unsigned int param_1, unsigned char param_2, float param_3)
{
    const float fVar1 = static_cast<float>(param_2) * param_3 * DAT_00e44640;

    if (DAT_00e2e210 < fVar1) {
        FUN_004eec40(
            static_cast<float>((param_1 >> 8) & 0xff) * DAT_00e44640,
            static_cast<float>((param_1 >> 16) & 0xff) * DAT_00e44640,
            static_cast<float>(param_1 >> 24) * DAT_00e44640,
            fVar1
        );
    }
}