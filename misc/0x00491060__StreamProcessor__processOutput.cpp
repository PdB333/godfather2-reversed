// FUNC_NAME: StreamProcessor::processOutput

class StreamProcessor {
private:
    // Offsets relative to this:
    // +0x14: int m_dataSize
    // +0x1c0: void* m_pSourceData
    // +0x1d0: char m_outputBuffer[?] (address passed as destination)

    void __thiscall baseInit(void); // FUN_00490b20
    void __fastcall copyDataSized(int size, void* src, void* dst); // FUN_0060ad20

public:
    // The method being reconstructed
    void __thiscall processOutput(void) {
        baseInit();

        if (m_pSourceData != nullptr) {
            copyDataSized(m_dataSize, m_pSourceData, &m_outputBuffer);
        }
    }

private:
    // Dummy data members to represent offsets (not true layout, just for clarity)
    int m_dataSize;               // offset +0x14
    // padding
    void* m_pSourceData;          // offset +0x1c0
    char m_outputBuffer;          // offset +0x1d0 (start of buffer)
};