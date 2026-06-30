#include <cstdint>

extern "C" void* FUN_009c8e80(std::uint32_t size);
extern "C" void FUN_004d3b50(void* src);
extern "C" void FUN_009c8f10(void* ptr);

struct FUN_004074e0_Entry
{
    void* object;                             // [0x00]
    std::uint32_t field_0x04;                // [0x04]
    std::uint32_t field_0x08;                // [0x08]
    void (__fastcall* destroy)(void*);       // [0x0C]
};

struct FUN_004074e0_Array
{
    FUN_004074e0_Entry* entries; // [0x00]
    int count;                   // [0x04]
    int capacity;                // [0x08]
};

extern "C" void __thiscall FUN_004074e0(FUN_004074e0_Array* param_1, std::uint32_t param_2)
{
    if (static_cast<std::uint32_t>(param_1->capacity) < param_2) {
        auto* const newEntries =
            static_cast<FUN_004074e0_Entry*>(FUN_009c8e80(param_2 << 4));

        int offset = 0;

        if (param_1->entries != nullptr) {
            std::uint32_t local_8 = 0;
            auto* dst = reinterpret_cast<std::uint8_t*>(newEntries);

            if (param_1->count != 0) {
                do {
                    auto* const src = reinterpret_cast<FUN_004074e0_Entry*>(
                        reinterpret_cast<std::uint8_t*>(param_1->entries) + offset);

                    if (dst != nullptr) {
                        FUN_004d3b50(src);
                    }

                    if (src->object != nullptr) {
                        src->destroy(src->object);
                    }

                    local_8 = local_8 + 1;
                    offset = offset + 0x10;
                    dst = dst + 0x10;
                } while (local_8 < static_cast<std::uint32_t>(param_1->count));
            }

            FUN_009c8f10(param_1->entries);
        }

        param_1->entries = newEntries;
        param_1->capacity = static_cast<int>(param_2);
    }
}