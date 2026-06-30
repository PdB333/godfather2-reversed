// FUNC_NAME: NetObject::serialize
// Address: 0x00760e00
// Role: Serialize/deserialize NetObject state for network ghost replication

// Global pointer referenced: likely a singleton network manager
extern int* g_pNetManager; // DAT_012233a0

// External helper functions (identified via context)
extern uint GetCurrentTick();            // FUN_0072fa80
extern uint GetSimTime();                // FUN_007347e0
extern void* AllocateBuffer(void* stream, uint size); // FUN_007ffdf0
extern void WriteData(void* data, void* stream, bool flag); // FUN_00757c10
extern void FlushBuffer(void* unknown);                    // FUN_0075cd50
extern void EndMessage(uint unknown);                      // FUN_0075cd70
extern void RegisterGhost(void* obj);                     // FUN_007607b0
extern void ReadDeserializeChunk(void* member);            // FUN_007608a0
extern void ReadSomething(void* member);                   // FUN_00760900
extern void DeserializeObject(void* stream);               // FUN_00760070
extern void DefaultSerialize(void* stream);                // FUN_0073e4d0

// Stream context struct (simplified – actual layout unknown)
struct SerializationStream {
    // vtable at offset 0
    // uint64 values at various offsets (0x78, 0x80, etc.)
};

// Hash constants for read/write operations
const uint HASH_WRITE = 0x6862a74c;
const uint HASH_READ  = 0x6b4fe568;

// Thunk for first vtable entry: GetStreamType()
typedef uint (__thiscall* GetStreamTypeFunc)(SerializationStream*);

void __thiscall NetObject::serialize(SerializationStream* stream)
{
    uint streamType = (*(GetStreamTypeFunc)(*(void**)stream))(); // get stream type (e.g., "Write" or "Read")

    if (streamType == HASH_WRITE) {
        // ----- Write (pack) path -----
        uint* memberPtr = (uint*)(this + 0x70); // +0x70: pointer to some member, possibly NetStringTable
        if (*(int*)memberPtr != 0) {
            uint* otherPtr = (uint*)(this + 0x78); // +0x78: another member pointer
            // Check condition from game logic: member at +0x5c has flags
            uint flags = *(uint*)(*(int*)(this + 0x5c) + 0x5f0);
            ushort mask = *(ushort*)(*(int*)(this + 0x70) + 0x4e);
            if ((flags & mask) != 0) {
                // Allocate and write with size = 1
                void* buffer = AllocateBuffer((void*)(this + 0x70), 1);
                WriteData(buffer, (void*)(this + 0x70), true);
            }
            // Flush and end the network message
            FlushBuffer((void*)otherPtr);
            EndMessage(*(uint*)(otherPtr + 0xc)); // +0x0c: message ID

            // Register ghost on network manager if available
            int* netMgr = *(int**)(g_pNetManager + 4);
            if ((netMgr != 0) && (*(int*)(netMgr + (-0x1f30 / 4)) != 0)) {
                // -0x1f30 offset: possibly a ghost list offset
                int* ghostEntry = netMgr + (-0x7CC); // 0x1f30 / 4 = 0x7CC
                RegisterGhost((void*)(ghostEntry));
                // Store pointer to (this+0x8c) in stream for later use
                stream[0x41] = this + 0x8c; // +0x8c: another member offset
            }
        }

        // Prepare ghost data to send: store function pointers and constants into stream
        // stream[0x1e] = getSimTime() with this->+0x5c appended? (Concat44)
        *(ulonglong*)(stream + 0x1e) = CONCAT44(GetSimTime, *(int*)(this + 0x5c));
        // stream[0x20] = lower 32 bits of local variable (stack variable uStack_c) shifted to high
        *(ulonglong*)(stream + 0x20) = (ulonglong)uStack_c << 0x20;
        // stream[0x22] = address of global label &LAB_0073b090 with uStack_8 (another local)
        *(ulonglong*)(stream + 0x22) = CONCAT44(&LAB_0073b090, uStack_8);
        // stream[0x24] = address of ghost update function (LAB_00760010) with this pointer
        *(ulonglong*)(stream + 0x24) = CONCAT44(&LAB_00760010, this);
        // stream[0x26] = another shifted stack value
        *(ulonglong*)(stream + 0x26) = (ulonglong)uStack_c << 0x20;
        // stream[0x28] = another address with stack
        *(ulonglong*)(stream + 0x28) = CONCAT44(&LAB_007600b0, uStack_8);
        // Set version field
        stream[0x3c] = 3; // version = 3
        return;
    }
    else if (streamType == HASH_READ) {
        // ----- Read (unpack) path -----
        uint currentTick = GetCurrentTick();
        stream[0x39] = currentTick;
        uint simTime = GetSimTime();
        stream[0x38] = simTime;

        // Deserialize chunk at this+0x70
        ReadDeserializeChunk((void*)(this + 0x70));

        // Global variable: assumed tick offset for network compensation
        extern uint g_netTickOffset; // DAT_00e51b24
        stream[0x2a] = g_netTickOffset;

        // Set a flag (0x10) in stream flags
        stream[0x3a] |= 0x10;

        // Read additional data at this+0x7c
        ReadSomething((void*)(this + 0x7c));

        // Final deserialization of the object
        DeserializeObject(stream);
        return;
    }
    else
    {
        // Unknown stream type – fallback to default serialization
        DefaultSerialize(stream);
        return;
    }
}