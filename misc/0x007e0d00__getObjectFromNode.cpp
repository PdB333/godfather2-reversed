// FUNC_NAME: getObjectFromNode
// Address: 0x007e0d00
// Role: Retrieves an object pointer from an internal node pointer. Checks if the node at +0x104 exists,
//       then returns the node address minus 0x48 (likely offset to containing structure).
int __fastcall getObjectFromNode(int param_1)
{
    // +0x104: pointer to child node or internal data structure
    if (*(int *)(param_1 + 0x104) != 0) {
        // Subtract 0x48 to get the container object's address
        return *(int *)(param_1 + 0x104) - 0x48;
    }
    return 0;
}