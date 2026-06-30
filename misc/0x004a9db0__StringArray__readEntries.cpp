// FUNC_NAME: StringArray::readEntries
// Address: 0x004a9db0
// Reads a binary stream using stream_read (FUN_0064b9e0) to populate a dynamic string array.
// The stream contains: number of entries (DWORD), then for each entry: a size DWORD followed by size*8 bytes of data.
// Data is null-terminated at byte offset 'size' and then processed (likely converted to UTF-8).
// Array grows by doubling capacity when full. A callback may be invoked at end (not used by default).

class StringArray {
    char** data;        // +0x00 pointer to string array
    int count;          // +0x04 number of strings currently stored
    int capacity;       // +0x08 allocated capacity
    void (*callback)(char*); // +0x0C callback function (unused, always null)
public:
    void readEntries(); // __thiscall
};

// These are external helper functions (from engine):
void stream_read(int type, void* out); // FUN_0064b9e0 - reads from binary stream
char* stringProcess(char* buf);        // FUN_004d3d90 - returns processed string (might allocate)
void* memRealloc(int newSize);         // FUN_00407880 - reallocates memory (returns new pointer)
void callbackHelper(int* data);        // FUN_004d3b50 - sets up callback context

void StringArray::readEntries() {
    int entryCount;
    int entrySize;
    char buffer[132]; // local_88
    int callbackData[3] = {0, 0, 0}; // local_98
    void (*callbackFunc)() = nullptr; // local_8c

    stream_read(0x20, &entryCount); // read number of entries (DWORD)

    while (entryCount-- > 0) {
        stream_read(0x20, &entrySize); // read size of next data block

        // Read the data block (size*8 bytes) into buffer
        stream_read(entrySize * 8, buffer);
        buffer[entrySize] = '\0'; // null-terminate at the original character count

        // Process the string (e.g., decode from EA encoding)
        char* processedString = stringProcess(buffer);

        // Grow array if full
        if (count == capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            data = (char**)memRealloc(newCapacity * sizeof(char*));
            capacity = newCapacity;
        }

        // Add the processed string to the array
        int idx = count; // save old count
        count++;
        if (data[idx] != nullptr) {
            callbackHelper(callbackData); // potential callback setup (unused logic)
        }
    }

    // If any callback data was accumulated, invoke the callback (not used)
    if (callbackData[0] != nullptr && callbackFunc != nullptr) {
        callbackFunc(callbackData[0]);
    }
}