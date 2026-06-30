// FUN_00444240: InputManager::InputManager

#include <cstdint>

// Forward declarations for external functions
extern "C" void* __fastcall allocateMemory(size_t size); // FUN_009c8e50
extern "C" void* __fastcall allocateBuffer(uint32_t size); // FUN_009c8e80
extern "C" int __fastcall acquireLock(); // FUN_00407da0
extern "C" void __fastcall releaseLock(void* lock, uint32_t flags); // FUN_004084d0
extern "C" void __fastcall setInputActive(int active); // FUN_00444930

// Global variables (addresses from decompiled)
extern uint32_t g_inputManager; // DAT_012233b4 (base pointer to controller array)
extern int g_someFlag;          // DAT_01205254
extern void* g_refCounter1;     // DAT_012069d4
extern void* g_refCounter2;     // DAT_012069ec
extern void* g_refCounter3;     // DAT_012069e4
extern void* g_refCounter4;     // DAT_012069dc
extern int g_refCount1;         // _DAT_012069d8
extern int g_refCount2;         // _DAT_012069f0
extern int g_refCount3;         // _DAT_012069e8
extern int g_refCount4;         // _DAT_012069e0

// Controller structure (size 0x44 per slot)
struct ControllerSlot {
    char pad0[0x6A];            // +0x00 to +0x69
    char connected;              // +0x6A (0 = disconnected, 1 = connected)
    char pad1[0x6C - 0x6B];     // +0x6B to +0x6C (two bytes set later)
    char flags;                 // +0x6D? Not used here
    // ... more fields
};

// InputManager class layout (inferred from offsets)
class InputManager {
public:
    // Vtable pointer at offset 0
    void* vtable;                // +0x00

    // Fields
    int field_04;                // +0x04 (set to 1)
    int field_08;                // +0x08 (set to 0)
    void* vtable2;               // +0x0C (set to &PTR_LAB_00e31198, then later changed to &PTR_LAB_00e31194)

    // Buffer allocation (size 0x200)
    struct BufferNode {
        void* buffer;            // +0x00 (allocated with FUN_009c8e80)
        int freeIndex;           // +0x04 (set to 0)
        int capacity;            // +0x08 (set to 0x80)
    }* bufferNode;               // +0x10 (allocated with allocateMemory(0xC))

    // Free list for controller objects (16 entries, each 5 ints apart)
    int freeListHead;            // +0x14 (offset 0xB6*4 = 0x2D8? Wait, calculate)
    // Actually: param_1[0xB6] = param_1+0x66; so field at +0x2D8 = pointer to field at +0x198? 
    // Let's treat as array of 16 pointers at +0x198 (0x66*4 = 0x198)
    int* freeList[16];           // +0x198 (each element points to next free, -1 marks end)

    // Controller slot data (16 slots)
    struct SlotData {
        char unk1;               // +0x00 (set to 0)
        int unk2;                // +0x04 (set to 0)
        int unk3;                // +0x08 (set to 0)
        int unk4;                // +0x0C (set to 0)
        char unk5;               // +0x10 (set to 0)
        int unk6;                // +0x14 (set to 0)
        // total size 0x18? Actually loop iterates 6 ints = 24 bytes per slot
    } slotData[16];              // +0x1C (param_1+7 = +0x1C) each slot 6*4=24 bytes

    char byte_0x195;             // +0x195 (some setting)
    char byte_0x196;             // +0x196 (used in loop)
    char byte_0x2D7;             // +0x2D7 (bitfield, set at end)
    // Possibly more fields after

