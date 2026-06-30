#include <cstdint>
#include <cstddef>
#include <strings.h>

struct LookupEntry
{
    std::int32_t* key;          // [0x00]
    const char* name;           // [0x04]
    std::int32_t field8;        // [0x08]
    std::int32_t fieldC;        // [0x0C]
    std::int32_t field10;       // [0x10]
};

struct LookupTable
{
    std::int32_t field0;        // [0x00]
    std::int32_t field4;        // [0x04]
    std::uint16_t entryCount;   // [0x08]
    std::uint16_t fieldA;       // [0x0A]
    std::int32_t fieldC;        // [0x0C]
    LookupEntry entries[1];     // [0x10]
};

struct SearchKey
{
    std::int32_t id;            // [0x00]
    const char* name;           // [0x04]
};

struct FUN_00405fd0_Object
{
    std::uint8_t pad_0000[0xA4];
    LookupTable* lookupTables[0x20]; // [0xA4]
    std::uint8_t pad_0124[0x124 - 0xA4 - sizeof(lookupTables)];
    std::uint32_t lookupTableCount;  // [0x124]
};

static_assert(offsetof(FUN_00405fd0_Object, lookupTables) == 0xA4);
static_assert(offsetof(FUN_00405fd0_Object, lookupTableCount) == 0x124);

extern "C" LookupTable* FUN_004057f0(LookupTable* table);
extern "C" LookupEntry* FUN_004a8180(std::int32_t id, std::int32_t unused);

LookupEntry* __thiscall FUN_00405fd0(
    FUN_00405fd0_Object* self,
    LookupTable* table,
    SearchKey* key)
{
    LookupEntry* foundEntry = nullptr;
    LookupTable* resolvedTable = nullptr;

    if (table != nullptr) {
        resolvedTable = FUN_004057f0(table);

        if (key->id == 0) {
            std::uint32_t index = 0;
            LookupEntry* entry = reinterpret_cast<LookupEntry*>(
                reinterpret_cast<std::uint8_t*>(resolvedTable) + 0x10);

            if (resolvedTable->entryCount != 0) {
                do {
                    if (entry->key == reinterpret_cast<std::int32_t*>(key)) {
                        foundEntry = reinterpret_cast<LookupEntry*>(
                            reinterpret_cast<std::uint8_t*>(resolvedTable) + 0x10) + index;
                        goto found_in_initial_table;
                    }

                    if (*reinterpret_cast<std::int32_t*>(entry->key) != 0) {
                        break;
                    }

                    index = index + 1;
                    entry = entry + 1;
                } while (index < resolvedTable->entryCount);
            }
        } else {
            foundEntry = FUN_004a8180(key->id, 0);

found_in_initial_table:
            if (foundEntry != nullptr) {
                return foundEntry;
            }
        }
    }

    std::uint32_t tableIndex = 0;
    if (self->lookupTableCount != 0) {
        LookupTable** currentTable = &self->lookupTables[0];

        do {
            LookupTable* candidateTable = *currentTable;
            if (candidateTable != resolvedTable) {
                if (key->id == 0) {
                    const std::uint16_t entryCount = candidateTable->entryCount;
                    std::uint32_t entryIndex = 0;
                    LookupEntry* entry = reinterpret_cast<LookupEntry*>(
                        reinterpret_cast<std::uint8_t*>(candidateTable) + 0x10);

                    if (entryCount != 0) {
                        do {
                            if (*reinterpret_cast<std::int32_t*>(entry->key) != 0) {
                                break;
                            }

                            const char* lhs = reinterpret_cast<const char*>(entry->key[1]);
                            const char* rhs = key->name;

                            std::uint32_t compareResult;
                            if ((lhs == nullptr) || (rhs == nullptr)) {
                                if (lhs <= rhs) {
                                    compareResult = static_cast<std::uint32_t>(lhs < rhs);
                                    if (compareResult == 0) {
                                        foundEntry = reinterpret_cast<LookupEntry*>(
                                            reinterpret_cast<std::uint8_t*>(candidateTable) + 0x10) + entryIndex;
                                        break;
                                    }
                                }
                            } else {
                                compareResult = static_cast<std::uint32_t>(::strcasecmp(lhs, rhs));
                                if (compareResult == 0) {
                                    foundEntry = reinterpret_cast<LookupEntry*>(
                                        reinterpret_cast<std::uint8_t*>(candidateTable) + 0x10) + entryIndex;
                                    break;
                                }
                            }

                            entryIndex = entryIndex + 1;
                            entry = entry + 1;
                        } while (entryIndex < entryCount);
                    }
                } else {
                    foundEntry = FUN_004a8180(key->id, 0);
                }

                if (foundEntry != nullptr) {
                    return foundEntry;
                }
            }

            currentTable = currentTable + 1;
            tableIndex = tableIndex + 1;
        } while (tableIndex < self->lookupTableCount);
    }

    return foundEntry;
}