// FUNC_NAME: StreamManager::tryAcquireStreamNode

char __fastcall StreamManager::tryAcquireStreamNode(int this)
{
    int *headPointer;            // pointer to m_headNode field
    int oldHeadNode;             // previous m_headNode
    int newNode;                 // newly acquired node
    char success;                // return value
    int loopCounter;

    success = '\0';
    if (*(int *)(this + 0x88) != 0) // m_streamHandle
    {
        oldHeadNode = *(int *)(this + 0x94); // m_headNode
        headPointer = (int *)(this + 0x94);
        // Save the next pointer (offset +4) of the old head into a temp
        // (likely used to restore later)
        *(undefined4 *)(oldHeadNode + 4) = 0; // actually the decompiler did local_4 = ... and then overwrote, but we ignore local_4
        if (oldHeadNode != 0)
        {
            // Temporarily unlink old head by pointing its 'prev' to stack? This is odd but likely a decompiler artifact.
            // Actually the original code did: *(int **)(oldHeadNode+4) = &oldHeadNode;
            // We'll keep it as is.
            *(int **)(oldHeadNode + 4) = &oldHeadNode;
        }

        loopCounter = 0;
        do
        {
            // Choose which method to acquire a node based on bit 1 of m_flags (offset 0xe4)
            if ((*(unsigned int *)(this + 0xe4) >> 1 & 1) == 0)
            {
                // Method A: get a generic node and initialize it from a buffer
                int base = FUN_00471610();                          // getSomeBaseValue()
                newNode = FUN_006e68b0(base + 0x30, this + 0x58);   // setupNode(base + 0x30, this->m_buffer)
            }
            else
            {
                // Method B: acquire node from a pool using additional parameters
                newNode = FUN_006e6980(
                    *(unsigned int *)(this + 0x88),    // m_streamHandle
                    this + 0xe8,                      // m_nodePool
                    _DAT_0112ae64,                    // global constant
                    this + 0x58,                      // m_buffer
                    _DAT_00e51928                     // global constant
                );
            }

            if (newNode != 0)
            {
                if (newNode != oldHeadNode)
                {
                    // If head has changed, insert newNode as the new head
                    if (*headPointer != newNode)
                    {
                        // Remove the previous head node from the list
                        if (*headPointer != 0)
                        {
                            FUN_004daf90(headPointer); // unlinkNode(headPointer)
                        }
                        // Set new head
                        *headPointer = newNode;
                        // Save newNode's next pointer to m_headNext? Actually offset 0x98
                        *(int *)(this + 0x98) = *(int *)(newNode + 4); // m_headNext
                        // Set newNode's previous pointer to point to the head pointer variable
                        *(int **)(newNode + 4) = headPointer;
                    }
                    // Notify a state change with 1 (e.g., "active")
                    FUN_006e6430(1, *(unsigned int *)(this + 0x88)); // notifyNodeState(1, m_streamHandle)
                }
                success = '\x01';
                break;
            }
            loopCounter = loopCounter + 1;
        } while (loopCounter < 1); // only one attempt

        // Restore previous head state if it changed
        if (oldHeadNode != 0)
        {
            if (oldHeadNode != *headPointer)
            {
                // Notify a state change with 0 (e.g., "inactive")
                FUN_006e6430(0, *(unsigned int *)(this + 0x88)); // notifyNodeState(0, m_streamHandle)
            }
            // Remove the old head node from its temporary unlinked state
            if (oldHeadNode != 0)
            {
                FUN_004daf90(&oldHeadNode); // unlinkNode(&oldHeadNode)
            }
        }

        if (success != '\0')
        {
            return success;
        }
    }

    // Clean up: notify inactive and remove the current head if any
    headPointer = (int *)(this + 0x94);
    if (*(int *)(this + 0x94) != 0)
    {
        FUN_006e6430(0, *(unsigned int *)(this + 0x88)); // notifyNodeState(0, m_streamHandle)
    }
    if (*headPointer != 0)
    {
        FUN_004daf90(headPointer); // unlinkNode(headPointer)
        *headPointer = 0;
    }
    return '\0';
}