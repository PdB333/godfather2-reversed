// FUNC_NAME: InGameVideoPlayer::InGameVideoPlayer
// Address: 0x008f0ee0
// Role: Constructor for InGameVideoPlayer class. Initializes base class, vtable, and registers pause/unpause video messages.

// Note: FUN_0046c590 is likely a base class constructor (e.g., EARSObject or similar).
// FUN_00408240 is likely a message registration function (e.g., registerMessage).

class InGameVideoPlayer {
public:
    // Constructor
    InGameVideoPlayer(void* param2) {
        // Call base class constructor
        FUN_0046c590(param2);

        // Set vtable pointer (offset +0x00)
        *reinterpret_cast<void**>(this) = &PTR_FUN_00d80ec0;

        // Initialize various fields
        // +0x3C (offset 0x0F * 4)
        this->field_0x3C = &PTR_LAB_00d80eb0;
        // +0x48 (offset 0x12 * 4)
        this->field_0x48 = &PTR_LAB_00d80eac;
        // +0x50 (offset 0x14 * 4)
        this->field_0x50 = 0;
        // +0x54 (offset 0x15 * 4) - short
        *reinterpret_cast<short*>(reinterpret_cast<char*>(this) + 0x54) = 0;
        // +0x56 (offset 0x56) - short
        *reinterpret_cast<short*>(reinterpret_cast<char*>(this) + 0x56) = 0;
        // +0x58 (offset 0x16 * 4)
        this->field_0x58 = 0;
        // +0x5C (offset 0x17 * 4) - short
        *reinterpret_cast<short*>(reinterpret_cast<char*>(this) + 0x5C) = 0;
        // +0x5E (offset 0x5E) - short
        *reinterpret_cast<short*>(reinterpret_cast<char*>(this) + 0x5E) = 0;

        // Register pause/unpause video messages
        registerMessage(&DAT_0112ddf8, "iMsgPauseInGameVideo");
        registerMessage(&DAT_0112ddf0, "iMsgUnpauseInGameVideo");
    }

private:
    // Helper function for message registration (FUN_00408240)
    void registerMessage(void* msgData, const char* msgName);

    // Fields (offsets relative to this)
    // +0x00: vtable pointer
    // +0x3C: pointer (PTR_LAB_00d80eb0)
    // +0x48: pointer (PTR_LAB_00d80eac)
    // +0x50: int (0)
    // +0x54: short (0)
    // +0x56: short (0)
    // +0x58: int (0)
    // +0x5C: short (0)
    // +0x5E: short (0)
    void* field_0x3C;
    void* field_0x48;
    int field_0x50;
    short field_0x54;
    short field_0x56;
    int field_0x58;
    short field_0x5C;
    short field_0x5E;
};