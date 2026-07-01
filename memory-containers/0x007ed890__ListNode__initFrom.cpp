// FUNC_NAME: ListNode::initFrom
// Address: 0x007ed890
// Initializes a list node (this) by cloning data from a source description and setting up self-referencing links.

int* __thiscall ListNode::initFrom(int* thisPtr, int* source)
{
    // source[0] is a pointer to some data source object (vtable at offset 0)
    // source[1] is a size/count field
    int* dataPtr = reinterpret_cast<int*>(source[0]);
    int dataSize = source[1];

    // Call virtual function at vtable[2] (offset 8) on dataPtr - likely an init/clone method
    (**(code**)(*dataPtr + 8))(dataPtr);

    // Clone the source data if size > 0
    int clonedData;
    if (dataSize == 0) {
        clonedData = 0;
    } else {
        clonedData = FUN_004265d0(dataSize, dataPtr); // creates a copy or allocates
    }

    // Second initialization step with the cloned data
    FUN_007ed5a0(dataPtr, clonedData);

    // Extract a secondary object from thisPtr[1]
    int* subObj = reinterpret_cast<int*>(thisPtr[1]);
    int tempBuf[3]; // temporary 12-byte buffer if subObj is null
    if (subObj == nullptr) {
        tempBuf[0] = 0;
        tempBuf[1] = 0;
        tempBuf[2] = 0;
        subObj = tempBuf;
    }

    // Call virtual function at vtable[9] (offset 0x24) of the object pointed by thisPtr[0]
    // Arguments: 0x24 (size?) and subObj
    int newNode = (*(code**)*thisPtr)[9](0x24, subObj); // func(0x24, subObj)

    if (newNode != 0) {
        *(int*)newNode = newNode;      // set prev pointer to self
        *(int*)(newNode + 4) = newNode; // set next pointer to self
    }

    thisPtr[6] = newNode; // store newly created node
    thisPtr[7] = 0;       // zero flag
    return thisPtr;
}