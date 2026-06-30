// FUNC_NAME: EARSVector::consolidate

#include <cassert>

// Offset 0x08: pointer to begin of element data (uint as address)
// Offset 0x0C: pointer to end of element data (uint as address)
// Element size is 0x28 (40 bytes)

struct Range {
    uint32_t start;
    uint32_t end;
};

void EARSVector::consolidate() {
    uint32_t beginPtr = *(uint32_t*)(this + 0x08);
    if (beginPtr == 0) {
        return;
    }

    uint32_t endPtr = *(uint32_t*)(this + 0x0C);
    int32_t byteDiff = (int32_t)(endPtr - beginPtr);
    int32_t elementCount = byteDiff / 0x28;

    // If there are no elements, nothing to do
    if (elementCount == 0) {
        return;
    }

    // Sanity checks: end must be >= begin
    if (endPtr < beginPtr) {
        assert(false); // FUN_00b97aea
    }

    // Create a temporary range from current data (likely used for iteration)
    Range tempRange;
    getRange(&tempRange, 0); // FUN_005da4d0(local_c, 0)

    // Process elements: compact or move them within the container
    processElements(this, tempRange.start, tempRange.end, this, endPtr); // FUN_005da180
}