// FUNC_NAME: AsyncLoader::processLoad
// Address: 0x004cae60
// Role: Processes an asynchronous load operation using a stream interface.
// The object holds a pointer to an IStream (or similar) at offset 0x04 and a result at offset 0x08.
// Virtual call indices: 0x08=vtable[2] (begin), 0x04=vtable[1] (process), 0x0C=vtable[3] (end).

class AsyncLoader {
public:
    // Offset 0x00: vtable pointer (assumed)
    // Offset 0x04: IStream* m_pStream
    // Offset 0x08: int m_nResult

    void __thiscall processLoad(void* pStream, void* pData) {
        // pStream is a pointer to an object with virtual functions.
        // pData is the data source (e.g., buffer, filename pointer).

        // Store the stream pointer in the object.
        this->m_pStream = static_cast<IStream*>(pStream);

        // Begin the stream operation.
        this->m_pStream->vtable_begin(); // vtable offset 0x08

        if (pData != nullptr) {
            // Load data from pData into the stream.
            // FUN_004265d0 is likely a load function: returns result.
            this->m_nResult = LoadData(pData, this->m_pStream);

            // Process the loaded data.
            // vtable offset 0x04: function takes (pData, 0)
            // The second argument 0 might indicate mode or offset.
            this->m_pStream->vtable_process(pData, 0);

            // End the stream operation.
            this->m_pStream->vtable_end(); // vtable offset 0x0C
        } else {
            // No data: set result to 0 and end.
            this->m_nResult = 0;
            this->m_pStream->vtable_end(); // vtable offset 0x0C
        }
    }
};

// Note: The actual virtual function signatures and LoadData are unknown,
// but the logic is preserved. The class is likely part of the EA EARS engine's async loading system.