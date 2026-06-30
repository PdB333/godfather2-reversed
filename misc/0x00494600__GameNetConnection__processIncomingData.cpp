// FUNC_NAME: GameNetConnection::processIncomingData

// Function address: 0x00494600
// Role: Processes incoming data for a game network connection.
// Called with __fastcall, param_1 is this pointer.
// Guard functions around main logic suggest a synchronization mechanism (e.g., mutex lock/unlock).

class GameNetConnection {
public:
    // +0x14: size or count (integer)
    // +0x1c0: pointer to incoming data buffer (non-null when data pending)
    // +0x1d0: internal receive buffer (or offset within receive stream)

    void __fastcall processIncomingData() {
        // Enter critical section / lock:
        FUN_00490b20();

        // If there is data pending to be processed
        if (*(int*)(this + 0x1c0) != 0) {
            // Process received chunk: (size, sourcePtr, destOffset)
            // FUN_0060ad20 likely copies/decrypts data into internal buffer
            FUN_0060ad20(
                *(int*)(this + 0x14),          // size of data
                *(int*)(this + 0x1c0),         // pointer to incoming data
                this + 0x1d0                   // destination in internal buffer
            );
        }

        // Leave critical section / unlock:
        FUN_00494220();

        return;
    }
};