// FUNC_NAME: DataStreamReader::readTypedTriplets
// Address: 0x00631960
// This function reads three typed float values (types 3, 2, 1) from a binary stream,
// skipping invalid or sentinel entries, and writes the last type and value to an output buffer.

#include <cstdint>

// Forward declarations for external functions
bool isValidNumericValue(float* outValue);
void logMessage(const char* msg);
void debugBreak();

class DataStreamReader {
public:
    // Assumed structure offsets (relative to 'this'):
    // +0x08: uint32_t* outputCursor  (where to write parsed entries)
    // +0x0C: uint32_t* inputBuffer   (pointer to start of input entries?)
    // Each entry is 8 bytes: 4 bytes type (int32) + 4 bytes value (float)

    int32_t readTypedTriplets() {
        int32_t* entryPtr;            // piVar1
        int32_t  searchType;          // iVar3
        int32_t  validationResult;    // iVar2
        double   tempDouble;          // dVar4
        float    value1;              // local_14
        float    value2;              // local_18
        int32_t  tempType;            // local_10
        float    validatedValue;      // local_c

        // Initially, point to the first entry in the input buffer?
        entryPtr = reinterpret_cast<int32_t*>(*reinterpret_cast<int32_t*>(this + 0x0C) + 8);
        searchType = 3;

        // If the output cursor has already passed this entry, or entry is null, go to default
        if (*reinterpret_cast<int32_t**>(this + 0x08) <= entryPtr) goto default_value1;
        if (entryPtr == nullptr) goto default_value1;

        // Check the type of the entry
        if (*entryPtr != 3) {
            if (*entryPtr != 4) goto default_value1;
            validationResult = isValidNumericValue(&value1);
            if (validationResult == 0) goto default_value1;
            tempType = 3;
            validatedValue = value1;
            entryPtr = &tempType;  // Use local dummy to continue processing
        }

        // Extract value from the entry (or dummy)
        value1 = *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(entryPtr) + 4);
        if (value1 == *reinterpret_cast<float*>(0x00e2b05c)) { // Sentinel (0.0f)
            // Loop to find the next valid entry of type searchType (or type 4 with validation)
            while (true) {
                entryPtr = reinterpret_cast<int32_t*>(*reinterpret_cast<int32_t*>(this + 0x0C) + 8);
                if (*reinterpret_cast<int32_t**>(this + 0x08) <= entryPtr || entryPtr == nullptr) {
                    // No more data, break and set default later
                    break;
                }
                if (*entryPtr == searchType) {
                    break; // Found matching type
                }
                if (*entryPtr == 4) {
                    validationResult = isValidNumericValue(&value2);
                    if (validationResult != 0) {
                        // Simulate the same pattern: use a local dummy
                        tempType = searchType;
                        validatedValue = value2;
                        entryPtr = &tempType;
                        break;
                    }
                }
                // If not found, update search type and log
                searchType = 2;
                logMessage("number");
                // Loop continues without explicit progress? Actually the loop is infinite
                // but in practice it will break when conditions are met or when the output cursor passes.
            }
        }
        
    default_value1:
        value1 = 0.0f;  // Default when no valid entry

        // Repeat for searchType = 2
        entryPtr = reinterpret_cast<int32_t*>(*reinterpret_cast<int32_t*>(this + 0x0C));
        if (*reinterpret_cast<int32_t**>(this + 0x08) <= entryPtr) goto default_value2;
        if (entryPtr == nullptr) goto default_value2;
        if (*entryPtr != searchType) {
            if (*entryPtr != 4) goto default_value2;
            validationResult = isValidNumericValue(&value2);
            if (validationResult == 0) goto default_value2;
            validatedValue = value2;
            entryPtr = &tempType;
            tempType = searchType;
        }
        value2 = *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(entryPtr) + 4);
        if (value2 == *reinterpret_cast<float*>(0x00e2b05c)) {
            while (true) {
                entryPtr = reinterpret_cast<int32_t*>(*reinterpret_cast<int32_t*>(this + 0x0C));
                if (*reinterpret_cast<int32_t**>(this + 0x08) <= entryPtr || entryPtr == nullptr) {
                    break;
                }
                if (*entryPtr == searchType) break;
                if (*entryPtr == 4) {
                    validationResult = isValidNumericValue(&tempType);
                    if (validationResult != 0) {
                        entryPtr = &tempType;
                        break;
                    }
                }
                searchType = 1;
                logMessage("number");
            }
        }

    default_value2:
        value2 = 0.0f;

        // Write the final results to output buffer
        entryPtr = *reinterpret_cast<int32_t**>(this + 0x08);
        *entryPtr = searchType;
        tempDouble = static_cast<double>(value2);
        debugBreak();
        *(entryPtr + 1) = static_cast<int32_t>(static_cast<float>(tempDouble));
        *reinterpret_cast<int32_t*>(this + 0x08) = *reinterpret_cast<int32_t*>(this + 0x08) + 8;
        return 1;
    }
};