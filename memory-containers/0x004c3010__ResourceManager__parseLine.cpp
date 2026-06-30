// FUNC_NAME: ResourceManager::parseLine

#include <cstdio>
#include <cstring>

// Global delimiter characters (DAT_00e3621c: 0x00e3621c, two bytes)
extern char gDelimiter[2]; // DAT_00e3621c

// Allocator: allocates a block of size bytes (FUN_009c8e50)
void* allocateMemory(int size);

// Resizes the internal array to newCapacity (FUN_004c32f0)
void resizeArray(int newCapacity);

// Stores a name string (FUN_004d3d90) – likely copies into a pool or hashes it
void storeName(const char* name);

// Resource entry structure (size = 0x1c = 28 bytes)
struct ResourceEntry {
    int field0;          // +0x00: some counter/refcount (initialized to 0)
    int field4;          // +0x04
    int field8;          // +0x08
    int field12;         // +0x0C
    int hexValue;        // +0x10: parsed hex value
    int* counterPtr;     // +0x14: pointer to external counter (param_2)
    char byte24;         // +0x18: single byte (initialized to 0)
    // Total: 6*4 + 1 = 25 bytes, but aligned to 28; padding 3 bytes
};

void __thiscall ResourceManager::parseLine(int* counterPtr, const char* line) {
    // this: at +0x208: array of ResourceEntry* (ptr)
    //          +0x20C: current count (int)
    //          +0x210: allocated capacity (int)
    ResourceEntry* newEntry;
    char* token;
    int type = -1;
    unsigned int hexValue;
    char nameBuffer[256];

    // Tokenizer delimiter (local_10c / local_10a) = gDelimiter
    // strtok with global delimiter
    token = strtok(const_cast<char*>(line), gDelimiter);
    if (token == nullptr) return;
    sscanf(token, "%d", &type);
    if (type != 1) return;   // Only process lines starting with "1"

    // Second token: hex value
    token = strtok(nullptr, gDelimiter);
    if (token == nullptr) return;
    sscanf(token, "0x%x", &hexValue);

    // Third token: name string
    token = strtok(nullptr, gDelimiter);
    if (token == nullptr) return;
    strncpy(nameBuffer, token, sizeof(nameBuffer) - 1);
    nameBuffer[sizeof(nameBuffer) - 1] = '\0';

    // Allocate a new ResourceEntry
    newEntry = static_cast<ResourceEntry*>(allocateMemory(sizeof(ResourceEntry)));
    if (newEntry != nullptr) {
        newEntry->counterPtr = counterPtr;
        newEntry->field0 = 0;
        newEntry->field4 = 0;
        newEntry->field8 = 0;
        newEntry->field12 = 0;
        newEntry->hexValue = 0;
        newEntry->byte24 = 0;
        // Increment the external counter (counterPtr points to an int)
        (*counterPtr)++;
        newEntry->hexValue = hexValue;
        storeName(nameBuffer);
    }

    // Ensure the internal array has capacity
    int count = *(int*)((char*)this + 0x20C);
    int capacity = *(int*)((char*)this + 0x210);
    if (count == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        resizeArray(capacity);
    }

    // Add new entry to the array
    ResourceEntry** array = *(ResourceEntry***)((char*)this + 0x208);
    int newCount = count + 1;
    *(int*)((char*)this + 0x20C) = newCount;
    array[count] = newEntry;
}