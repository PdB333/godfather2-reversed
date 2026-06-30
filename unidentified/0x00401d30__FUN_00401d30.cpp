#include <cstddef>
#include <cstdint>

extern "C" void FUN_004d3ca0(const char* a1, int a2, const char* a3, int a4);

int __thiscall FUN_00401d30(int this_, char* param_2, char* param_3)
{
    *reinterpret_cast<std::uint32_t*>(this_ + 0x0c) = 0;

    int param_3_length;
    if (param_3 == nullptr) {
        param_3_length = 0;
    } else {
        char* end = param_3;
        char ch;
        do {
            ch = *end;
            ++end;
        } while (ch != '\0');
        param_3_length = static_cast<int>(end - (param_3 + 1));
    }

    if (param_2 != nullptr) {
        char* end = param_2;
        char ch;
        do {
            ch = *end;
            ++end;
        } while (ch != '\0');

        FUN_004d3ca0(param_2, static_cast<int>(end - (param_2 + 1)), param_3, param_3_length);
        return this_;
    }

    FUN_004d3ca0(nullptr, 0, param_3, param_3_length);
    return this_;
}