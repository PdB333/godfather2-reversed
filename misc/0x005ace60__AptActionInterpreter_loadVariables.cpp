// Xbox PDB: AptActionInterpreter::loadVariables
// FUNC_NAME: DebugRegistry::printAllItems
// Address: 0x005ace60
// Role: Iterates over a registry of items (probably debug commands or objects) and outputs them via a callback.
// Uses global function pointers for allocation/deallocation and singleton selection based on 'this' pointer.

#include <cstdint>

// Global function pointers (initialized elsewhere)
static void* (*s_getFromRegistry_nonNull)() = reinterpret_cast<void*(*)()>(DAT_0119cb24);
static void* (*s_getFromRegistry_null)() = reinterpret_cast<void*(*)()>(DAT_0119cb28);
static void* (*s_alloc)(uint32_t size, uint32_t flags) = reinterpret_cast<void*(*)(uint32_t,uint32_t)>(DAT_0119caf0);
static void  (*s_dealloc)(void* ptr) = reinterpret_cast<void(*)(void*)>(DAT_0119caf4);
// Note: DAT_0119cb28 and DAT_0119cb24 are function pointers returning void*; they are the "registry" singleton getters.

// Forward declarations of helper functions
int FUN_005b1510(void* registry, int* outStringLen, void* outString); // get next entry
void FUN_005a0a00(void* string); // probably hash or normalize string
void FUN_005ad5b0(void* output1, void* output2, void* nameBuf, uint32_t* entryData, int flag1, int flag2); // output function

// The function itself - assumed __thiscall but used as static in this context
void DebugRegistry::printAllItems(void* outputParam1, void* outputParam2) // param_2 and param_3
{
    void* registry;
    if (in_EAX == 0) {
        // static call, use null registry singleton
        if (DAT_0119cb28 == 0) {
            FUN_0059bf00(); // initialization
        }
        registry = s_getFromRegistry_null();
    } else {
        // instance call, use non-null registry singleton
        registry = s_getFromRegistry_nonNull();
    }

    // Local buffers for iteration
    // Stack allocation for name buffer (max 16 bytes? Actually 0x10 bytes)
    char nameBuffer[0x10] = {0}; // uStack_10 (0x10 bytes)
    char entryName[0x10] = {0};  // uStack_2c (0x10 bytes)
    int stringLen = 0;           // iStack_38
    int someFlag = 0;            // uStack_34

    // Start iteration
    int iterator = FUN_005b1510(registry, &stringLen, &entryName); // iVar2

    do {
        if (iterator == 0) {
            // End of iteration, clean up
            s_dealloc(registry);
            if (nameBuffer != 0 && nameBuffer != (char*)0) {
                s_dealloc(nameBuffer);
            }
            if (entryName != 0 && entryName != (char*)0) {
                s_dealloc(entryName);
            }
            return;
        }

        // Compare current entry name with empty string? Actually pcVar5 = ""; but might be a parameter?
        // Assuming filter string is empty (always matches? The logic is: if strings equal, skip output; else output)
        // This seems inverted: if they match, skip? Actually it's: if not equal, perform output.
        // With empty filter, all entries are non-equal (unless entry is empty), so all entries are printed.
        int compareIdx = 0;
        const char* filter = ""; // pcVar5
        if (0 < stringLen) {
            do {
                if (*filter == '\0') break;
                if (entryName[compareIdx] != *filter) goto LAB_005acf50;
                compareIdx++;
                filter++;
            } while (compareIdx < stringLen);
        }

        if ((compareIdx != stringLen) || (*filter != '\0')) {
            // Entry name does not match filter, so output it
LAB_005acf50:
            // Allocate entry data block (0x24 bytes)
            uint32_t* entryData = (uint32_t*)s_alloc(0x24, 0);
            if (entryData == 0) {
                entryData = 0;
            } else {
                // Initialize entryData: set flags and magic?
                *entryData = (*entryData & 0xFFFF8001) | 1;
                *(uint16_t*)((int)entryData + 2) = 0;
                *entryData = *entryData | 0x8000;
                FUN_005a0a00(&entryName); // process string (hash?)
                entryData[8] = 0xBEEFCEEC; // magic constant
            }
            // Output entry: name, data, flags
            FUN_005ad5b0(outputParam1, outputParam2, entryName, entryData, 1, 1);
        }

        // Get next entry
        iterator = FUN_005b1510(iterator, &stringLen, &entryName);
    } while (true);
}