// FUNC_NAME: EffectRangeConfig::loadFromData

// Reconstructed from Ghidra decompile at 0x006fc700
// This function reads a configuration data block and computes a final range value based on a type selection.

void __thiscall EffectRangeConfig::loadFromData(void* thisPtr, void* dataBuffer)
{
    char isDone;
    int dataType;
    
    // Initialize the data parser
    initDataParser(dataBuffer);
    setChecksum(dataBuffer, 0x559b9832);
    
    // Loop through the data records
    isDone = isDataAvailable();
    while (isDone == '\0') {
        advanceData();                      // skip to next record
        dataType = getDataType();
        if (dataType == 0) {
            dataType = getNextData();       // get pointer to record data
            *(int*)(thisPtr + 0x144) = *(int*)(dataType + 8);   // m_rangeType = record[8]
        }
        else if (dataType == 1) {
            dataType = getNextData();
            *(int*)(thisPtr + 0x148) = *(int*)(dataType + 8);   // m_baseValue = record[8]
        }
        else if (dataType == 2) {
            dataType = getNextData();
            *(int*)(thisPtr + 0x150) = *(int*)(dataType + 8);   // m_unknown = record[8]
        }
        finalizeDataRecord();
        isDone = isDataAvailable();
    }
    
    // Compute the final range based on stored type
    int baseRange;
    switch (*(int*)(thisPtr + 0x144)) {   // m_rangeType
    case 1:
        baseRange = 400;
        break;
    case 2:
        baseRange = 1000;
        break;
    case 3:
        baseRange = 2000;
        break;
    case 4:
        baseRange = 0xa28;   // 2600
        break;
    default:
        baseRange = 0;
    }
    *(int*)(thisPtr + 0x14c) = *(int*)(thisPtr + 0x148) + baseRange;   // m_finalRange = m_baseValue + baseRange
    return;
}