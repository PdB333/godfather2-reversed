// FUNC_NAME: RegisteredCallbackManager::processCallbacks
// Function address: 0x00699af0
// Role: Iterates over a global array of registered callback structures. For each entry, calls a preparation function, retrieves callback data (id, data, function pointer), invokes the callback if non-null, and returns 1 if any callback indicates it handled the event.

// Assumed types and globals based on decompilation pattern:
// Global pointer list starts at 0x01129f8c, ends at 0x01129f90 (each entry is 4 bytes – a pointer to a callback data struct).
// The callback data struct is a triple: id, data, function pointer.

struct RegisteredCallbackData {
    uint32_t id;         // +0x00
    uint32_t data;       // +0x04
    void (*callback)(uint32_t); // +0x08
};

// Global array of pointers to RegisteredCallbackData
static RegisteredCallbackData** s_callbackListStart; // at 0x01129f8c
static RegisteredCallbackData** s_callbackListEnd;   // at 0x01129f90

class RegisteredCallbackManager {
public:
    // param_1 = unknown (possibly 'this' of owning manager)
    // param_2, param_3 = context data (e.g., event IDs)
    int processCallbacks(uint32_t param1, uint32_t param2, uint32_t param3);

private:
    // Called each iteration, possibly to prepare current callback slot
    void prepareCallbackIteration(); // corresponds to FUN_004d3bc0

    // Retrieves next callback data into the structure, returns non-zero if handled
    char getNextCallback(RegisteredCallbackData& outData, uint32_t param2, uint32_t param3); // FUN_00699840
};

int RegisteredCallbackManager::processCallbacks(uint32_t param1, uint32_t param2, uint32_t param3) {
    if (s_callbackListStart == s_callbackListEnd) {
        return 0;
    }

    RegisteredCallbackData callbackEntry;
    RegisteredCallbackData** current = s_callbackListStart;
    do {
        prepareCallbackIteration();          // FUN_004d3bc0(param1)
        char handled = getNextCallback(callbackEntry, param2, param3); // FUN_00699840

        if (callbackEntry.callback != nullptr) {
            callbackEntry.callback(callbackEntry.id);
        }

        if (handled != 0) {
            return 1;
        }

        current++;  // advance to next pointer in the global array (4 bytes per pointer)
    } while (current != s_callbackListEnd);

    return 0;
}