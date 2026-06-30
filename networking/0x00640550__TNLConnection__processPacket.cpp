// FUNC_NAME: TNLConnection::processPacket
void __thiscall TNLConnection::processPacket(int sequenceNum, int dataValue, int packetType, bool isReliable)
{
    int *stream = reinterpret_cast<int *>(this->m_stream); // this[7] – pointer to internal stream
    // Reset stream state
    resetStream(); // FUN_0063def0

    if (this->m_state == 0x103) // expected state: "packet building ready"
    {
        // Copy expected sequence
        this->m_expectedSequence = this->m_lastSequence; // this[1]->this[2]

        if (this->m_packetType == 0x11f) // "header pending" constant
        {
            // Read actual packet type from stream data
            this->m_state = readPacketType(stream + 4); // FUN_00639c70
        }
        else
        {
            // Move to next state
            this->m_state = this->m_packetType;
            this->m_stateData = this->m_extraData;
            this->m_packetType = 0x11f;
        }

        // ---- Temporary stack buffer for header checking ----
        int tempBuffer[3];
        tempBuffer[1] = 0x1; // local_18
        tempBuffer[2] = 0xFFFFFFFF; // local_28[1]
        tempBuffer[3] = stream[0xD]; // +0x34

        int local_1c = 0; // unused except init

        tempBuffer[0] = stream[5]; // +0x14
        stream[5] = reinterpret_cast<int>(tempBuffer); // store stack address (dangerous)

        int backupStreamOffset = stream[6]; // saved EBP
        stream[7] = backupStreamOffset;

        int *pStreamData = reinterpret_cast<int *>(this->m_stream);
        int local_4 = 0;
        int local_10 = 0xFFFFFFFF;
        int local_c = *(reinterpret_cast<int *>(reinterpret_cast<char *>(pStreamData) + 0x34));
        int local_8 = 0;
        int local_14 = *(reinterpret_cast<int *>(reinterpret_cast<char *>(pStreamData) + 0x14));
        *reinterpret_cast<int **>(reinterpret_cast<char *>(pStreamData) + 0x14) = &local_14;

        // Write packet header and send
        writePacketHeader(); // FUN_006417c0
        flushWrite(); // FUN_0063e400
        sendPacket(stream); // FUN_00642880

        this = reinterpret_cast<TNLConnection *>(stream); // reassign this

        if (isReliable)
        {
            int extraData = *reinterpret_cast<int *>(stream[3] + 8); // stream[3] + 8
            int code = (sequenceNum << 24) | 0x7FFF9C;
            goto label_sendAndLog;
        }
    }
    else
    {
        // State mismatch: print error
        char *errorMsg = formatString("`%s' expected", g_errorString); // FUN_00636c00
        debugLog(errorMsg); // FUN_00638b80
        isReliable = m_savedFlag; // carry over from previous (unaff_EBX)
        stream = reinterpret_cast<int *>(this); // use current object as stream
    }

    // Common path: prepare data and log
    {
        int extraData = *reinterpret_cast<int *>(this->m_state + 8);
        int code = (packetType * 0x40 - 0xBF) | (sequenceNum << 24) | 0x1D;
    label_sendAndLog:
        debugLog(code, extraData); // FUN_006438e0

        // Store the data value into the output array
        // array = *(this->field0 + 0x14), index = this->field6 - 1
        int *arrayBase = reinterpret_cast<int *>(*reinterpret_cast<int *>(this) + 0x14);
        arrayBase[this->m_count - 1] = dataValue;

        if (!isReliable)
        {
            int statePtr = this->m_state;
            *stream = -1; // mark stream as finished
            debugLog(0x7FFF94, *reinterpret_cast<int *>(statePtr + 8));
            sendPacket(this); // FUN_00642880
        }

        if (backupStreamOffset == this->m_count)
        {
            this->m_streamIndex = this->m_count;
            sendPacket(this);
            flushWrite();
            return;
        }

        acknowledgePacket(this, backupStreamOffset, 0xFF, backupStreamOffset, 0xFF, backupStreamOffset);
        flushWrite();
    }
}