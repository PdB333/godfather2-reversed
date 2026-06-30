extern "C" int FUN_0040cbe0(char param_1)
{
    if (param_1 != '\0') {
        FUN_00ab5130(&DAT_00e2ee68);
    }

    FUN_00ab4db0(&DAT_00e2ee68);

    int queued = unaff_ESI[0];
    if (queued != 0) {
        if (unaff_ESI[1] == queued) {
            unaff_ESI[1] = 0;
        }

        unaff_ESI[0] = *reinterpret_cast<int*>(queued + 0x1C);
    }

    unaff_ESI[5] = queued;
    FUN_00ab4e70();
    return unaff_ESI[5];
}