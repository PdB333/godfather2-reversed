// FUNC_NAME: GraphLoader::GraphLoader
class GraphLoader {
public:
    struct SubObject1 { /* unknown */ };
    struct SubObject2 { /* unknown */ };

    // +0x00: vtable pointer
    // +0x04: subObject1
    // +0x08: subObject2 vtable? actually a second vtable pointer at +0x08 (maybe for a base class)
    // +0x0C: archive pointer (Archive*)
    // +0x50: buffer (uint8_t*) and count (the size/16? stored in buffer)
    // +0x54: end of object? 

    // Global singleton pointer:
    static GraphLoader* s_pInstance; // DAT_01223524

    // Constructor
    GraphLoader(Archive* archive, int arg3);
};

// Global singleton
GraphLoader* GraphLoader::s_pInstance = nullptr;

// Archive class with virtual methods (assuming vtable layout):
class Archive {
public:
    virtual ~Archive() {}
    virtual void read(void* data, int size) = 0; // vtable[1]? Actually called with (code)(*param_2+4) -- that's vtable[1] (destructor? no, they call it with parameter 0 after reading)
    virtual void beginRead() = 0; // vtable[2] (called with (code)(*param_2+8))
    virtual void endRead() = 0; // vtable[3] (called with (code)(*param_2+0xc))
    // Maybe other methods
};

GraphLoader* GraphLoader::GraphLoader(Archive* archive, int arg3) {
    // Initialize members
    this->subObject1.someField = 0; // offset +0x04
    this->vtable2 = &VTABLE_00e40818; // offset +0x08
    s_pInstance = this; // store globally
    this->vtable = &VTABLE_00e40808; // offset +0x00
    this->vtable2 = &VTABLE_00e40814; // offset +0x08 (overwrites)
    this->archive = archive; // offset +0x0C

    // Local serialization context
    struct SerialContext { int a, b, c; } ctx = {0,0,0}; // local_14,local_10,local_c

    // Read first sub-object (subObject1)
    archive->beginRead();
    int result = FUN_004265d0(&ctx, archive); // likely reads some data from archive into ctx
    FUN_005fb300(&this->subObject1); // initialize subObject1
    if (result != 0) {
        archive->read(result, 0); // vtable[1] with data pointer and 0?
    }
    archive->endRead();

    // Read second sub-object (subObject2) at offset +0x0C
    ctx = {0,0,0};
    archive->beginRead();
    result = FUN_004265d0(&ctx, archive);
    FUN_005fb610(&this->subObject2); // initialize subObject2 (starts at this+0x0C)
    if (result != 0) {
        archive->read(result, 0);
    }
    archive->endRead();

    // Call a virtual method on the archive? Actually it's calling via archive->vtable[2] again? But archive is this->archive, and we have code: (**(code **)(*(int *)param_1[3] + 8))() which is archive->vtable[2] again.
    archive->beginRead(); // or some other method

    // Set up logging
    FUN_0049c6e0("GRAPH", 1);

    // Handle arg3: allocate buffer if non-zero
    if (arg3 == 0) {
        this->bufferPtr = nullptr; // +0x50
    } else {
        // Allocate buffer and store some info
        ctx = {0,0,0};
        BufferInfo* info = (BufferInfo*)archive->allocate(sizeof(BufferInfo), &ctx); // allocate via archive? Actually uses a function: (*(code **) *this->archive) (0xc, &ctx); but that's a vtable call with size 0xc (12) and a context. This is unusual. Possibly archive->allocate(12, &ctx)
        if (info == nullptr) {
            this->bufferPtr = nullptr;
        } else {
            info->buffer = (uint8_t*)FUN_009c8e80(arg3 << 4); // allocate arg3*16 bytes
            info->size = 0;
            info->count = arg3;
            this->bufferPtr = info;
        }
    }

    // Register message handlers
    uint32_t msgLoadId = FUN_004dafd0("iMsgGraphLoadCompleted");
    FUN_00408260(0x01222228, msgLoadId); // DAT_01222228 is a message handler slot
    uint32_t msgUnloadId = FUN_004dafd0("iMsgGraphUnloading");
    FUN_00408260(0x01222220, msgUnloadId);

    return this;
}