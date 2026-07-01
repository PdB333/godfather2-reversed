// Xbox PDB: EARS_Modules_ChaseManager_ChaseManager
// FUNC_NAME: ChaseManager::ChaseManager
// Function address: 0x008fa7d0
// Constructor for ChaseManager class. Initializes chase system, registers messages, and subscribes to them.

#include <cstring> // for memset

// Forward declarations (assumed from game engine)
class ChaseManager;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char byte;

// External functions (from game engine)
extern void debugMarker(uint hash, int size); // FUN_0083f250
extern uint registerMessageString(const char* str); // FUN_00408240, returns message ID
extern void subscribeToMessage(void* subscriber, uint* msgId, uint flags); // FUN_00408900
extern void destructSubObject(void* ptr); // FUN_004daf90

// Global data (from decompilation)
extern ChaseManager* g_chaseManager; // DAT_0112af68
extern uint g_msgSetChaseEnable; // DAT_0112fe6c
extern uint g_msgSetChaseDisable; // DAT_0112fe90
extern uint g_msgChaseStarted; // DAT_0112fe64
extern uint g_msgChaseEnded; // DAT_0112fe88
extern uint g_msgLongChaseStarted; // DAT_0112fe80
extern uint g_msgChaseTimerExpiredWhilePlayerOnFoot; // DAT_0112fe74
extern uint g_msgSetChaseComplete; // DAT_0112fea8
extern uint g_msgChaseConfigTriggered; // DAT_0112fea0
extern uint g_msgChaseConfigApplied; // DAT_0112fe98
extern uint g_someGlobal; // DAT_0112b36c
extern uint g_anotherGlobal; // DAT_0112fc60
extern uint g_globalE448F0; // DAT_00e448f0
extern uint g_globalD61B40; // DAT_00d61b40
extern uint g_globalD812A8; // DAT_00d812a8

// Vtable pointers (from decompilation)
extern void* vtable_00d813f0; // PTR_FUN_00d813f0
extern void* vtable_00d813e0; // PTR_LAB_00d813e0
extern void* vtable_00d813dc; // PTR_LAB_00d813dc
extern void* vtable_00d813d8; // PTR_FUN_00d813d8
extern void* vtable_00d813d4; // PTR_LAB_00d813d4
extern void* vtable_00d813b0; // PTR_FUN_00d813b0
extern void* vtable_00d813cc; // PTR___purecall_00d813cc
extern void* vtable_00d813d0; // PTR_LAB_00d813d0

// ChaseManager class (partial layout based on offsets)
class ChaseManager {
public:
    // Vtable pointer at +0x00
    void* vtable;

    // ... many fields ...

    // Offsets (in words, each 4 bytes):
    // +0x0F (0x3C): vtable pointer
    // +0x12 (0x48): vtable pointer
    // +0x1C (0x70): some field
    // +0x56 (0x158): vtable pointer
    // +0x57 (0x15C): vtable pointer
    // +0x58 (0x160): some field
    // +0x59 (0x164): some field
    // +0x5A (0x168): some field
    // +0x5C (0x170): some field
    // +0x5D (0x174): some field
    // +0x5E (0x178): some field
    // +0x5F (0x17C): magic 0xbadbadba
    // +0x60 (0x180): magic 0xbeefbeef
    // +0x61 (0x184): magic 0xeac15a55
    // +0x62 (0x188): magic 0x91100911
    // +0x63 (0x18C): 0
    // +0x65 (0x194): 0
    // +0x66 (0x198): 0
    // +0x67 (0x19C): vtable pointer
    // +0x6E (0x1B8): 0
    // +0x6F (0x1BC): 0
    // +0x70 (0x1C0): 0
    // +0x71 (0x1C4): some value
    // +0x7B (0x1EC): byte = 1
    // +0x1ED: byte = 0
    // +0x6A (0x1A8): 0
    // +0x69 (0x1A4): 0
    // +0x68 (0x1A0): 0
    // +0x6D (0x1B4): 0
    // +0x6C (0x1B0): 0
    // +0x6B (0x1AC): 0
    // +0x74 (0x1D0): 0
    // +0x73 (0x1CC): 0
    // +0x72 (0x1C8): 0
    // +0x77 (0x1DC): 0
    // +0x76 (0x1D8): 0
    // +0x75 (0x1D4): 0
    // +0x7A (0x1E8): 0
    // +0x79 (0x1E4): 0
    // +0x78 (0x1E0): 0
    // +0x7C (0x1F0): 0
    // +0x7D (0x1F4): ushort = 0
    // +0x1F6: ushort = 0
    // +0x7E (0x1F8): 0
    // +0x7F (0x1FC): ushort = 0
    // +0x1FE: ushort = 0
    // +0x80 (0x200): 0
    // +0x81 (0x204): ushort = 0
    // +0x206: ushort = 0
    // +0xB6 (0x2D8): 0
    // +0xB9 (0x2E4): start of chase slot array (9 slots, each 4 words)
    // +0xDB (0x36C): some field
    // +0xDC (0x370): some field
    // +0xDD (0x374): some field
    // +0xDE (0x378): 0
    // +0xDF (0x37C): 0
    // +0xE0 (0x380): start of buffer (0xA8 bytes)
    // +0x10A (0x428): 0
    // +0x10B (0x42C): 0
    // +0x10C (0x430): 0
    // +0x10D (0x434): 0
    // +0x10E (0x438): 0
    // +0x10F (0x43C): 0
    // +0x110 (0x440): 0
    // +0x111 (0x444): start of another buffer (0xB0 bytes)

