// FUNC_NAME: CmpObject::evaluateComparison
#include <cstdint>

// Forward declarations
struct ValueSource;
typedef void (__stdcall* GetValueFunc)(int contextId, int index, float* out); // actually __thiscall? from call pattern: (*pcVar2)(*param_2, iVar3, local_18); so first arg is from param_2[0] which is likely this for a function? But we'll use __stdcall as placeholder.

// Table entry at g_pGetValueTable + i * 0xC: [4 bytes unknown, 4 bytes function pointer, 4 bytes unknown?]
struct GetValueTableEntry {
    uint8_t unknown_00[4]; // +0x00
    GetValueFunc pfnGetValue; // +0x04
    uint8_t unknown_08[4]; // +0x08
};

// Global variables assumed from the binary (actual addresses unknown)
extern GetValueTableEntry* g_pGetValueTable; // DAT_01205570
extern int32_t g_iMaxIndex; // DAT_01205574

// ValueSource structure
// When flag == '\n' (0x0A), uses index to call g_pGetValueTable entry
// Otherwise literal is stored at +0x4
struct ValueSource {
    char flag;             // +0x00: if '\n' then refer to table, else literal
    char padding;          // +0x01
    int16_t index;         // +0x02: used when flag == '\n'
    float literal;         // +0x04: direct float value when flag != '\n' (actually stored at +4? code reads *(float *)(pcVar1 + 4))
};

// The object that holds two ValueSource pointers
struct ComparisonObject {
    uint8_t unknown_00[8]; // +0x00-0x07 unknown
    ValueSource** ppValues; // +0x08: pointer to array of two ValueSource* [0]=first, [1]=second
};

// Output structure for the comparison result
struct ComparisonResult {
    int32_t contextId;   // +0x00: passed to GetValueFunc as first argument
    uint8_t pad[8];      // +0x04-0x0B (not used in this function)
    ComparisonObject* pObject; // +0x0C: set to this pointer if condition true
};

// Function to read a float from a ValueSource
static float readValue(const ValueSource* pSource, int contextId) {
    if (pSource->flag == '\n') {
        int index = pSource->index;
        if (index >= 0 && index < g_iMaxIndex) {
            GetValueTableEntry* entry = &g_pGetValueTable[index];
            if (entry->pfnGetValue != nullptr) {
                float result;
                entry->pfnGetValue(contextId, index, &result);
                return result;
            }
        }
        return 0.0f; // fallback, shouldn't happen
    } else {
        return pSource->literal;
    }
}

// Main function: evaluates comparison of two values from the object's ValueSources
bool __thiscall evaluateComparison(ComparisonObject* this_, ComparisonResult* pResult) {
    ValueSource** ppSources = this_->ppValues;
    ValueSource* pFirstSource = ppSources[0];
    ValueSource* pSecondSource = ppSources[1];

    float valueFirst = readValue(pFirstSource, pResult->contextId);
    float valueSecond = readValue(pSecondSource, pResult->contextId);

    if (valueFirst < valueSecond) {
        return false; // 0
    }

    pResult->pObject = this_; // remember the object that matched
    return true; // 1
}