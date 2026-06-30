#include <cstdint>

extern "C" void FUN_00abd570();
extern "C" void FUN_00ac41a0(int param_2, std::uint32_t flags, int a3, int a4, int a5);
extern "C" int FUN_00ac28b0();
extern "C" void FUN_00abd5c0();
extern "C" std::uint32_t FUN_00abe220(int value);

class Context {
public:
    struct Entry {
        int value;                  // +0x00
        std::uint8_t active;        // +0x04
        std::uint8_t pad05;         // +0x05
        std::uint8_t pad06;         // +0x06
        std::uint8_t nameUsed;      // +0x07 / unknown byte in decompile window gap
        std::uint32_t cachedValue;  // +0x08
        std::uint32_t computedValue;// +0x0C
    };

    Entry* entries() {
        return *reinterpret_cast<Entry**>(reinterpret_cast<std::uint8_t*>(this) + 0x38);
    }

    const Entry* entries() const {
        return *reinterpret_cast<Entry* const*>(reinterpret_cast<const std::uint8_t*>(this) + 0x38);
    }

    int entryCount() const {
        return *reinterpret_cast<const int*>(reinterpret_cast<const std::uint8_t*>(this) + 0x40);
    }
};

extern "C" int __thiscall FUN_004015e0(Context* this_, int param_2, std::uint8_t param_3) {
    if (param_2 != 0) {
        int entryCount = this_->entryCount();
        int index = 1;

        if (1 < entryCount) {
            std::uint8_t* usedFlag = reinterpret_cast<std::uint8_t*>(this_->entries()) + 0x14;
            do {
                if (*usedFlag == 0) {
                    break;
                }
                index = index + 1;
                usedFlag = usedFlag + 0x10;
            } while (index < entryCount);
        }

        if (index < entryCount) {
            std::uint32_t flags = 0;

            if ((param_3 & 1) == 0) {
                flags = 1;
                if ((param_3 & 4) != 0) {
                    flags = 3;
                }
                if ((param_3 & 8) == 0) {
                    flags = flags | 4;
                }
            }

            FUN_00abd570();
            FUN_00ac41a0(param_2, flags, 0, 0, 0xff);

            int createdValue = FUN_00ac28b0();
            if (createdValue != 0) {
                const int byteOffset = index * 0x10;
                auto* base = reinterpret_cast<std::uint8_t*>(this_->entries());

                *reinterpret_cast<std::uint8_t*>(base + 4 + byteOffset) = 1;
                *reinterpret_cast<int*>(base + byteOffset) = createdValue;

                const std::uint32_t computedValue = FUN_00abe220(createdValue);
                *reinterpret_cast<std::uint32_t*>(base + 0x0c + byteOffset) = computedValue;

                std::uint32_t cachedValue;
                if ((param_3 & 8) == 0) {
                    cachedValue = 0;
                } else {
                    cachedValue = *reinterpret_cast<std::uint32_t*>(base + 0x0c + byteOffset);
                }

                *reinterpret_cast<std::uint32_t*>(base + 8 + byteOffset) = cachedValue;

                FUN_00abd5c0();
                return index;
            }

            FUN_00abd5c0();
        }
    }

    return 0;
}