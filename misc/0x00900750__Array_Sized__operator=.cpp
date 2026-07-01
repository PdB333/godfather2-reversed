// FUNC_NAME: Array_Sized::operator=
// This function is a copy assignment operator for a container that stores 12-byte elements.
// The container manages an array of objects (likely handles or pointers) with intrusive linked list linking.
// Layout of container (int*):
//   +0: data (pointer to array of elements)
//   +4: size (number of elements)
//   +8: capacity (allocated element count)
// Each element is 12 bytes:
//   +0: object pointer (int*)
//   +4: next pointer (int*) – stored as pointer to the next pointer in the object itself (linked list)
//   +8: user value (int)

int* __thiscall Array_Sized::operator=(int* thisObj, int* otherObj)
{
    int i;
    int* elementPtr;
    int size;
    int capacity;
    int otherSize;
    int* srcData;
    int* dstElement;
    int objPtr;
    unsigned int idx;

    // Skip self-assignment
    if (thisObj == otherObj) {
        return thisObj;
    }

    // Destroy existing elements in reverse order
    size = thisObj[1] - 1;
    if (size >= 0) {
        do {
            // Each element is 12 bytes. Calculate pointer to element.
            elementPtr = (int*)(thisObj[0] + size * 12);
            if (elementPtr[0] != 0) {
                // Destructor for the object pointed to by the element
                FUN_004daf90(elementPtr);
            }
            size--;
        } while (size >= 0);
    }

    // Resize if capacity is insufficient
    otherSize = otherObj[1];
    if ((uint)thisObj[2] < (uint)otherSize) {
        // Free old data buffer
        FUN_009c8f10(thisObj[0]);
        // Update capacity to match other's size
        thisObj[2] = otherSize;
        // Allocate new data buffer (otherSize * 12 bytes)
        if (otherSize == 0) {
            thisObj[0] = 0;
        } else {
            thisObj[0] = FUN_009c8e80(otherSize * 12);
        }
    }

    // Copy elements from other to this
    idx = 0;
    if (otherSize != 0) {
        srcData = otherObj[0];
        for (;;) {
            dstElement = (int*)(thisObj[0] + idx * 12);
            objPtr = srcData[idx * 3]; // first dword of source element (object pointer)
            dstElement[0] = objPtr;
            dstElement[1] = 0; // reset next pointer initially
            if (objPtr != 0) {
                // Store the address of the next pointer field of the object (at objPtr+4)
                dstElement[1] = (int)(objPtr + 4); // pointer to object's "next" field
                // Update the object's next pointer to point back to this element
                *(int**)(objPtr + 4) = dstElement;
            }
            // Copy the third dword (user value)
            dstElement[2] = srcData[idx * 3 + 2];
            idx++;
            if (idx >= (uint)otherSize) break;
        }
    }

    // Update size to match other
    thisObj[1] = otherSize;
    return thisObj;
}