#include <cstdint>

extern "C" void FUN_00b8fc30(std::uint32_t value);

class Context {
public:
    std::uint32_t& slot0() {
        return *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this) + 0x04);
    }

    std::uint32_t* slot_array() {
        return reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this) + 0x04);
    }

    const std::uint32_t* slot_array() const {
        return reinterpret_cast<const std::uint32_t*>(reinterpret_cast<const std::uint8_t*>(this) + 0x04);
    }

    int& count() {
        return *reinterpret_cast<int*>(reinterpret_cast<std::uint8_t*>(this) + 0x24);
    }

    const int& count() const {
        return *reinterpret_cast<const int*>(reinterpret_cast<const std::uint8_t*>(this) + 0x24);
    }
};

extern "C" void __thiscall FUN_00401590(Context* this_) {
    int i = 0;

    if (0 < this_->count()) {
        std::uint32_t* slot = this_->slot_array();

        do {
            FUN_00b8fc30(*slot);
            *slot = 0;
            i = i + 1;
            slot = slot + 1;
        } while (i < this_->count());

        this_->count() = 0;
        return;
    }

    this_->count() = 0;
    return;
}