// FUNC_NAME: EARSObject::constructor

#include <cstdint>

// Forward declarations of external functions (assumed engine calls)
void __thiscall baseConstructor(void); // FUN_00533cc0
void __thiscall finalizeSetup(void);   // FUN_004ebb40
uint32_t __cdecl computeHash(const int* position); // FUN_004e9270
void __thiscall finalInit(EARSObject* obj, int param1, uint64_t param2, uint64_t param3, uint32_t hashId, int param5, int param6); // FUN_00504d40

// Constants
constexpr uint32_t DEFAULT_TIME_SCALE = 0x00e2b1a4; // DAT_00e2b1a4
constexpr uint32_t HASH_TABLE_SIZE = 0x1000;        // up to 4096 entries
constexpr uint32_t HASH_ENTRY_STRIDE = 0x38;
constexpr uint32_t FRAME_BUFFER_SIZE = 20;          // 0x13 + 1
constexpr uint32_t INVALID_HASH_OFFSET = 0xfee0f0d8; // -0x11a0f28 as unsigned

// Global variables (engine state)
extern uint32_t* g_hashTableBase;          // DAT_011a0f38 - base of hash entry table
extern int32_t   g_frameTimeIndex;         // DAT_0119478c - current index in frame time ring buffer
extern float     g_frameTimeBuffer[FRAME_BUFFER_SIZE]; // DAT_01194790 - ring buffer for frame delta averaging

// Vtable pointer symbol (actual vtable at 0x00e37f58)
extern void* PTR_FUN_00e37f58;

class EARSObject {
public:
    uint32_t vtablePtr;        // +0x00
    uint32_t parentPtr;        // +0x04 (offset 1)
    uint32_t someFlag;         // +0x08 (offset 2)
    uint32_t unknown;          // +0x0C (offset 3)
    uint32_t internalData[2];  // +0x10 (offset 4-5) - points to transform data
    uint32_t spawnParams;      // +0x24 (offset 9)
    uint32_t field_0x28;       // +0x28 (offset 10)
    uint32_t field_0x2c;       // +0x2C (offset 11)
    uint32_t field_0x30;       // +0x30 (offset 12)
    uint8_t  flag_0x0d;        // +0x0D - non-zero if already constructed
};

// Represents the spawn parameter data structure passed by pointer
struct SpawnParams {
    int32_t pos[4];            // +0x00..0x0C (position/rotation/quat)
    int32_t flags;             // +0x14 (index 5)
    int32_t vel[3];            // +0x30 (index 0xC..0xE) - interpreted as int or float
};

// Windows TLS helper: FS:[0x2C] -> pointer to thread-local storage array
inline int* getTlsArray() {
    int* tlsPtr;
    __asm mov eax, fs:[0x2C];
    return eax;
}

void __thiscall EARSObject::constructor(int* spawnParams_raw) {
    SpawnParams* spawn = reinterpret_cast<SpawnParams*>(spawnParams_raw);

    // Base class initialization
    baseConstructor();

    // Set vtable for this class
    vtablePtr = reinterpret_cast<uint32_t>(&PTR_FUN_00e37f58);

    // Check if already initialized (flag at +0x0D)
    if (flag_0x0d != 0)
        return;

    // Initialize some fields
    field_0x28 = 0;
    field_0x2c = DEFAULT_TIME_SCALE;
    field_0x30 = DEFAULT_TIME_SCALE;
    spawnParams = reinterpret_cast<uint32_t>(spawn);

    // Set a flag on the parent/container object
    uint32_t* parentObj = reinterpret_cast<uint32_t*>(parentPtr);
    *parentObj |= 0x100000;

    // Access thread-local storage
    int* tls = getTlsArray();
    int someOffset = tls[2]; // *(int*)((uint)tls + 8)

    // Set up a child structure: offset 0x10 of this points to data, then +0x10 + someOffset
    uint32_t* childBase = reinterpret_cast<uint32_t*>(
        reinterpret_cast<uint32_t>(internalData[0]) + 0x10 + someOffset);

    // Initialize 12 dwords (48 bytes) with default values
    childBase[0] = DEFAULT_TIME_SCALE;    // +0x00
    childBase[1] = 0;                    // +0x04
    childBase[2] = 0;                    // +0x08
    childBase[3] = 0;                    // +0x0C
    childBase[4] = 0;                    // +0x10
    childBase[5] = DEFAULT_TIME_SCALE;   // +0x14
    childBase[6] = 0;                    // +0x18
    childBase[7] = 0;                    // +0x1C
    childBase[8] = 0;                    // +0x20
    childBase[9] = 0;                    // +0x24
    childBase[10] = DEFAULT_TIME_SCALE;  // +0x28
    childBase[11] = 0;                   // +0x2C

    // Process velocity from spawn parameters
    float* velocity = reinterpret_cast<float*>(
        reinterpret_cast<uint32_t>(internalData[0]) + 0x40 + someOffset);
    if ((spawn->flags & 2) == 0) {
        // Absolute set (if bit 4 set)
        if ((spawn->flags & 4) != 0) {
            reinterpret_cast<int32_t*>(velocity)[0] = spawn->vel[0];
            reinterpret_cast<int32_t*>(velocity)[1] = spawn->vel[1];
            reinterpret_cast<int32_t*>(velocity)[2] = spawn->vel[2];
        }
    } else {
        // Additive (float addition)
        velocity[0] = static_cast<float>(spawn->vel[0]) + velocity[0];
        velocity[1] = static_cast<float>(spawn->vel[1]) + velocity[1];
        velocity[2] = static_cast<float>(spawn->vel[2]) + velocity[2];
    }

    // Finalize some setup
    finalizeSetup();

    // Compute hash from spawn position (used as reference count ID)
    uint32_t hashId = 0;
    if (spawn->pos[0] != 0 || spawn->pos[1] != 0 || spawn->pos[2] != 0 || spawn->pos[3] != 0) {
        hashId = computeHash(spawn->pos);
        if ((hashId != 0) && (hashId != 0xFFFFFFFF) && (hashId < HASH_TABLE_SIZE) &&
            (hashId * HASH_ENTRY_STRIDE != INVALID_HASH_OFFSET)) {
            int* entry = reinterpret_cast<int*>(
                reinterpret_cast<uint32_t>(g_hashTableBase) + hashId * HASH_ENTRY_STRIDE);
            if (entry != nullptr) {
                *entry += 1; // increment reference
            }
        }
    }

    // Update frame time ring buffer (circular accumulation)
    int32_t prevIndex = g_frameTimeIndex - 1;
    int32_t nextIndex = g_frameTimeIndex + 2;
    if (prevIndex < 0)         prevIndex = FRAME_BUFFER_SIZE - 1; // 19
    if (nextIndex > FRAME_BUFFER_SIZE - 1) nextIndex = g_frameTimeIndex - (FRAME_BUFFER_SIZE - 2); // -18 -> +2 mod?
    g_frameTimeBuffer[prevIndex] = g_frameTimeBuffer[prevIndex] + g_frameTimeBuffer[nextIndex];
    g_frameTimeIndex = prevIndex;

    // Final initialization call with packed parameters
    finalInit(this,
              *reinterpret_cast<int*>(parentPtr + 0x10),
              (static_cast<uint64_t>(reinterpret_cast<uint32_t>(&spawn)) << 32) | reinterpret_cast<uint32_t>(spawn),
              (static_cast<uint64_t>(g_frameTimeBuffer[prevIndex]) << 32) | someFlag, // someFlag from +0x08
              hashId,
              internalData[0],
              internalData[1]);
}