// FUNC_NAME: NetConnection::processIncomingPackets
uint __thiscall NetConnection::processIncomingPackets(void* thisPtr)
{
    uint uResult = 0;

    if (thisPtr != 0)
    {
        // Begin processing incoming message with specific message type (0x3302871b)
        beginMessageProcessing(thisPtr, 0x3302871b);

        // Poll until all pending messages are processed
        while (!isProcessingComplete())
        {
            // Advance to the next message in the queue
            advanceToNextMessage();

            // Check the status of the current message
            int iStatus = getMessageStatus();
            if (iStatus == 0) // No error, valid message
            {
                // Retrieve the current message pointer
                void* pMessage = getCurrentMessage();
                // Read the packet type/ID at offset +0x08
                uResult = *(uint*)((int)pMessage + 8);
            }

            // Finalize processing for this message step
            endMessageProcessingStep();
        }
    }

    // Return only the relevant bits (mask out low 2 bits, preserve flags in bits 2-7)
    return uResult & 0xfc;
}