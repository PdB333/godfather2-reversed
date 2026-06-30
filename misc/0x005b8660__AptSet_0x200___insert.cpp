// FUNC_NAME: AptSet<0x200>::insert
// Address: 0x005b8660
// Role: Inserts an element pointer into a fixed-size linear probing set (capacity 0x200).
// Asserts that current element count is less than capacity before insertion.
// After insertion, if the element is not a sentinel and has certain type bits, calls processElement.

#include <cstdint>

// Forward declaration of helper function
void FUN_0059c230(uint32_t* element); // likely processInsertedElement

// Template class for fixed-size set with linear probing
// _ElementArraySize is the maximum number of elements (0x200 = 512)
template <typename T, uint32_t _ElementArraySize = 0x200>
class AptSet {
public:
    // Field offsets: +0x00: current count (int32)
    //                +0x04: array of pointers to elements (size _ElementArraySize)
    int32_t count;               // +0x00
    T*       elements[_ElementArraySize]; // +0x04

    // Insert an element pointer into the set
    // Asserts count < _ElementArraySize before insertion
    void insert(T* element) {
        if (count > _ElementArraySize - 1) { // 0x1ff = 511
            // Assertion failure: "nElements < _nSize"
            // The crash handler or debug breakpoint
            // In release, this would likely be optimized out or cause a crash.
            // The decompiled code shows a complex assertion block; simplified here.
            return; // or trigger breakpoint
        }

        count++; // increment element count

        int32_t idx = count; // start index = new count? Actually count is incremented before search.
        // Search for an empty slot (null pointer) using linear probing with wrap-around
        while (elements[idx] != nullptr) {
            idx++;
            if (idx >= _ElementArraySize) {
                idx = 0;
            }
        }

        // Store the element pointer in the empty slot
        elements[idx] = element;

        // After insertion, if element is not a sentinel (DAT_0119cbbc), check its type bits
        static const uint32_t* kSentinel = reinterpret_cast<uint32_t*>(0x0119cbbc); // DAT_0119cbbc
        if (element != kSentinel) {
            uint32_t elementFlags = *element; // first field of the element object
            uint32_t typeId = elementFlags & 0x7FFF; // lower 15 bits
            bool isFlagSet = (elementFlags >> 0xF) & 1; // bit 15
            // Call processElement unless typeId is a special type (0x19, 0x0B, 0x18, 0x17) or if bit 15 is set and type matches?
            // Condition: (typeId != 0x19) AND ((NOT bit15) OR (typeId != 0x0B && typeId != 0x18 && typeId != 0x17))
            if ((typeId != 0x19) &&
                ((!isFlagSet) ||
                 ((typeId != 0x0B) && (typeId != 0x18) && (typeId != 0x17)))) {
                FUN_0059c230(element); // process the element
            }
        }
    }
};