#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" std::int32_t FUN_004a8180(std::int32_t param_1, std::int32_t param_2);

struct FUN_00406380_StringEntry
{
    const char* name;          // [0x00]
    std::uint32_t value;       // [0x04]
    std::uint32_t unknown_08;  // [0x08]
    std::uint32_t unknown_0c;  // [0x0C]
};

struct FUN_00406380_RuntimeObject
{
    std::byte pad00[0x0A];
    std::uint8_t flags;                    // [0x0A]
    std::byte pad0b[0x01];
    FUN_00406380_StringEntry* stringEntry; // [0x0C]
};

struct FUN_00406380_Record
{
    std::int32_t param_2_value;      // [0x00]
    std::int32_t param_4_value;      // [0x04]
    FUN_00406380_StringEntry* entry; // [0x08]
    std::int32_t param_5_value;      // [0x0C]
    std::int32_t param_6_value;      // [0x10]
};

struct FUN_00406380_Object
{
    std::byte pad00[0x44];
    FUN_00406380_Record* records;               // [0x44]
    std::uint32_t recordCount;                  // [0x48]
    std::byte pad4c[0xD8];
    std::uint32_t runtimeObjectLimit;           // [0x124]
    std::byte pad128[0x2C];
    FUN_00406380_StringEntry* stringEntries;    // [0x154]
    std::uint32_t stringEntryCount;             // [0x158]
};

void FUN_00406380(
    std::int32_t param_1,
    std::int32_t param_2,
    FUN_00406380_StringEntry* param_3,
    std::int32_t param_4,
    std::int32_t param_5,
    std::int32_t param_6)
{
    auto* const self = reinterpret_cast<FUN_00406380_Object*>(param_1);

    FUN_00406380_StringEntry* const targetEntry = param_3;
    std::uint32_t matchedIndex = 0;
    param_3 = nullptr;

    std::uint32_t selectedIndex = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(param_3));

    if (self->stringEntryCount != 0) {
        FUN_00406380_StringEntry* currentEntry = self->stringEntries;

        do {
            if (currentEntry->value == targetEntry->value) {
                selectedIndex = matchedIndex;

                if (currentEntry->value == 0) {
                    break;
                }

                const auto* lhs =
                    reinterpret_cast<const std::uint8_t*>(targetEntry->name);
                const auto* rhs =
                    reinterpret_cast<const std::uint8_t*>(currentEntry->name);

                std::int32_t compareResult;

                do {
                    const std::uint8_t first = *rhs;
                    const bool isLess = first < *lhs;

                    if (first != *lhs) {
                        compareResult =
                            (1 - static_cast<std::uint32_t>(isLess)) -
                            static_cast<std::uint32_t>(isLess != 0);
                        goto compare_done;
                    }

                    if (first == 0) {
                        break;
                    }

                    const std::uint8_t second = rhs[1];
                    const bool secondIsLess = second < lhs[1];

                    if (second != lhs[1]) {
                        compareResult =
                            (1 - static_cast<std::uint32_t>(secondIsLess)) -
                            static_cast<std::uint32_t>(secondIsLess != 0);
                        goto compare_done;
                    }

                    rhs += 2;
                    lhs += 2;
                } while (second != 0);

                compareResult = 0;

compare_done:
                if (compareResult == 0) {
                    break;
                }
            }

            matchedIndex = matchedIndex + 1;
            currentEntry = currentEntry + 1;
            selectedIndex = static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(param_3));
        } while (matchedIndex < self->stringEntryCount);
    }

    param_3 = reinterpret_cast<FUN_00406380_StringEntry*>(
        static_cast<std::uintptr_t>(selectedIndex));

    std::uint32_t runtimeIndex = 0;
    std::int32_t runtimeObject;

    do {
        if (self->runtimeObjectLimit <= runtimeIndex) {
            break;
        }

        runtimeObject = FUN_004a8180(param_2, 0);

        if (runtimeObject != 0) {
            auto* const object =
                reinterpret_cast<FUN_00406380_RuntimeObject*>(runtimeObject);

            object->flags = static_cast<std::uint8_t>(object->flags & 0xdfu);
            object->stringEntry = param_3;
        }

        runtimeIndex = runtimeIndex + 1;
    } while (runtimeObject == 0);

    if (self->recordCount != 0) {
        FUN_00406380_Record* currentRecord = self->records;
        std::uint32_t recordIndex = 0;

        while ((currentRecord->param_2_value != param_2 ||
                currentRecord->param_4_value != param_4) ||
               (currentRecord->entry != param_3 ||
                (currentRecord->param_5_value != param_5 ||
                 currentRecord->param_6_value != param_6))) {
            recordIndex = recordIndex + 1;
            currentRecord = currentRecord + 1;

            if (self->recordCount <= recordIndex) {
                return;
            }
        }

        if (recordIndex != self->recordCount - 1U) {
            FUN_00406380_Record* const lastRecord =
                reinterpret_cast<FUN_00406380_Record*>(
                    reinterpret_cast<std::uintptr_t>(self->records) - 0x14 +
                    self->recordCount * 0x14);

            FUN_00406380_Record* const destination =
                reinterpret_cast<FUN_00406380_Record*>(
                    reinterpret_cast<std::uintptr_t>(self->records) +
                    recordIndex * 0x14);

            *destination = *lastRecord;
        }

        self->recordCount = self->recordCount + static_cast<std::uint32_t>(-1);
    }
}