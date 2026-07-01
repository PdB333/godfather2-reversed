// FUNC_NAME: DonScoreManager::addDonScoringRow (0x0092ea80)
// Global manager pointer used for Don Scoring system (likely from DonControlManager or TopDonChallenge)
static uintptr_t g_donScoreManager = 0x0112ebb4; // Replace with actual global address

// Default empty string constant (0x0120546e)
static const char* kEmptyString = ""; // Placeholder for DAT_0120546e

// Helper functions (likely EA string/memory operations)
// FUN_00603d30: unknown copy/alloc function (e.g., EA::Memory::strdup)
// FUN_00604000: unknown string concatenation/alloc function (e.g., EA::Memory::strcat)
// FUN_005a04a0: logging/table insertion function (e.g., debug printf or database insert)

void DonScoreManager::addDonScoringRow(int categoryId, uint32_t* rowData) {
    if (rowData == nullptr) {
        return;
    }

    // Temporary string buffers for concatenation
    char* buffer1 = nullptr;  // for rowData[6]
    char* buffer2 = nullptr;  // for rowData[7]
    char* buffer3 = nullptr;  // for rowData[8]
    char* bufferCombined = nullptr; // for rowData[7] + rowData[8]

    // Initialize strings with empty defaults
    char* string0 = nullptr;
    char* string1 = nullptr;
    char* string2 = nullptr;
    char* string3 = nullptr;
    char* combinedString = nullptr;

    // Store first two parameters into the manager's fields
    *(uint32_t*)(g_donScoreManager + 0x144) = categoryId;            // +0x144: scoring category ID
    *(uint32_t*)(g_donScoreManager + 0x164) = rowData[5];            // +0x164: probably a score value or identifier

    // Process strings from rowData
    // rowData[6] -> buffer1 (single copy)
    EA::Memory::strdup(reinterpret_cast<const char*>(rowData[6]), &buffer1, 1);
    // rowData[7] -> buffer2 (single copy)
    EA::Memory::strdup(reinterpret_cast<const char*>(rowData[7]), &buffer2, 1);
    // rowData[8] -> buffer3 (single copy)
    EA::Memory::strdup(reinterpret_cast<const char*>(rowData[8]), &buffer3, 1);
    // rowData[7] + rowData[8] -> combined (string concatenation)
    EA::Memory::strcat(reinterpret_cast<const char*>(rowData[7]), reinterpret_cast<const char*>(rowData[8]), &combinedString, 1);

    // Fallback to empty string if any allocation failed
    const char* s0 = (rowData[0] != 0) ? reinterpret_cast<const char*>(rowData[0]) : kEmptyString;
    const char* s1 = (buffer1 != nullptr) ? buffer1 : kEmptyString;
    const char* s2 = (buffer2 != nullptr) ? buffer2 : kEmptyString;
    const char* s3 = (buffer3 != nullptr) ? buffer3 : kEmptyString;
    const char* sCombined = (combinedString != nullptr) ? combinedString : kEmptyString;

    // Log the scoring row (5 strings: rowData[0], rowData[6], rowData[7], rowData[8], combined)
    Debug::logTable("AddDonScoringRow", 0, "row_format", 5, s0, s1, s2, s3, sCombined);

    // Free allocated buffers using their respective destructor function pointers
    if (combinedString != nullptr) {
        deleteBuffer(combinedString);
    }
    if (buffer3 != nullptr) {
        deleteBuffer(buffer3);
    }
    if (buffer2 != nullptr) {
        deleteBuffer(buffer2);
    }
    if (buffer1 != nullptr) {
        deleteBuffer(buffer1);
    }
}