// FUNC_NAME: EARSObject::addChild

// Function at 0x00454030: Adds a child object to this object's children array.
// Checks for duplicates, marks child as "added" (flag at offset +0x3c), propagates
// a flag (offset +0x20) to the child's own children, and resizes the array if needed.
// Offsets used:
//   this:
//     +0x28: int** childrenArray (array of pointers to child objects)
//     +0x2c: int   childrenCount (number of children currently in array)
//     +0x30: int   childrenCapacity (allocated size of childrenArray)
//   child:
//     +0x1c: int   nextChild (pointer to next sibling in internal linked list)
//     +0x20: uint  flags (bitfield; bit 0x10 is set on children of the added child)
//     +0x3c: uint  flags1 (bit 0x1 is set to mark the child as "added")

void __thiscall EARSObject::addChild(EARSObject* child)
{
    uint index = 0;
    // Check if child is already in the array
    if (this->childrenCount != 0) {
        int** arrayPtr = this->childrenArray;
        do {
            if (*arrayPtr == child) {
                if (index != 0xffffffff) {
                    return; // Already present, do nothing
                }
                break;
            }
            index++;
            arrayPtr++;
        } while (index < this->childrenCount);
    }
    // Mark the child as added
    child->flags1 |= 1; // +0x3c
    // Notify the engine (likely marks the scene as dirty)
    // Unknown function at 0x0064d670
    FUN_0064d670();
    // Propagate a flag (0x10) to all children of the added child
    for (EARSObject* subChild = child->firstChild; subChild != 0; subChild = subChild->nextChild) {
        subChild->flags |= 0x10; // +0x20
    }
    // Resize the children array if it's full
    if (this->childrenCount == this->childrenCapacity) {
        int newCapacity = (this->childrenCapacity == 0) ? 1 : this->childrenCapacity * 2;
        // Resize function at 0x004554a0 (likely reallocates array)
        FUN_004554a0(newCapacity);
    }
    // Add the child to the array
    int* slot = this->childrenArray + this->childrenCount;
    this->childrenCount++;
    if (slot != 0) {
        *slot = child;
    }
    return;
}