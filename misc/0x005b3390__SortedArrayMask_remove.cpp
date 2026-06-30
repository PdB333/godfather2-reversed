// Xbox PDB: SortedArrayMask::remove
// FUNC_NAME: AptDisplayList::removeElement
// Function address: 0x005b3390
// Removes an element at the given index from the display list array.
// Shifts subsequent elements left by one and decrements the element count.

void AptDisplayList::removeElement(int index)
{
    // Assert: index must be within valid range [0, nElements)
    if ((index < 0) || (index >= this->nElements))  // this->nElements at offset +0x80
    {
        // Assertion failure: "i >= 0 && i < nElements"
        // File: ..\source\Apt\AptDisplayList.cpp, line 0x273 (627)
        // Trigger debug break or abort
        char* assertMsg = "i >= 0 && i < nElements";
        char* assertFile = "..\\source\\Apt\\AptDisplayList.cpp";
        int assertLine = 0x273;
        int assertType = 2;  // likely assertion type
        // ... (assertion handling code omitted for clarity)
        // In release builds, this would be removed.
        // The original code uses a debug assertion macro.
        // We'll just return or crash.
        return;  // or __debugbreak()
    }

    // Shift elements left to fill the gap
    int count = this->nElements;
    if (index < count - 1)
    {
        do {
            this->elements[index] = this->elements[index + 1];  // each element is 4 bytes (undefined4)
            index++;
        } while (index < count - 1);
    }

    // Decrement element count
    this->nElements--;
}