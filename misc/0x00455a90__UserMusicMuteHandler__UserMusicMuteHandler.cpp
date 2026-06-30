// FUNC_NAME: UserMusicMuteHandler::UserMusicMuteHandler
// Address: 0x00455a90
// Role: Constructor for a handler that subscribes to user music mute/unmute events.
// This class uses multiple inheritance (two vtable pointers) and registers itself
// with the message system for "iMsgMuteUserMusic" and "iMsgUnmuteUserMusic" messages.

class UserMusicMuteHandler {
public:
    // +0x08: flag (initialized to 1)
    // +0x0C: counter (initialized to 0)
    // +0x10: hashed identifier derived from constructor parameter
    // +0x14..0x15: two zeroed bytes

    // Constructor: takes a user identifier string (e.g., "currentUser")
    UserMusicMuteHandler(const char* userIdentifier) {
        // Set first base class vtable pointer
        this->vtable1 = (void**)&PTR_LAB_00e319ac;
        // Set second base class vtable pointer (overwrites temporary base vtable)
        this->vtable2 = (void**)&PTR_LAB_00e319b0;

        // Initialize data members
        this->field_0x08 = 1;
        this->field_0x0C = 0;
        *(uint8_t*)((uintptr_t)this + 0x14) = 0; // +0x14 byte
        *(uint8_t*)((uintptr_t)this + 0x15) = 0; // +0x15 byte

        // Hash the user identifier and store it
        this->field_0x10 = hashString(userIdentifier);

        // Register this handler (as a listener at offset 4) for the user-specific message
        registerForMessages((void*)((uintptr_t)this + 4), &DAT_01206940);

        // Register the global message IDs for mute and unmute
        registerMessage(&DAT_0120ea84, hashString("iMsgMuteUserMusic"));
        registerMessage(&DAT_0120ea8c, hashString("iMsgUnmuteUserMusic"));

        // Subscribe to the mute and unmute messages
        if (DAT_0120ea84 != 0) {
            registerForMessages((void*)((uintptr_t)this + 4), &DAT_0120ea84);
        }
        if (DAT_0120ea8c != 0) {
            registerForMessages((void*)((uintptr_t)this + 4), &DAT_0120ea8c);
        }
    }

private:
    // +0x00: first vtable pointer (inherited base 1)
    void** vtable1;
    // +0x04: second vtable pointer (inherited base 2)
    void** vtable2;
    int field_0x08;   // +0x08
    int field_0x0C;   // +0x0C
    int field_0x10;   // +0x10
    uint8_t field_0x14; // +0x14
    uint8_t field_0x15; // +0x15
};

// External symbols (from other compilation units)
extern void* PTR_LAB_00e319ac; // Base 1 vtable
extern void* PTR_LAB_00e319b0; // Base 2 vtable
extern int DAT_01206940; // User-specific message ID or listener target
extern int DAT_0120ea84; // Mute message storage
extern int DAT_0120ea8c; // Unmute message storage

// Helper functions (original addresses in parentheses)
int hashString(const char* str);                      // FUN_004dafd0
void registerForMessages(void* listener, int* msgId);  // FUN_00407e60
void registerMessage(int* storage, int msgHash);       // FUN_00408260