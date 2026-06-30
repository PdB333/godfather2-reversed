// FUNC_NAME: NetworkSession::attachConnection (0x005e1390)
// This function appears to be part of a network session management class.
// It associates a connection object (param_1) with the current session,
// initializes it via virtual function calls, and optionally creates a stream handle.
// The class has fields at +0x4 (connection pointer) and +0x8 (stream handle).

class NetworkSession {
public:
    // +0x00: (vtable pointer) - likely inherited from some base class
    // +0x04: m_connection (void*) - pointer to the connection object
    // +0x08: m_streamHandle (uint32_t) - handle/ID returned by stream creation

    // __thiscall: this in ECX/EDI (decompiler shows unaff_EDI as this)
    void attachConnection(void* connection, void* param2) {
        m_connection = connection;  // Store connection pointer at this+0x4

        // Call virtual function at vtable offset 8 of connection (index 2)
        // Likely initializes the connection (e.g., onAttach())
        (**(void (__thiscall**)(void*))(*(uint32_t*)connection + 8))(connection);

        if (param2 != 0) {
            // Create a stream handle from the connection and param2
            uint32_t streamHandle = createStreamHandle(param2, m_connection);
            m_streamHandle = streamHandle;  // Store at this+0x8

            // Call virtual function at vtable offset 4 of connection (index 1)
            // Possibly attaches the stream to the connection (e.g., setStream(param2, 0))
            (**(void (__thiscall**)(void*, void*, int))(*(uint32_t*)connection + 4))(connection, param2, 0);

            // Call virtual function at vtable offset 12 of connection (index 3)
            // Likely finalizes the setup (e.g., onComplete())
            (**(void (__thiscall**)(void*))(*(uint32_t*)connection + 12))(connection);
        } else {
            m_streamHandle = 0;  // No stream, set to null

            // Still call the finalization virtual
            (**(void (__thiscall**)(void*))(*(uint32_t*)connection + 12))(connection);
        }
    }

private:
    // External helper function at 0x004265d0
    // Presumably creates a stream object and returns a handle
    uint32_t createStreamHandle(void* param2, void* connection);
};