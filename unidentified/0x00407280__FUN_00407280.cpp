#include <cstdint>

extern "C" int __fastcall FUN_00407280(std::uint32_t* param_1, void* param_2)
{
    std::uint32_t* current = reinterpret_cast<std::uint32_t*>(*param_1);
    int index = 0;

    while (true) {
        if (current == nullptr) {
            return -1;
        }

        if (current == param_2) {
            break;
        }

        current = reinterpret_cast<std::uint32_t*>(*current);
        index = index + 1;
    }

    return index;
}