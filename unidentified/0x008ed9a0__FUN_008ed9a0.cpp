// FUNC_NAME: UnknownClass::isolateNode
void __fastcall UnknownClass::isolateNode(int thisPtr)
{
    // thisPtr points to a structure:
    // +0x00: unknown
    // +0x04: pointer to a Node (current node)
    // +0x08: some count (set to 0)
    int *nodePtr = *(int **)(thisPtr + 4);  // Node structure: +0x00: self, +0x04: prev, +0x08: next

    // Cleanup call on the node's previous pointer (before modification)
    FUN_008ed0d0(*(int *)(nodePtr + 4));

    // Set node's prev to itself (self‑circular)
    *(int *)(nodePtr + 4) = (int)nodePtr;

    // Reset the count in the wrapper to 0
    *(int *)(thisPtr + 8) = 0;

    // Self‑loop at offset 0
    *(int *)nodePtr = (int)nodePtr;

    // Set node's next to itself (completing the singlet circular)
    *(int *)(nodePtr + 8) = (int)nodePtr;
}