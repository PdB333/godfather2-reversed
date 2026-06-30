// FUNC_NAME: deactivateEntitiesById
// Address: 0x0051cb10
// Role: Traverses a global linked list of entities and clears bit 29 (0x20000000) in the flags field
// for either all entities (if id == 0) or for ones matching a derived ID computed from offset +0xc4.

void __fastcall deactivateEntitiesById(int /*unused*/, int id)
{
    int* nodePtr = *(int**)0x01205514; // Global head of entity list
    if (nodePtr != 0)
    {
        do
        {
            if (id == 0)
            {
                // Clear bit 29 for all nodes
                *(unsigned int*)(nodePtr + 0xc) &= 0xdfffffff; // +0xc: flags
            }
            else
            {
                int derivedId;
                if (*(int*)(nodePtr + 0xc4) == 0)            // +0xc4: some value (pointer or ID)
                    derivedId = 0;
                else
                    derivedId = *(int*)(nodePtr + 0xc4) - 0x48; // Subtract offset to get ID

                if (id == derivedId)
                {
                    // Clear bit 29 for this node
                    *(unsigned int*)(nodePtr + 0xc) &= 0xdfffffff;
                }
            }
            // Advance to next node
            nodePtr = *(int**)(nodePtr + 0x14); // +0x14: next pointer
        } while (nodePtr != 0);
    }
}