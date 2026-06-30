// FUNC_NAME: someClass::processRange

// Reconstructed from Ghidra decompile at 0x0061e4e0
// Iterates over a range of elements (index from this+0x30 to this+0x34-1)
// Updates two output pointers (this+0x50 and this+0x58) per element, then calls per-element handler.
// Offsets:
//   +0x08 : elementIntCount (number of ints per element in primary array) -> primaryStride = elementIntCount * 4
//   +0x0C : secondaryElementStride (byte offset per element in secondary array)
//   +0x30 : startIndex (current processing position)
//   +0x34 : endIndex (one past last index to process)
//   +0x38 : dirtyFlag (set to 0 at start)
//   +0x40 : primaryBase (pointer to primary array of (elementIntCount*4)-byte elements)
//   +0x48 : secondaryBase (pointer to secondary array of secondaryElementStride-byte elements)
//   +0x50 : output pointer for primary element (set to primaryBase + index * primaryStride)
//   +0x58 : output pointer for secondary element (set to secondaryBase + index * secondaryElementStride)

class someClass {
public:
    void __thiscall processRange();
};

void someClass::processRange() {
    int currentIndex = *(int*)((char*)this + 0x30);      // start index
    int endIndex = *(int*)((char*)this + 0x34);          // end index
    int elementIntCount = *(int*)((char*)this + 0x08);   // number of ints per primary element
    int secondaryElementStride = *(int*)((char*)this + 0x0C); // byte stride for secondary array

    int primaryStride = elementIntCount * 4; // in bytes
    int* primaryBase = *(int**)((char*)this + 0x40);
    int* secondaryBase = *(int**)((char*)this + 0x48);

    *(int*)((char*)this + 0x38) = 0; // clear dirty flag

    if (currentIndex < endIndex) {
        int primaryOffset = currentIndex * primaryStride;
        do {
            // Set output pointers for this element
            *(int**)((char*)this + 0x58) = (int*)((char*)secondaryBase + secondaryElementStride * currentIndex);
            *(int**)((char*)this + 0x50) = (int*)((char*)primaryBase + primaryOffset);

            // Call per‑element processing function (address 0x0061e410)
            FUN_0061e410(currentIndex);

            currentIndex++;
            primaryOffset += primaryStride;
        } while (currentIndex < endIndex);
    }
    // Note: this+0x30 (startIndex) is not updated after loop – caller must manage range.
}