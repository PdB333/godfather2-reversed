// FUNC_NAME: GameConnection::GameConnection

class GameConnection {
public:
    GameConnection(int connectionId);
    // Virtual table at offset 0
    // Fields:
    // +0x00: vtable pointer (void*)
    // +0x3C: function pointer (void*)
    // +0x48: function pointer (void*)
    // +0x50: union: first byte flag, then function pointer (void*)
    // +0x144: connection state (int)
    // +0x148: some count (int)
    // +0x14C: other count (int)
    // +0x150: pointer to global system (int)
};

// Base class constructor call (FUN_00473f10) – assumed to be BaseConnection
void BaseConnection(int id);

GameConnection::GameConnection(int connectionId) {
    // Call base class constructor with the provided id
    BaseConnection(connectionId);

    // Load global value used later
    int globalPointer = *reinterpret_cast<int*>(0x00d5780c);

    // Initialize byte at +0x50 to 0 (will be overwritten by function pointer)
    *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this) + 0x50) = 0;

    // Clear two fields at +0x148 and +0x14C
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x148) = 0;
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x14C) = 0;

    // Set the virtual table pointer
    *reinterpret_cast<void**>(this) = reinterpret_cast<void*>(0x00d60c30);

    // Set three function pointers (packet/event handlers)
    *reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x3C) = reinterpret_cast<void*>(0x00d60c20);
    *reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x48) = reinterpret_cast<void*>(0x00d60c1c);
    *reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x50) = reinterpret_cast<void*>(0x00d60c18);

    // Set connection state to 2 (e.g., Connected)
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x144) = 2;

    // Store the global pointer (likely some system singleton)
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x150) = globalPointer;
}