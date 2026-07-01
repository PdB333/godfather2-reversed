// FUNC_NAME: NetConnection::NetConnection
// Address: 0x0089db99
// Role: Constructor for NetConnection class. Initializes vtable, inserts into a global list,
// allocates two PacketWindow objects (send/receive), initializes sequence buffers and flags.

class NetConnection {
public:
    // Vtable pointer at offset 0x00
    void* vtable;

    // Linked list node: next pointer at offset 0x04 (unused in this constructor)
    NetConnection* next;

    // Insertion point: pointer to node after which this is inserted (offset 0x08)
    NetConnection* listPrev;

    // Previous next pointer (offset 0x0C)
    NetConnection* listNext;

    // Padding or other fields at offsets 0x10, 0x14, 0x1C (skipped)
    // Actually offsets 0x10 (16), 0x14 (20), 0x1C (28) are set to null

    // Two PacketWindow objects (size 0x30 each) at offsets 0x18 (24) and 0x20 (32)
    PacketWindow* sendWindow;   // +0x18
    PacketWindow* recvWindow;   // +0x20

    // Fields at offsets 0x30 (48), 0x34 (52), 0x38 (56), 0x3C (60)
    uint32_t field_0x30;        // +0x30, initialized to 0
    uint32_t field_0x34;        // +0x34, initialized from global DAT_00d5f204
    uint32_t field_0x38;        // +0x38, initialized to 0
    uint32_t field_0x3C;        // +0x3C, initialized from global _DAT_00d5780c

    // Two arrays of 0x98 bytes each (38 uint32_t elements)
    uint32_t sendSequenceBuffer[38];  // +0x40 (offset 0x10 * 4)
    uint32_t recvSequenceBuffer[38];  // +0xD8 (offset 0x36 * 4)

    // Byte flags at offsets 0x170 and 0x171
    uint8_t flag_0x170;         // +0x170
    uint8_t flag_0x171;         // +0x171

    // Constructor
    // insertAfter: pointer to a node in a global list after which this connection is inserted.
    // If null, no insertion (but the code checks ZF from previous operation).
    __thiscall NetConnection(NetConnection* insertAfter) {
        // Set vtable (class-specific)
        this->vtable = &PTR_FUN_00d78694;

        // Initialize linked list pointers
        this->next = nullptr;           // offset 0x04
        this->listPrev = insertAfter;   // offset 0x08 (if insertAfter is null, set to null)
        this->listNext = nullptr;       // offset 0x0C

        // If insertAfter is not null, insert this node after it
        if (insertAfter != nullptr) {
            this->listNext = insertAfter->listNext;  // save old next
            insertAfter->listNext = &this->listPrev; // point to this node's listPrev field
        }

        // Clear other fields
        this->field_0x10 = nullptr;  // offset 0x10
        this->field_0x14 = nullptr;  // offset 0x14
        this->field_0x1C = nullptr;  // offset 0x1C

        // Allocate first PacketWindow (send)
        PacketWindow* newWindow = (PacketWindow*)FUN_004eb390(0x30, 0x10);
        uint32_t defaultValue = _DAT_00d5780c;  // global default value

        if (newWindow == nullptr) {
            newWindow = nullptr;
        } else {
            newWindow->vtable = &PTR_FUN_00e372b4;
            newWindow->refCount = 0;            // offset 0x04
            newWindow->field_0x20 = nullptr;    // offset 0x20 (8th uint32)
            newWindow->field_0x10 = defaultValue; // offset 0x10
            newWindow->field_0x14 = defaultValue; // offset 0x14
            newWindow->field_0x18 = defaultValue; // offset 0x18
            newWindow->field_0x1C = defaultValue; // offset 0x1C
        }
        this->sendWindow = newWindow;
        if (newWindow != nullptr) {
            newWindow->refCount++;  // increment reference count
        }

        // Allocate second PacketWindow (receive)
        newWindow = (PacketWindow*)FUN_004eb390(0x30, 0x10);
        if (newWindow == nullptr) {
            newWindow = nullptr;
        } else {
            newWindow->vtable = &PTR_FUN_00e372b4;
            newWindow->refCount = 0;
            newWindow->field_0x20 = nullptr;
            newWindow->field_0x10 = defaultValue;
            newWindow->field_0x14 = defaultValue;
            newWindow->field_0x18 = defaultValue;
            newWindow->field_0x1C = defaultValue;
        }
        this->recvWindow = newWindow;
        if (newWindow != nullptr) {
            newWindow->refCount++;
        }

        // Initialize fields at offsets 0x30-0x3C
        this->field_0x30 = 0;
        this->field_0x34 = DAT_00d5f204;  // another global
        this->field_0x38 = 0;
        this->field_0x3C = defaultValue;

        // Zero out the two sequence buffers
        memset(this->recvSequenceBuffer, 0, sizeof(this->recvSequenceBuffer)); // offset 0xD8
        this->flag_0x170 = 0;  // clear flag

        memset(this->sendSequenceBuffer, 0, sizeof(this->sendSequenceBuffer)); // offset 0x40
        this->flag_0x171 = 0;  // clear flag

        // Return this pointer
        return this;
    }
};

// PacketWindow class (size 0x30 = 48 bytes)
class PacketWindow {
public:
    void* vtable;           // +0x00
    int refCount;           // +0x04
    // Fields at offsets 0x10, 0x14, 0x18, 0x1C, 0x20
    uint32_t field_0x10;    // +0x10
    uint32_t field_0x14;    // +0x14
    uint32_t field_0x18;    // +0x18
    uint32_t field_0x1C;    // +0x1C
    void* field_0x20;       // +0x20
    // Remaining 0x30 - 0x24 = 0xC bytes padding or other fields
};