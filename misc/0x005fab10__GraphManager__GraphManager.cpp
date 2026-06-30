// FUNC_NAME: GraphManager::GraphManager
// Address: 0x005fab10
// Role: Constructor for the graph loading/unloading manager. Initializes internal state, reads graph data from a stream,
// and registers messages for load/unload events. The stream interface provides methods at vtable offsets 0x4, 0x8, 0xc
// (e.g., read, getSize, close). The param_3 parameter indicates whether to allocate and store a data structure (size = param_3 * 16).

class GraphManager {
public:
    // Offsets:
    // +0x00: vtable pointer (set to FUN_00e40808)
    // +0x04: sub-object initialized by FUN_005fb300 (likely a graph loader)
    // +0x08: vtable pointer (initially LAB_00e40818, then overwritten to LAB_00e40814)
    // +0x0c: pointer to input stream (IReadStream*)
    // +0x10: (unused?)
    // ...
    // +0x14 (offset 20): allocated data block (see final if-else)
};

// Forward declarations for known sub-functions
void FUN_005fb300(void* subObj);   // Initialize sub-object at this+0x04
void FUN_005fb610(void* subObj);   // Initialize sub-object at this+0x0c
int FUN_004265d0(undefined4* buf, int* stream); // Read data from stream into buf (likely a buffer of 3 words)
undefined4* FUN_009c8e80(int size); // Allocate memory (size in bytes)
int FUN_004dafd0(const char* name); // Lookup message ID by name
void FUN_00408260(int* msgList, int msgId); // Register message handler

// Global pointer used by the game – stores the single GraphManager instance
GraphManager* g_graphManager; // (DAT_01223524)

// Stream interface with vtable at offset 0. Methods:
// vtable[0] = ? (used as allocator? called with (0xc, &local_14))
// vtable[1] = read (offset 4)
// vtable[2] = getSize or readMore (offset 8)
// vtable[3] = close (offset 0xc)
struct IReadStreamVTable {
    void* (*alloc)(int size, void* context); // offset 0
    int (*read)(void* buffer, int size);     // offset 4
    int (*getSize)(void);                    // offset 8
    void (*close)(void);                     // offset 0xc
};

class IReadStream {
public:
    IReadStreamVTable* vtable;
    // ...
};

// The function corresponds to:
GraphManager* __thiscall GraphManager::GraphManager(GraphManager* this, IReadStream* stream, int param_3) {
    int iVar1;
    undefined4* puVar2;
    undefined4 uVar3;
    undefined4 buf[3]; // local_14, local_10, local_c

    // Initialize fields
    this->field_0x04 = 0;                          // param_1[1] = 0
    this->field_0x08 = &PTR_LAB_00e40818;          // temporary vtable
    g_graphManager = this;                         // DAT_01223524 = this
    this->vtable = &PTR_FUN_00e40808;              // set main vtable
    this->field_0x08 = &PTR_LAB_00e40814;          // final vtable for sub-object
    this->stream = stream;                         // store stream pointer

    buf[0] = 0;
    buf[1] = 0;
    buf[2] = 0;

    // --- First read phase ---
    // Call stream->getSize() (offset 8)
    stream->vtable->getSize();

    // Read data into buf using helper function
    iVar1 = FUN_004265d0(buf, stream);

    // Initialize sub-object at this+0x04 using the read data
    FUN_005fb300(&this->field_0x04);

    if (iVar1 != 0) {
        // If read was successful, call stream->read ? (offset 4) with additional buffer? Actually offset 4 is read.
        stream->vtable->read(iVar1, 0);
    }

    // Close the first read phase? (offset 0xc)
    stream->vtable->close();

    // --- Second read phase ---
    buf[0] = 0;
    buf[1] = 0;
    buf[2] = 0;

    stream->vtable->getSize(); // get size again

    iVar1 = FUN_004265d0(buf, stream);

    // Initialize sub-object at this+0x0c
    FUN_005fb610(&this->field_0x0c);

    if (iVar1 != 0) {
        stream->vtable->read(iVar1, 0);
    }

    stream->vtable->close(); // close second phase

    // Call stream's vtable[2] again (getSize?) after both phases
    stream->vtable->getSize();

    // Logging
    FUN_0049c6e0("GRAPH", 1);

    // Allocate and store an optional data block based on param_3
    if (param_3 == 0) {
        this->dataBlock = 0;
    } else {
        buf[0] = 0;
        buf[1] = 0;
        buf[2] = 0;

        // Call stream's vtable[0] – this is unusual; maybe it's an allocator that takes size and a context buffer
        puVar2 = (undefined4*)stream->vtable->alloc(0xc, &buf);
        if (puVar2 == 0) {
            this->dataBlock = 0;
        } else {
            uVar3 = FUN_009c8e80(param_3 << 4); // Allocate (param_3 * 16) bytes
            *puVar2 = uVar3;                    // Store allocated pointer
            puVar2[1] = 0;
            puVar2[2] = param_3;               // Store the original param_3 (maybe size or count)
            this->dataBlock = puVar2;
        }
    }

    // Register messages for graph load/unload
    int msgLoadId = FUN_004dafd0("iMsgGraphLoadCompleted");
    FUN_00408260(&g_msgGraphLoadCompletedList, msgLoadId);

    int msgUnloadId = FUN_004dafd0("iMsgGraphUnloading");
    FUN_00408260(&g_msgGraphUnloadingList, msgUnloadId);

    return this;
}