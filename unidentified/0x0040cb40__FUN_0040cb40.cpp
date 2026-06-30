extern "C" int FUN_0040cb40(char param_1)
{
    if (param_1 != '\0') {
        FUN_00ab5130(&DAT_00e2ee68);
    }

    FUN_00ab4db0(&DAT_00e2ee68);

    int previous = *reinterpret_cast<int*>(unaff_ESI + 0x08);
    if (previous != 0) {
        if (*reinterpret_cast<int*>(unaff_ESI + 0x0C) == previous) {
            *reinterpret_cast<int*>(unaff_ESI + 0x0C) = 0;
        }

        *reinterpret_cast<int*>(unaff_ESI + 0x08) = *reinterpret_cast<int*>(previous + 0x1C);
    }

    *reinterpret_cast<int*>(unaff_ESI + 0x10) = previous;
    FUN_00ab4e70();
    return *reinterpret_cast<int*>(unaff_ESI + 0x10);
}