// FUNC_NAME: CommandBuffer::pushMixOperations
// Address: 0x00468040
// Reconstructed C++ code for EA EARS engine mixer command buffer builder

class CommandBuffer {
public:
    // Internal structure (size unknown)
    // +0x00: unknown (likely vtable or similar)
    // +0x04: unknown
    // +0x08: stack pointer (command entry pointer) - int
    // +0x0C: unknown
    // +0x10: pointer to allocator/descriptor (CheckBufferSpace uses +0x20 & +0x24)
    // +0x40: temporary storage area for pairExtraData
};

// Function prototypes (callees)
void pushCommandName(CommandBuffer* self, const char* commandName); // FUN_00625ca0
void handleBufferOverflow(); // FUN_00627360 - assert/error
CommandEntry* allocateCommandEntry(int unknown); // FUN_00638110 - returns a new command entry with size? "0" param
void pairExtraData(void* tempArea, int startStackPos, int endStackPos); // FUN_00633d60 - links command data

// Command entry structure (allocated via allocateCommandEntry)
struct CommandEntry {
    // +0x00: possibly type/size
    // +0x04: unknown
    // +0x08: unknown
    // +0x0C: function pointer to command handler
};

void __thiscall CommandBuffer::pushMixOperations() {
    CommandEntry* entry;
    int currentStackPos; // local variable holding stack pointer from this+0x08
    int* stackPtr;
    void* tempArea; // this+0x40

    // ---- SetMixValues ----
    pushCommandName(this, "SetMixValues");

    // Check buffer space: if allocator descriptor indicates overflow, call error handler
    if (*(unsigned int*)(*(int*)(this + 0x10) + 0x20) <= *(unsigned int*)(*(int*)(this + 0x10) + 0x24)) {
        handleBufferOverflow();
    }

    entry = allocateCommandEntry(0);
    entry->handler = FUN_00468290; // handler for SetMixValues

    stackPtr = *(int**)(this + 8);
    stackPtr[1] = entry;  // store entry in command stack
    *stackPtr = 6;        // command type (6 = mixer command)

    // Advance stack pointer by 8 bytes (one command slot)
    *(int*)(this + 8) = *(int*)(this + 8) + 8;

    tempArea = (void*)(this + 0x40);
    pairExtraData(tempArea, *(int*)(this + 8) - 0x10, *(int*)(this + 8) - 8);
    // Decrement stack by 0x10 (undo? or finalize pairing?)
    *(int*)(this + 8) = *(int*)(this + 8) - 0x10;

    // ---- ApplyMix ----
    pushCommandName(this, "ApplyMix");
    if (*(unsigned int*)(*(int*)(this + 0x10) + 0x20) <= *(unsigned int*)(*(int*)(this + 0x10) + 0x24)) {
        handleBufferOverflow();
    }

    entry = allocateCommandEntry(0);
    entry->handler = FUN_00468540; // handler for ApplyMix

    stackPtr = *(int**)(this + 8);
    stackPtr[1] = entry;
    *stackPtr = 6;
    *(int*)(this + 8) = *(int*)(this + 8) + 8;

    pairExtraData(tempArea, *(int*)(this + 8) - 0x10, *(int*)(this + 8) - 8);
    *(int*)(this + 8) = *(int*)(this + 8) - 0x10;

    // ---- RemoveMix ----
    pushCommandName(this, "RemoveMix");
    if (*(unsigned int*)(*(int*)(this + 0x10) + 0x20) <= *(unsigned int*)(*(int*)(this + 0x10) + 0x24)) {
        handleBufferOverflow();
    }

    entry = allocateCommandEntry(0);
    entry->handler = FUN_00468680; // handler for RemoveMix

    stackPtr = *(int**)(this + 8);
    stackPtr[1] = entry;
    *stackPtr = 6;
    *(int*)(this + 8) = *(int*)(this + 8) + 8;

    pairExtraData(tempArea, *(int*)(this + 8) - 0x10, *(int*)(this + 8) - 8);
    *(int*)(this + 8) = *(int*)(this + 8) - 0x10;

    // ---- SetMasterVolume ----
    pushCommandName(this, "SetMasterVolume");
    if (*(unsigned int*)(*(int*)(this + 0x10) + 0x20) <= *(unsigned int*)(*(int*)(this + 0x10) + 0x24)) {
        handleBufferOverflow();
    }

    entry = allocateCommandEntry(0);
    entry->handler = &LAB_004687e0; // handler for SetMasterVolume (address of label)

    stackPtr = *(int**)(this + 8);
    stackPtr[1] = entry;
    *stackPtr = 6;
    *(int*)(this + 8) = *(int*)(this + 8) + 8;

    pairExtraData(tempArea, *(int*)(this + 8) - 0x10, *(int*)(this + 8) - 8);
    *(int*)(this + 8) = *(int*)(this + 8) - 0x10;

    return;
}