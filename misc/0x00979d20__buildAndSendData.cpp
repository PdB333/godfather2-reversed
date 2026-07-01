// FUNC_NAME: buildAndSendData
// Address: 0x00979d20
// Role: Retrieves data from a manager, constructs a temporary struct with a time offset, and passes it to a processing function.

// Globals (from data references):
// _DAT_00d5780c - unknown int constant
// DAT_00d8bbc8 - float base time offset

// Struct for temporary data (4 fields, 16 bytes)
struct TempData {
    int field0;      // +0x00
    float field1;    // +0x04
    int field2;      // +0x08
    int field3;      // +0x0C
};

// Forward declarations of called functions
void* getDataPointer();                          // FUN_00950b20
void processData(TempData* data, int param2);    // FUN_00979130
void handleNullPointer();                        // FUN_004df650

void buildAndSendData(int param1, int param2) {
    void* dataPtr = getDataPointer();
    if (dataPtr != nullptr) {
        // Interpret the returned data as a struct with at least 3 fields
        int* intData = (int*)dataPtr;
        float* floatData = (float*)dataPtr;

        TempData temp;
        temp.field0 = intData[0];                // first field
        temp.field1 = DAT_00d8bbc8 + floatData[1]; // second field + global offset
        temp.field2 = intData[2];                // third field
        temp.field3 = _DAT_00d5780c;             // global constant

        processData(&temp, param2);
    } else {
        handleNullPointer();
    }
}