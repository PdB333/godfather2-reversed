// FUNC_NAME: Iterator::advance

#include <cassert>

struct Iterator {
    int* container;   // +0x00: pointer to container structure
    int  offset;      // +0x04: current offset (in bytes) within container's data
};

struct ContainerHeader {
    int field_0x00;     // +0x00: unknown
    int field_0x04;     // +0x04: unknown
    int minOffset;      // +0x08: minimum valid offset (inclusive)
    int maxOffset;      // +0x0C: maximum valid offset (exclusive)
    // data follows at offset 0x10 perhaps
};

// Advances the iterator by 'count' elements (each element size = 0x28 = 40 bytes)
Iterator* Iterator::advance(Iterator* result, int count) {
    // Get current container and offset from the implicit 'this' pointer (stored in EAX)
    ContainerHeader* container = reinterpret_cast<ContainerHeader*>(this->container);
    int currentOffset = this->offset;

    // If container is null, trigger assertion
    if (container == nullptr) {
        assertion_failed();  // FUN_00b97aea
    }

    // Compute new offset
    int newOffset = currentOffset + count * 0x28;

    // Validate new offset is within [minOffset, maxOffset)
    if (newOffset < container->minOffset || newOffset > container->maxOffset) {
        assertion_failed();  // FUN_00b97aea
    }

    // Write results into output iterator
    result->container = reinterpret_cast<int*>(container);
    result->offset = newOffset;

    return result;
}