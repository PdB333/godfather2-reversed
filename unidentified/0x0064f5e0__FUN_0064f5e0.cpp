extern "C" void FUN_0064f5e0()
{
    if (*reinterpret_cast<int*>(unaff_ESI + 0x210) == 0) {
        const auto allocation = FUN_009c8e80(0x1000);
        *reinterpret_cast<undefined4*>(unaff_ESI + 0x210) = allocation;

        int offset = 0;
        do {
            *reinterpret_cast<undefined4*>(*reinterpret_cast<int*>(unaff_ESI + 0x210) + offset) = 0;
            offset = offset + 4;
        } while (offset < 0x1000);
    }
}