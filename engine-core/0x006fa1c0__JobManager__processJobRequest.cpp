// FUNC_NAME: JobManager::processJobRequest
// Function address: 0x006fa1c0
// Role: Iterates over a linked list of job nodes (starting at this+0x6d4), searches for a matching entry based on a condition check (FUN_004d4b20), extracts a pointer from the node (offset +0x10 minus 0x48), possibly removes the node from the list (via FUN_006f9a10), and then processes the extracted pointer (FUN_006e61a0). The search only occurs if a flag at this+0x6dc is non-zero. After the loop, stores a value from param_2+0x0C into this+0x38.

void __thiscall JobManager::processJobRequest(int this, int jobData)
{
    int currentNode;
    int extractedPtr;
    int condResult;
    int iVar3;
    int dummy;
    char localBuffer[4]; // unused

    // Only proceed if the job list is active
    if (*(int *)(this + 0x6dc) != 0) {
        currentNode = *(int *)(this + 0x6d4); // Head of the linked list
        iVar3 = 0; // Will hold extracted pointer when a match is found
        do {
            int node = currentNode;
            if (currentNode == 0) {
                // End of list: if no match found, return
                if (iVar3 == 0) {
                    return;
                }
                break;
            }
            // Check condition based on some field in jobData
            condResult = FUN_004d4b20(jobData + 0x10);
            if (condResult == 0) {
                // Condition met: extract pointer from node
                iVar3 = *(int *)(node + 0x10); // offset +0x10 in node
                if (iVar3 == 0) {
                    iVar3 = 0;
                } else {
                    iVar3 = iVar3 - 0x48; // Adjust pointer (e.g., container_of cast)
                }
                // Possibly remove node from list (or advance iterator)
                FUN_006f9a10(localBuffer, &currentNode);
            } else {
                // Condition not met: move to next node in list
                currentNode = *(int *)(node + 0x18); // next pointer at +0x18
            }
        } while (iVar3 == 0);

        // Store a value from jobData into this
        *(int *)(this + 0x38) = *(int *)(jobData + 0x0C);
        // Process the extracted pointer
        FUN_006e61a0(iVar3);
    }
    return;
}