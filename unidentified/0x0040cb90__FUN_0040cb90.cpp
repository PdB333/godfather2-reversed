extern "C" void FUN_0040cb90()
{
    if (unaff_ESI[4] != 0) {
        FUN_00ab4db0(&DAT_00e2ee68);

        int queued = unaff_ESI[4];
        *reinterpret_cast<int*>(queued + 0x1C) = 0;

        if (unaff_ESI[1] == 0) {
            unaff_ESI[0] = queued;
        } else {
            *reinterpret_cast<int*>(unaff_ESI[1] + 0x1C) = queued;
        }

        unaff_ESI[1] = queued;
        unaff_ESI[4] = 0;

        FUN_00ab4e70();
        FUN_00ab51e0(1);
    }
}