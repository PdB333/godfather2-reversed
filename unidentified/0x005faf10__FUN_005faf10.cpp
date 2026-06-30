// FUNC_NAME: FUN_005faf10
// Function address: 0x005faf10
// Role: Hash-based lookup in a linked list of 128-bit GUIDs (4 DWORDS)
// The function takes a this pointer and a pointer to a 4-DWORD key (param_2)
// and searches a linked list at this+0x28 for a matching node.
// Each node has: next pointer (0x0), prev pointer (0x4?), then data at offset 0x8? 
// The actual data being compared is at offset 0x10 within each node's payload.
// Returns the payload pointer if found, 0 otherwise. Uses redundant iterator.

int __thiscall hashBasedGuidLookup(int this, int *key)
{
    int result; // eax: return value
    int *nodeIter; // puVar2: walking the linked list
    int foundResult; // local_14: candidate match

    foundResult = 0;
    // If any of the four key DWORDS are non-zero, search the list
    if ((key[0] != 0) || (key[1] != 0) || (key[2] != 0) || (result = 0, key[3] != 0))
    {
        // Dereference this+0x28 to get head pointer? Or table base?
        nodeIter = *(int **)(*(int **)(this + 0x28) + 0); // get first node (or head)
        // Loop: while nodeIter != the base sentinel at this+0x28
        while (result = foundResult, nodeIter != *(int **)(this + 0x28))
        {
            // Safety check: if nodeIter == base (unlikely after already checked)
            if (nodeIter == *(int **)(this + 0x28))
            {
                FUN_00b97aea(); // assert or crash
            }
            // Dereference offset 0x8? Actually: nodeIter[2] gives payload pointer?
            result = nodeIter[2]; // nodeIter+0x8: pointer to payload?
            // Compare payload's 4 DWORDS (at offset 0x10) with key
            if ((*(int *)(result + 0x10) == key[0]) && 
                (*(int *)(result + 0x14) == key[1]) &&
                ((*(int *)(result + 0x18) == key[2] && 
                  (*(int *)(result + 0x1c) == key[3]))))
            {
                foundResult = result; // store match candidate
            }
            if (nodeIter == *(int **)(this + 0x28))
            {
                FUN_00b97aea();
            }
            nodeIter = (int *)*nodeIter; // advance to next node
            if (foundResult != 0)
            {
                return foundResult;
            }
        }
    }
    return result; // 0 if not found
}