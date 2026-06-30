undefined4 __thiscall FUN_00404280(int this_, undefined4 param_2, undefined4 param_3, undefined4 param_4)
{
    const int resolved = FUN_00405720(param_2, 0);
    if (resolved != 0) {
        undefined1* entryData = nullptr;

        if ((*(reinterpret_cast<byte*>(resolved + 10)) & 0x20) != 0) {
            entryData = *reinterpret_cast<undefined1**>(
                *reinterpret_cast<int*>(resolved + 0xc) * 0x10 + *reinterpret_cast<int*>(this_ + 0x154));

            if (entryData == nullptr) {
                entryData = &DAT_0120546e;
            }
        }

        return FUN_00403c40(resolved, param_3, entryData, param_4);
    }

    return 0;
}