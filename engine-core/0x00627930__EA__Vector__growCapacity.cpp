// FUNC_NAME: EA::Vector::growCapacity
void EA::Vector::growCapacity(void* container, uint flags, int* capacity, uint elementSize, uint allocatorHandle) {
    int currentCapacity = *capacity;
    int newCapacity;

    if (currentCapacity * 2 < 4) {
        newCapacity = 4;
    } else {
        newCapacity = currentCapacity * 2;
        // Attempt to use the requested capacity if it fits within growth heuristics
        int requestedCapacity; // passed via EAX (not in standard param list)
        if ((requestedCapacity / 2 <= currentCapacity) &&
            (newCapacity = requestedCapacity, (requestedCapacity - 4 <= currentCapacity))) {
            // Assertion failure: requested capacity is too close to current; should request larger growth.
            FUN_00633920(container, allocatorHandle); // error handling / logging
            __debugbreak(); // int3 breakpoint
        }
    }

    FUN_006279a0(currentCapacity * elementSize, newCapacity * elementSize); // reallocate memory
    *capacity = newCapacity;
}