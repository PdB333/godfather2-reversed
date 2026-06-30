extern "C" void __thiscall FUN_004538b0(void* this_, std::uint32_t param_1, int* param_2)
{
    auto* const self = static_cast<std::uint32_t*>(this_);
    auto* const secondaryVtable = self + 1;

    DAT_0122344c = self;

    *secondaryVtable = reinterpret_cast<std::uint32_t>(&PTR_FUN_00e2f19c);
    self[2] = 1;
    self[3] = 0;
    self[0] = reinterpret_cast<std::uint32_t>(&PTR_FUN_00e31890);
    *secondaryVtable = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e31898);

    {
        using Fn = std::uint32_t (__thiscall*)();
        auto* const vtable = *reinterpret_cast<void***>(param_2);
        auto* const fn = reinterpret_cast<Fn>(vtable[3]); // +0x0c
        self[4] = fn();
    }

    self[5]  = 0;
    self[8]  = 0;
    self[9]  = 0;
    self[10] = 0;
    self[11] = 0;
    self[12] = 0;
    self[13] = 0;
    self[14] = 0;
    self[15] = 0;
    self[16] = 0;
    self[17] = 0;
    self[18] = 0;
    self[19] = 0;
    self[20] = 0;
    self[21] = 0;
    self[25] = 0;
    self[26] = 0;

    std::uint32_t value;
    const auto allocA = FUN_009c8e50(8);
    if (allocA == 0) {
        value = 0;
    } else {
        value = FUN_004536b0();
    }
    self[26] = value;

    const auto allocB = FUN_009c8e50(0x8c);
    if (allocB == 0) {
        value = 0;
    } else {
        value = FUN_004cb610(param_1, self[26]);
    }

    FUN_00452df0(value);

    auto* object38 = reinterpret_cast<std::uint32_t*>(FUN_009c8e50(0x38));
    if (object38 != nullptr) {
        object38[1]  = 0;
        object38[2]  = 0;
        object38[8]  = 0;
        object38[12] = 0;
        object38[6]  = 0xffffffffu;
        object38[7]  = 0;
        object38[3]  = 0;
        object38[4]  = 0;
        object38[5]  = 0;
        object38[11] = 0;
        object38[0]  = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e31864);
        object38[13] = 0;
    }
    self[22] = reinterpret_cast<std::uint32_t>(object38);

    auto* object34 = reinterpret_cast<std::uint32_t*>(FUN_009c8e50(0x34));
    if (object34 != nullptr) {
        object34[1]  = 0;
        object34[2]  = 0;
        object34[8]  = 0;
        object34[12] = 0;
        object34[6]  = 0xffffffffu;
        object34[7]  = 0;
        object34[3]  = 0;
        object34[4]  = 0;
        object34[5]  = 0;
        object34[11] = 0;
        object34[0]  = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e3181c);
        object34[12] = object34[12] | 8;
    }
    self[23] = reinterpret_cast<std::uint32_t>(object34);

    FUN_00452df0(reinterpret_cast<std::uint32_t>(object34));

    if (DAT_01206940 != 0) {
        FUN_00407e60(secondaryVtable, &DAT_01206940);
    }
}