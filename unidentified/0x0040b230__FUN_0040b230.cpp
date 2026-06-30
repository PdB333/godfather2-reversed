extern "C" void FUN_0040b230(unsigned int param_1, unsigned int /*param_2*/, float param_3, float param_4, unsigned int param_5)
{
    float local_20;
    float local_1c;
    float local_18;
    const float local_14 = param_4 * param_3;

    if (DAT_00e2e210 < local_14) {
        local_20 = static_cast<float>((param_1 >> 8) & 0xff) * DAT_00e44640;
        local_1c = static_cast<float>((param_1 >> 16) & 0xff) * DAT_00e44640;
        local_18 = static_cast<float>(param_1 >> 24) * DAT_00e44640;

        FUN_005172c0(
            *(unsigned int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 4),
            param_5,
            DAT_00e39f98,
            DAT_00e445ac,
            0x3f800000,
            &local_20,
            0,
            0,
            0
        );
    }
}