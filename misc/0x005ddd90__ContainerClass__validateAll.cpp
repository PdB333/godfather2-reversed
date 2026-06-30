// FUNC_NAME: ContainerClass::validateAll
// Address: 0x005ddd90
// Role: Iterates over a linked list of objects, calling validation functions on each.
//       Returns true only if all validations succeed.
// Offsets:
//   +0x24: flags byte (bit 0 indicates container is active/valid)
//   +0x28: count (number of items in list)
//   +0x2c: pointer to head of linked list (each node: +0x00 = data, +0x10 = next pointer)

bool __thiscall ContainerClass::validateAll(void* this, bool* outResult)
{
    byte* flagsByte;
    int nodeData;
    char subResult;
    int* currentNode;
    uint index;

    // Read flags
    flagsByte = (byte*)((int)this + 0x24);
    *outResult = true; // Assume success until proven otherwise

    // Check if container is marked as active (bit 0)
    if ((*flagsByte & 1) == 0) {
        return false;
    }

    // Call some preparation function (likely begins iteration)
    FUN_005ddd30();

    currentNode = *(int**)((int)this + 0x2c);
    if (currentNode != nullptr && *(int*)((int)this + 0x28) != 0) {
        index = 0;
        do {
            if (currentNode == nullptr) {
                *outResult = false;
            } else {
                // Validate first data element of the node
                nodeData = FUN_005dc670(*currentNode);
                if (nodeData == 0) {
                    *outResult = false;
                } else {
                    // Additional validation
                    subResult = FUN_005dd510();
                    if (subResult == '\0') {
                        *outResult = false;
                    }
                }
                // Move to next node (offset +0x10 = next pointer)
                currentNode = (int*)currentNode[0x10 / sizeof(int)]; // Actually currentNode[4] because each element is int, 16 bytes offset? Let's adjust: +0x10 = 4 ints offset
                // Assuming pointer size 4, offset 0x10 = 4 elements
            }
            index++;
        } while (index < *(uint*)((int)this + 0x28));
    }

    return *outResult;
}