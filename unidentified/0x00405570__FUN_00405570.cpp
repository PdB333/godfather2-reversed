void __thiscall FUN_00405570(void* this_, void* param_1)
{
    auto* const self = static_cast<std::uint32_t*>(this_);
    auto* const arg  = static_cast<std::uint8_t*>(param_1);

    if (self[6] != 0) {
        const int resource = FUN_004057f0(self[6]);
        *reinterpret_cast<short*>(resource + 0x0E) = *reinterpret_cast<short*>(resource + 0x0E) + -1;
        if ((*reinterpret_cast<unsigned short*>(resource + 0x0E) & 0x7FFF) == 0) {
            FUN_00404070();
        }
    }

    if (*reinterpret_cast<short*>(reinterpret_cast<std::uint8_t*>(self) + 0x56) != -1) {
        FUN_00402a30();
    }

    if (self[7] != 0) {
        FUN_00406a90();
    }

    self[0x0D] = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e2f0c0);

    if (self[2] != 0) {
        reinterpret_cast<void(__cdecl*)(std::uint32_t)>(self[5])(self[2]);
    }

    *self = *reinterpret_cast<std::uint32_t*>(arg + 0x38);

    *reinterpret_cast<int*>(arg + 0x14) =
        *reinterpret_cast<int*>(arg + 0x14) + -1;

    *reinterpret_cast<int*>(arg + 0x10) =
        *reinterpret_cast<int*>(arg + 0x10) + 1;

    *reinterpret_cast<std::uint32_t**>(arg + 0x38) = self;
}