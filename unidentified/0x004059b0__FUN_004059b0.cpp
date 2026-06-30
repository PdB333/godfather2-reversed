#include <cstdint>

std::int32_t __cdecl FUN_004056b0(std::int32_t param_1);

struct FUN_004059b0_Entry
{
    FUN_004059b0_Entry* next;    // [0x00]
    std::uint8_t gap_04[0x18];
    std::int32_t value;          // [0x1C]
    std::uint8_t gap_20[0x8];
    std::int32_t key;            // [0x2C]
};

struct FUN_004059b0_Object
{
    std::uint8_t gap_00[0x68];
    FUN_004059b0_Entry* list68;  // [0x68]
    FUN_004059b0_Entry* list70;  // [0x70]
    std::uint8_t gap_74[0xC];
    FUN_004059b0_Entry* cached;  // [0x80]
};

std::int32_t __thiscall FUN_004059b0(FUN_004059b0_Object* this_, std::int32_t param_2)
{
    FUN_004059b0_Entry* entry = this_->cached;

    if ((entry == nullptr) || (entry->key != param_2))
    {
        entry = this_->list70;
        if (entry != nullptr)
        {
            do
            {
                if (entry->key == param_2)
                {
                    break;
                }

                entry = entry->next;
            } while (entry != nullptr);

            if (entry != nullptr)
            {
                goto found;
            }
        }

        entry = this_->list68;
        if (entry != nullptr)
        {
            do
            {
                if (entry->key == param_2)
                {
                    break;
                }

                entry = entry->next;
            } while (entry != nullptr);

            if (entry != nullptr)
            {
                goto found;
            }
        }

        entry = reinterpret_cast<FUN_004059b0_Entry*>(FUN_004056b0(param_2));
        if (entry == nullptr)
        {
            return 0;
        }
    }

found:
    return entry->value;
}