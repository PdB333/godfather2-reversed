// FUNC_NAME: EARSString::assignFromSource
class EARSString {
public:
    // Offsets:
    // +0x00: uint32_t flags (zeroed)
    // +0x04: int32_t length
    // +0x08: byte padding
    // +0x0C: char* source
    // +0x10: int32_t index (temp counter)
    // +0x14: char* buffer (allocated)
    // +0x18: int32_t field_18
    // +0x1C: int32_t field_1C

    void assignFromSource(void* sourceObj) {
        // Zero out first two fields
        flags = 0;
        padding = 0;

        // Determine source string pointer from source object
        char* str = *(char**)((uint8_t*)sourceObj + 0x88);
        if (str == nullptr) {
            str = *(char**)((uint8_t*)sourceObj + 0x7C);
        }

        source = str;
        index = 0;

        // Calculate length of source string
        char ch = *str;
        while (ch != '\0') {
            index++;
            ch = *(str + index);
        }

        length = index;

        // Allocate buffer for string + null terminator
        uint32_t localBuffer[3] = {0, 0, 0};
        // Global allocator function at DAT_012234ec + 4
        typedef void* (*AllocFunc)(size_t, uint32_t*);
        AllocFunc alloc = *(AllocFunc*)(*(uint32_t*)0x012234ec + 4);
        buffer = (char*)alloc(length + 1, localBuffer);

        // Note: The actual copy of characters is missing in the decompiled output.
        // Possibly performed by the caller or optimized out by Ghidra.

        field_18 = 0;
        field_1C = 0;
    }

private:
    uint32_t flags;
    int32_t length;
    uint8_t padding;
    char* source;
    int32_t index;    // Temporary, not part of final structure
    char* buffer;
    int32_t field_18;
    int32_t field_1C;
};