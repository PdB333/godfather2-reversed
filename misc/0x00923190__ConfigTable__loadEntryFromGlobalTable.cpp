// FUNC_NAME: ConfigTable::loadEntryFromGlobalTable

class ConfigTable {
public:
    // Offset +0x48: flag indicating debug logging is enabled
    bool m_bDebugEnabled;
    // Offset +0x50: buffer holding 19 int32 values (0x4C bytes)
    int m_dataBuffer[19];  // actually stored as 19 dwords

    void loadEntryFromGlobalTable(int index);
};

// Global table of configuration entries: each entry is 19 int32 values
// Base address: 0x00e54db8
extern const int g_configDataTable[];  // each entry occupies 19 * 4 = 0x4C bytes

void __thiscall ConfigTable::loadEntryFromGlobalTable(int index)
{
    bool bDebugEnabled = this->m_bDebugEnabled;
    int *pSrc = (int *)((int)&g_configDataTable + index * 19);
    int *pDst = this->m_dataBuffer;
    
    for (int i = 0; i < 19; i++) {
        *pDst++ = *pSrc++;
    }
    
    if (bDebugEnabled) {
        // Log "Update" with additional parameters (debug level 0, category string)
        logDebug("Update", 0, &DAT_00d86e98, 0);
    }
}