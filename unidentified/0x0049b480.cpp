// FUN_NAME: getGlobalTable
// Address: 0x0049b480
// Role: Lazy initialization of a global table from a static source to a dynamically allocated buffer.
// The function checks a global flag; if not set, allocates memory for an array of structures (0xBC bytes each)
// based on the count stored in low byte of a global, copies from a static data array, then sets the flag.
// Returns pointer to a static structure containing the count and pointer to allocated data.

#include <cstring> // for memcpy

// Forward declaration of memory allocation function
void* allocateMemory(int size);

// Global state
static struct { // +0x00: count (byte), +0x04: data pointer (void*)
    unsigned char count;
    unsigned char padding[3];
    void* data;
} g_tableInfo = {0, {0, 0, 0}, nullptr};

static unsigned char g_initFlag = 0; // Actually stored at DAT_012053dc + 0x03

// Source table static data: count stored at DAT_010c36a8 (low byte), pointer to array at DAT_010c36b0
// The source count and data are external globals; we model them as extern.
extern unsigned int g_sourceCount; // DAT_010c36a8, low byte used
extern unsigned int g_sourcePointer; // DAT_010c36ac (not used directly in copy? The pointer is at DAT_010c36b0?)
// Actually based on decompile: DAT_010c36a8 is the count, DAT_010c36ac is some other value, DAT_010c36b0 is start of array.
// We'll treat DAT_010c36a8 as unsigned int with count in low byte, and DAT_010c36b0 as array of bytes.
extern unsigned char g_sourceData[]; // Starting at DAT_010c36b0

// The returned structure pointer is &g_tableInfo
struct TableInfo {
    unsigned char countWeird; // low byte of original? Actually g_tableInfo.count is set from low byte of DAT_010c36a8
    unsigned char pad[3];
    void* data;
};

// The function as decompiled
undefined1* getGlobalTable()
{
    if (g_initFlag == 0) {
        // Get count (low byte)
        unsigned char count = (unsigned char)(g_sourceCount & 0xFF);
        g_tableInfo.count = count; // _DAT_01163fe8 set to low byte
        g_tableInfo.data = nullptr;
        // Allocate memory for count * 0xBC (188) bytes
        int allocSize = count * 0xBC;
        void* allocated = allocateMemory(allocSize); // FUN_009c8e50
        g_tableInfo.data = allocated;
        // Copy from static source data at DAT_010c36b0
        memcpy(allocated, g_sourceData, allocSize);
        // Set initialization flag
        g_initFlag = 1;
    }
    // Return pointer to the static table info struct
    return (undefined1*)&g_tableInfo;
}