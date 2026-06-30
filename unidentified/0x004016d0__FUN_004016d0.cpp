#include <cstdint>

extern "C" void FUN_00abd570();
extern "C" void FUN_00ac3b80(int value, int a2, int a3, int a4);
extern "C" int FUN_00ac2870(void* param_1);
extern "C" void FUN_00abd5c0();

extern "C" std::uint8_t DAT_00e2eff8;

class Context {
public:
    struct Entry {
        int value;                  // +0x00
        std::uint8_t active;        // +0x04
        std::uint8_t pad05;         // +0x05
        std::uint8_t pad06;         // +0x06
        std::uint8_t nameUsed;      // +0x07
        std::uint32_t cachedValue;  // +0x08
        std::uint32_t computedValue;// +0x0C
    };

    Entry* entries() {
        return *reinterpret_cast<Entry**>(reinterpret_cast<std::uint8_t*>(this) + 0x38);
    }

    const Entry* entries() const {
        return *reinterpret_cast<Entry* const*>(reinterpret_cast<const std::uint8_t*>(this) + 0x38);
    }
};

extern "C" void __thiscall FUN_004016d0(Context* this_, int index) {
    Context::Entry* const entry = this_->entries() + index;

    if (entry->value != 0) {
        FUN_00abd570();
        FUN_00ac3b80(entry->value, 0, 0, 0xff);

        do {
        } while (FUN_00ac2870(&DAT_00e2eff8) == 0);

        FUN_00ac2870(&DAT_00e2eff8);

        entry->value = 0;
        entry->active = 0;
        entry->cachedValue = 0;
        entry->computedValue = 0;

        FUN_00abd5c0();
    }
}