    // Constructor
    ChaseManager() {
        // Debug marker
        debugMarker(0xb703f7bf, 4);

        // Set vtable pointers
        this->vtable = &vtable_00d813f0;
        *(void**)((char*)this + 0x3C) = &vtable_00d813e0;   // +0x0F
        *(void**)((char*)this + 0x48) = &vtable_00d813dc;   // +0x12
        *(void**)((char*)this + 0x158) = &vtable_00d813d8;  // +0x56
        *(void**)((char*)this + 0x15C) = &vtable_00d813d4;  // +0x57

        // Store global instance
        g_chaseManager = this;

        // Initialize fields
        *(uint*)((char*)this + 0x160) = 0; // +0x58
        *(uint*)((char*)this + 0x164) = 0; // +0x59
        *(uint*)((char*)this + 0x168) = 0; // +0x5A
        *(uint*)((char*)this + 0x170) = 0; // +0x5C
        *(uint*)((char*)this + 0x174) = 0; // +0x5D
        *(uint*)((char*)this + 0x178) = 0; // +0x5E
        *(uint*)((char*)this + 0x17C) = 0xbadbadba; // +0x5F
        *(uint*)((char*)this + 0x180) = 0xbeefbeef; // +0x60
        *(uint*)((char*)this + 0x184) = 0xeac15a55; // +0x61
        *(uint*)((char*)this + 0x188) = 0x91100911; // +0x62
        *(uint*)((char*)this + 0x18C) = 0; // +0x63
        *(uint*)((char*)this + 0x194) = 0; // +0x65
        *(uint*)((char*)this + 0x198) = 0; // +0x66
        *(void**)((char*)this + 0x19C) = &vtable_00d813b0; // +0x67

        *(uint*)((char*)this + 0x1B8) = 0; // +0x6E
        *(uint*)((char*)this + 0x1BC) = 0; // +0x6F
        *(uint*)((char*)this + 0x1C0) = 0; // +0x70
        *(uint*)((char*)this + 0x1C4) = g_globalE448F0; // +0x71 (from DAT_00d813c8)

        *(byte*)((char*)this + 0x1EC) = 1; // +0x7B
        *(byte*)((char*)this + 0x1ED) = 0;

        *(uint*)((char*)this + 0x1A8) = 0; // +0x6A
        *(uint*)((char*)this + 0x1A4) = 0; // +0x69
        *(uint*)((char*)this + 0x1A0) = 0; // +0x68
        *(uint*)((char*)this + 0x1B4) = 0; // +0x6D
        *(uint*)((char*)this + 0x1B0) = 0; // +0x6C
        *(uint*)((char*)this + 0x1AC) = 0; // +0x6B

        *(uint*)((char*)this + 0x1D0) = 0; // +0x74
        *(uint*)((char*)this + 0x1CC) = 0; // +0x73
        *(uint*)((char*)this + 0x1C8) = 0; // +0x72

        *(uint*)((char*)this + 0x1DC) = 0; // +0x77
        *(uint*)((char*)this + 0x1D8) = 0; // +0x76
        *(uint*)((char*)this + 0x1D4) = 0; // +0x75

        *(uint*)((char*)this + 0x1E8) = 0; // +0x7A
        *(uint*)((char*)this + 0x1E4) = 0; // +0x79
        *(uint*)((char*)this + 0x1E0) = 0; // +0x78

        *(uint*)((char*)this + 0x1F0) = 0; // +0x7C
        *(ushort*)((char*)this + 0x1F4) = 0; // +0x7D
        *(ushort*)((char*)this + 0x1F6) = 0;

        *(uint*)((char*)this + 0x1F8) = 0; // +0x7E
        *(ushort*)((char*)this + 0x1FC) = 0; // +0x7F
        *(ushort*)((char*)this + 0x1FE) = 0;

        *(uint*)((char*)this + 0x200) = 0; // +0x80
        *(ushort*)((char*)this + 0x204) = 0; // +0x81
        *(ushort*)((char*)this + 0x206) = 0;

        *(uint*)((char*)this + 0x2D8) = 0; // +0xB6

        // Initialize chase slot array (9 slots, each 4 words)
        // Slots start at +0x2E4 (0xB9*4)
        uint* slotPtr = (uint*)((char*)this + 0x2E4); // points to first slot's first word
        for (int i = 0; i < 9; i++) {
            // Each slot structure: [ptr, field1, field2, padding?]
            // Set field1 and field2 to 0
            slotPtr[-2] = 0; // field1 (offset -8 bytes)
            slotPtr[-1] = 0; // field2 (offset -4 bytes)
            // If pointer is non-zero, destruct sub-object and clear
            if (slotPtr[0] != 0) {
                destructSubObject((void*)slotPtr[0]);
                slotPtr[0] = 0;
            }
            slotPtr += 4; // move to next slot (4 words)
        }

        // Set additional fields after slot array
        *(uint*)((char*)this + 0x36C) = g_globalE448F0; // +0xDB
        *(uint*)((char*)this + 0x370) = g_globalE448F0; // +0xDC (uVar2 from earlier)
        *(uint*)((char*)this + 0x374) = g_globalD61B40; // +0xDD
        *(uint*)((char*)this + 0x70) = g_globalD812A8;  // +0x1C

        *(uint*)((char*)this + 0x378) = 0; // +0xDE
        *(uint*)((char*)this + 0x37C) = 0; // +0xDF

        // Clear buffer at +0x380 (0xA8 bytes)
        memset((char*)this + 0x380, 0, 0xA8);

        *(uint*)((char*)this + 0x428) = 0; // +0x10A
        *(uint*)((char*)this + 0x42C) = 0; // +0x10B

        // Clear buffer at +0x444 (0xB0 bytes)
        memset((char*)this + 0x444, 0, 0xB0);

        // Reset magic values (set earlier, now cleared)
        *(uint*)((char*)this + 0x188) = 0; // +0x62
        *(uint*)((char*)this + 0x184) = 0; // +0x61
        *(uint*)((char*)this + 0x180) = 0; // +0x60
        *(uint*)((char*)this + 0x17C) = 0; // +0x5F

        // Register message strings
        g_msgSetChaseEnable = registerMessageString("iMsgSetChaseEnable");
        g_msgSetChaseDisable = registerMessageString("iMsgSetChaseDisable");
        g_msgChaseStarted = registerMessageString("iMsgChaseStarted");
        g_msgChaseEnded = registerMessageString("iMsgChaseEnded");
        g_msgLongChaseStarted = registerMessageString("iMsgLongChaseStarted");
        g_msgChaseTimerExpiredWhilePlayerOnFoot = registerMessageString("iMsgChaseTimerExpiredWhilePlayerOnFoot");
        g_msgSetChaseComplete = registerMessageString("iMsgSetChaseComplete");
        g_msgChaseConfigTriggered = registerMessageString("iMsgChaseConfigTriggered");
        g_msgChaseConfigApplied = registerMessageString("iMsgChaseConfigApplied");

        // Subscribe to messages (if registered)
        void* subscriber = (char*)this + 0x3C; // +0x0F (used as subscriber pointer)
        if (g_someGlobal != 0) {
            subscribeToMessage(subscriber, &g_someGlobal, 0x8000);
        }
        if (g_msgSetChaseEnable != 0) {
            subscribeToMessage(subscriber, &g_msgSetChaseEnable, 0x8000);
        }
        if (g_msgSetChaseDisable != 0) {
            subscribeToMessage(subscriber, &g_msgSetChaseDisable, 0x8000);
        }
        if (g_msgChaseConfigApplied != 0) {
            subscribeToMessage(subscriber, &g_msgChaseConfigApplied, 0x8000);
        }
        if (g_anotherGlobal != 0) {
            subscribeToMessage(subscriber, &g_anotherGlobal, 0x8000);
        }
    }
};