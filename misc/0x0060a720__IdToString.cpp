// FUNC_NAME: IdToString
// Function address: 0x0060a720
// Role: Converts an integer ID to a string using a global table of converters.
// __fastcall: first parameter (typeIndex) in ECX, second (value) in EDX.
// Returns pointer to a temporary local buffer containing the string, or NULL if value is 0.
// The buffer is only valid until the function returns -- caller must use immediately.

#include <cstdint>

typedef uint32_t (__fastcall *ConvertFunc)(void* self, int value, char* buffer, int* bufferSize);

// Global array at DAT_011eb8f4, each entry is 0x10 bytes.
// Each entry appears to be a pointer to an object with a vtable.
// The object's vtable at offset 0x18 contains the conversion method.
static const uint8_t* const DAT_011eb8f4 = reinterpret_cast<const uint8_t*>(0x011eb8f4);

char* __fastcall IdToString(int typeIndex, int value)
{
    if (value == 0)
        return nullptr;

    char buffer[48];                 // Temporary output buffer
    int bufferSize = 48;             // Max buffer length (should be 48, corrected from decompiler's 1)

    // Locate the converter object from global table
    void* const* tableEntry = reinterpret_cast<void* const*>(DAT_011eb8f4 + typeIndex * 0x10);
    void* converterObj = *tableEntry;

    // Get the vtable pointer
    void* vtable = *reinterpret_cast<void**>(converterObj);

    // Function pointer from vtable offset 0x18
    ConvertFunc convertFunc = *reinterpret_cast<ConvertFunc*>(reinterpret_cast<uint8_t*>(vtable) + 0x18);

    // Call the converter: converts 'value' to string, writes into 'buffer', updates 'bufferSize' with actual length
    convertFunc(converterObj, value, buffer, &bufferSize);

    // Return buffer pointer (valid only in caller's immediate context)
    return buffer;
}