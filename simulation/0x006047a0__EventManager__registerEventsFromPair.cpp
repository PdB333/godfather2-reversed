// FUNC_NAME: EventManager::registerEventsFromPair
void EventManager::registerEventsFromPair(undefined2* eventPair[2]) {
    // Allocate two event structures (each 4 bytes = two shorts)
    undefined2* event1 = (undefined2*)FUN_009c8e50(4);
    event1[0] = 0x1E; // Event ID 30
    event1[1] = 0;   // Flags/padding

    undefined2* event2 = (undefined2*)FUN_009c8e50(4);
    event2[0] = 0x1F; // Event ID 31
    event2[1] = 0;

    // Register first event: event1, count=1, callback=eventPair[0], context=eventPair[1]
    FUN_004dbf70(event1, 1, eventPair[0], eventPair[1]);

    // Register second event: expects similar but parameters appear swapped in decompilation
    // Likely intended as: FUN_004dbf70(event2, 1, eventPair[1], eventPair[0]) but decompiler misordered
    // Due to calling convention ambiguity, we assume a consistent pattern.
    FUN_004dbf70(event2, 1, eventPair[1], eventPair[0]); // Reconstructed based on symmetry

    // Conditional cleanup for temporary array (compiler lifetime guard)
    undefined2* tempArray = eventPair; // local_28 equivalent
    if (eventPair != &tempArray) { // param_1 != &local_28
        if (tempArray == nullptr) {
            tempArray = (undefined2*)&DAT_00e2df14; // fallback static data
        }
        FUN_004dbb10(tempArray, 0, 0); // presumably a reference count or lock operation
    }

    // Invoke function pointers if set (from registration?)
    if (tempArray != nullptr) {
        (*((code**)&event1[2]))(tempArray); // local_1c: code* from event1?
    }
    if (event2 != nullptr) { // local_18 != 0 check
        (*((code**)local_18))(local_14); // local_c: code* from event2? local_c = (code*)*local_18?
    }

    // Free allocated event structures
    thunk_FUN_009c8eb0(event2);
    thunk_FUN_009c8eb0(event1);
}