    // Constructor
    InputManager() {
        // Vtable and initial values
        vtable = &g_vtable1;     // PTR_FUN_00e31184
        field_04 = 1;
        field_08 = 0;
        vtable2 = &g_vtable2;    // PTR_LAB_00e31198 (later changed to PTR_LAB_00e31194)
        byte_0x2D7 = 0;

        // Handle reference counted objects (lock acquire/release pattern)
        if (g_refCounter1) {
            g_refCount1++;
            int lock = acquireLock();
            if (lock == 0) {
                releaseLock(&g_refCounter1, 0x3FF0);
            } else {
                // Some atomic increment on lock's field at +0x14
                uint16_t val = *(uint16_t*)(lock + 0x14);
                *(uint16_t*)(lock + 0x14) = ((short)((val * 2) >> 1) + 1 ^ val) & 0x7FFF ^ val;
            }
        }
        if (g_refCounter2) {
            g_refCount2++;
            int lock = acquireLock();
            if (lock == 0) {
                releaseLock(&g_refCounter2, 0x3FF0);
            } else {
                uint16_t val = *(uint16_t*)(lock + 0x14);
                *(uint16_t*)(lock + 0x14) = ((short)((val * 2) >> 1) + 1 ^ val) & 0x7FFF ^ val;
            }
        }

        // Allocate buffer node (0xC bytes) and its buffer (0x200 bytes)
        BufferNode* node = (BufferNode*)allocateMemory(0xC);
        if (node) {
            node->buffer = allocateBuffer(0x200);
            node->freeIndex = 0;
            node->capacity = 0x80;
        }
        bufferNode = node;

        // Initialize free list linked chain (16 entries, spaced 5 ints apart)
        // param_1[0xB6] = param_1 + 0x66; -> point to start of free list array
        int* freeListBase = &field_0x198; // +0x198
        for (int i = 0; i < 16; i++) {
            freeListBase[i*5] = (int)(&freeListBase[(i+1)*5]); // pointer arithmetic
        }
        freeListBase[15*5] = 0; // last element null

        // Initialize slot data (16 slots, each 6 ints)
        for (int slot = 0; slot < 16; slot++) {
            SlotData* sd = &slotData[slot];
            sd->unk1 = 0;
            sd->unk2 = 0;
            sd->unk3 = 0;
            sd->unk4 = 0;
            sd->unk5 = 0;
            sd->unk6 = 0;
        }

        // Controller detection and assignment loop
        byte_0x196 = 0;
        int slot = 0;
        while (true) {
            if (slot < 0x10) {
                // Check if controller is connected at g_inputManager + 0x6A + slot*0x44
                if (*(char*)(g_inputManager + 0x6A + slot * 0x44) != 0) {
                    uint32_t controllerIndex = slot;
                    // Special case: if this slot equals the current controller type byte and flag is not 0x12
                    if (slot == *(uint8_t*)(g_inputManager + 0x53D) && *(uint8_t*)(g_inputManager + 0x568) != 0x12) {
                        controllerIndex = *(uint8_t*)(g_inputManager + 0x568);
                    }
                    int slotBase = g_inputManager + controllerIndex * 0x44;
                    if (*(char*)(slotBase + 0x6A) != 0) {
                        *(char*)(slotBase + 0x6B) = byte_0x195; // set some ID
                        *(char*)(slotBase + 0x6C) = byte_0x196;
                    }
                }
            } else if (slot == 0x11) {
                // Slot 0x11: find first disconnected controller
                int i = 0;
                char* base = (char*)(g_inputManager + 0x6A);
                while (i < 0x10) {
                    if (base[0] == 0) goto foundDisconnected;
                    i++;
                    base += 0x44;
                }
                // All connected, fall through to special assignment
                // (repeats same as above)
                uint32_t controllerIndex = slot; // but slot 0x11 is used as index?
                // This part replicates the above logic
                if (slot == *(uint8_t*)(g_inputManager + 0x53D) && *(uint8_t*)(g_inputManager + 0x568) != 0x12) {
                    controllerIndex = *(uint8_t*)(g_inputManager + 0x568);
                }
                int slotBase = g_inputManager + controllerIndex * 0x44;
                if (*(char*)(slotBase + 0x6A) != 0) {
                    *(char*)(slotBase + 0x6B) = byte_0x195;
                    *(char*)(slotBase + 0x6C) = byte_0x196;
                }
            }
        foundDisconnected:
            ; // empty
            slot++;
            if (slot > 0x10) break;
        }

        // Post-initialization
        g_someFlag = 0; // set to 0? Actually param_1[0xB8..0xBB]=0, but those are later offsets?
        // Let's treat fields at +0x2E0, +0x2E4, +0x2E8, +0x2EC as zero
        *(int*)(this + 0x2E0) = 0;
        *(int*)(this + 0x2E4) = 0;
        *(int*)(this + 0x2E8) = 0;
        *(int*)(this + 0x2EC) = 0;

        bool flag = (g_someFlag != 0);
        if (flag) {
            byte_0x2D7 |= 1;
            if (g_someFlag == 1) {
                setInputActive(1);
            }
        }
        byte_0x2D7 |= 2;

        // Handle another set of reference counters
        if (g_refCounter3) {
            g_refCount3++;
            int lock = acquireLock();
            if (lock == 0) {
                releaseLock(&g_refCounter3, 0x8000);
            } else {
                uint16_t val = *(uint16_t*)(lock + 0x14);
                *(uint16_t*)(lock + 0x14) = ((short)((val * 2) >> 1) + 1 ^ val) & 0x7FFF ^ val;
            }
        }
        if (g_refCounter4) {
            g_refCount4++;
            int lock = acquireLock();
            if (lock != 0) {
                uint16_t val = *(uint16_t*)(lock + 0x14);
                *(uint16_t*)(lock + 0x14) = ((short)((val * 2) >> 1) + 1 ^ val) & 0x7FFF ^ val;
                return; // early return?
            }
            releaseLock(&g_refCounter4, 0x8000);
        }
    }
};

// Vtable symbols (not defined here)
extern void* g_vtable1;   // 0x00e31184
extern void* g_vtable2;   // 0x00e31198 (later changed to 0x00e31194)