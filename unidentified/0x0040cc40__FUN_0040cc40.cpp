extern "C" void FUN_0040cc40()
{
    if (unaff_ESI[5] != 0) {
        int queued = unaff_ESI[5];
        *reinterpret_cast<int*>(queued + 0x14) = *reinterpret_cast<int*>(queued + 0x10);
        *reinterpret_cast<int*>(queued + 0x18) = *reinterpret_cast<int*>(queued + 0x10);

        FUN_00ab4db0(&DAT_00e2ee68);

        queued = unaff_ESI[5];
        *reinterpret_cast<int*>(queued + 0x1C) = unaff_ESI[2];

        if (unaff_ESI[2] == 0) {
            unaff_ESI[3] = queued;
        }

        unaff_ESI[2] = queued;
        unaff_ESI[5] = 0;

        FUN_00ab4e70();
        FUN_00ab51e0(1);
    }
}