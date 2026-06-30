extern "C" void FUN_0040af70(unsigned int param_1, unsigned int /*param_2*/, float param_3)
{
    if (DAT_00e2e210 < param_3 * DAT_00e2ee80) {
        FUN_004ef1d0(
            1,
            static_cast<float>((param_1 >> 8) & 0xff) * DAT_00e44640,
            static_cast<float>((param_1 >> 16) & 0xff) * DAT_00e44640,
            static_cast<float>(param_1 >> 24) * DAT_00e44640,
            param_3 * DAT_00e2ee80
        );
    }
}