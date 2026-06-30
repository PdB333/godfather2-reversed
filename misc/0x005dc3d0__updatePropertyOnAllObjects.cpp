// FUNC_NAME: updatePropertyOnAllObjects
undefined4 __thiscall updatePropertyOnAllObjects(int param_1, undefined4 param_2)
{
    int propertyId;
    int currentNode;
    int headNode;
    int containerNode;
    undefined4 *newNode;
    char *propertyName;

    containerNode = param_1;
    propertyName = (char *)*in_EAX;
    if (propertyName == (char *)0x0) {
        propertyName = &DAT_0120546e;  // default property name
    }
    propertyId = FUN_004dafd0(propertyName);  // convert string to property ID

    // If the container has an active list (offset +0xC != 0)
    if (*(int *)(containerNode + 0xc) != 0) {
        newNode = (undefined4 *)FUN_005df050(&propertyId);  // allocate new node for property value
        *newNode = param_2;  // store the value
    }

    // Iterate over object list (offset +0x8 is pointer to list struct, +0x4 is something else)
    if (*(int *)(containerNode + 8) != 0 && *(int *)(containerNode + 4) != 0) {
        // Get head node (sentinel) and first real node
        currentNode = **(int **)(*(int *)(containerNode + 8) + 0x1c);  // first real node
        headNode = *(int *)(*(int *)(containerNode + 8) + 0x1c);      // head sentinel

        while (true) {
            // Check sentinel consistency
            if (currentNode == 0 || currentNode != *(int *)(containerNode + 8)) {
                FUN_00b97aea();  // debug assert
            }
            if (currentNode == headNode) break;  // back to sentinel??
            if (currentNode == 0) {
                FUN_00b97aea();  // debug assert
            }
            if (currentNode == *(int *)(*(int *)(containerNode + 8) + 0x1c)) {
                FUN_00b97aea();  // debug assert
            }
            // If the object referenced by this node (offset +0x10) has matching property ID (0x2b4)
            if (*(int *)(*(int *)(currentNode + 0x10) + 0x2b4) == propertyId) {
                if (currentNode == *(int *)(*(int *)(containerNode + 8) + 0x1c)) {
                    FUN_00b97aea();  // debug assert
                }
                // Set the property value on the object (offset 0x29c)
                *(undefined4 *)(*(int *)(currentNode + 0x10) + 0x29c) = param_2;
            }
            FUN_005e09e0();  // advance to next node (likely modifies currentNode)
        }
        return 1;
    }
    return 0;
}