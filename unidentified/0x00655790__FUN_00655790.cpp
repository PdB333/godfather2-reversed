extern "C" void __thiscall FUN_00655790(
    int* this_,
    std::uint32_t param_2,
    int param_3)
{
    if (*reinterpret_cast<std::uint32_t*>(param_3 + 0x18) <
        *reinterpret_cast<std::uint32_t*>(param_3 + 0x2c)) {
        void* local_c[2];
        local_c[0] = this_;

        if ((*(*reinterpret_cast<std::uint8_t**>(param_3 + 0x0c)) & 0x80) == 0) {
            FUN_0064b9e0(8, local_c);

            if (7 < static_cast<std::uint8_t>(reinterpret_cast<std::uintptr_t>(local_c[0]))) {
                auto* const vtable =
                    reinterpret_cast<void***>(this_);
                auto* const method =
                    reinterpret_cast<void(__thiscall*)(int*, std::uint32_t, void*, int)>(
                        (*vtable)[4]);
                method(this_, param_2, local_c[0], param_3);
                return;
            }

            switch (static_cast<std::uint8_t>(reinterpret_cast<std::uintptr_t>(local_c[0]))) {
            case 0:
                FUN_00655a50(this_, param_2);
                return;

            case 1:
                FUN_00655cb0(this_);
                return;

            case 2:
                FUN_00656070(this_, param_2, param_3);
                return;

            case 3:
                FUN_006566e0(this_, param_2);
                return;

            case 4:
                FUN_00656510(param_2);
                return;

            case 5:
                FUN_00657800(this_, param_3);
                return;

            case 6:
                FUN_00656ad0(this_, param_2, param_3);
                return;

            case 7:
                FUN_00657220(this_, param_2, param_3);
                return;

            default:
                break;
            }
        } else {
            int* const obj = reinterpret_cast<int*>(FUN_00655250());
            if (obj != nullptr) {
                obj[2] = obj[2] + 1;
                FUN_00653150(param_3);

                int* const refCount = obj + 2;
                *refCount = *refCount + -1;
                if (*refCount == 0) {
                    (**reinterpret_cast<void (***)(void)>(obj + 0))[2]();
                    return;
                }
            }
        }
    }
}