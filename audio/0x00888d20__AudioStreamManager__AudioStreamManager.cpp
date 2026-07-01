// FUNC_NAME: AudioStreamManager::AudioStreamManager
// Address: 0x00888d20
// Role: Constructor for the audio stream manager (EARS engine). Initializes vtable pointers, voice slots (32), canary values, and child managers.

#include "ears/AudioStreamManager.h"
#include <cstdint>

// Forward declarations of called functions
extern void earsBaseInit(uint32_t param); // FUN_0046c590
extern void initInternal(); // FUN_0088ee30
extern void* allocateMemory(); // FUN_004dddd0
extern void* createChildManager(void* buffer, void* size); // FUN_004265d0
extern void lowLevelInit(void* globalData, uint16_t flags); // FUN_004086b0

// Vtable pointers (declared in assembly or other headers)
extern void* PTR_FUN_00d770d0; // main vtable
extern void* PTR_LAB_00d770c0; // sub-vtable at offset 0x3C (0xF * 4)
extern void* PTR_LAB_00d770bc; // sub-vtable at offset 0x48 (0x12 * 4)

class AudioStreamManager {
public:
    // Constructor
    AudioStreamManager(uint32_t baseParam) {
        // Call base initialization
        earsBaseInit(baseParam);

        // Set main vtable pointer
        *reinterpret_cast<void**>(this) = &PTR_FUN_00d770d0;

        // Set sub-vtable pointers at specific offsets
        m_subVtable1 = &PTR_LAB_00d770c0;    // +0x3C (0xF * 4)
        m_subVtable2 = &PTR_LAB_00d770bc;    // +0x48 (0x12 * 4)

        // Zero out various state fields
        m_field_0x1E = 0;   // +0x78 (0x1E * 4)
        m_field_0x1F = 0;   // +0x7C
        m_field_0x20 = 0;   // +0x80
        m_field_0x21 = 0;   // +0x84
        m_field_0x23 = 0;   // +0x8C
        m_field_0x24 = 0;   // +0x90
        m_field_0x25 = 0;   // +0x94
        m_field_0x27 = 0;   // +0x9C
        m_field_0x28 = 0;   // +0xA0
        m_field_0x29 = 0;   // +0xA4

        m_byteField_0x2B = 0;   // +0xAB? (offset from struct base? Actually param_1 + 0x2b as byte (0x2B*4 = 0xAC) but they use byte cast)
        // The following two bytes are set separately:
        m_byteField_0xAD = 1;   // +0xAD (explicit byte)
        m_byteField_0xAE = 0;   // +0xAE

        m_byteField_0x33 = 0;   // +0xCC (0x33 * 4 = 0xCC, byte)

        // Call internal initialization
        initInternal();

        // Allocate memory for child manager
        void* memory = allocateMemory();
        m_childManager = 0;          // +0x70 (0x70 * 4 = 0x1C0) - initially null
        void* childManagerBuffer = malloc(sizeof(int)); // local_c, local_8, local_4
        childManagerBuffer = nullptr; // local_c=0
        int* size = (int*)allocateMemory(); // piVar1
        m_childManager = createChildManager(childManagerBuffer, size); // uVar2 stored at +0x74 (0x74*4=0x1D0)
        m_childSize = size;               // +0x75 (0x75*4=0x1D4)

        // Call a method on the child manager via vtable (offset 8)
        void** vtable = (void**)*size;
        void (*initMethod)(void*) = (void (*)(void*))(vtable[2]); // *8
        initMethod(size); // Initialize child manager

        // Set remaining manager fields
        m_field_0x72 = 0;   // +0x1C8 (0x72*4)
        m_field_0x71 = 0;   // +0x1C4 (0x71*4)
        m_field_0x73 = 0;   // +0x1CC (0x73*4)
        m_field_0x76 = 0;   // +0x1D8 (0x76*4)

        // Initialize 32 voice slots with sentinel value 0xFE16702F
        const uint32_t kSentinel = 0xFE16702F;
        for (int i = 0; i < 32; i++) {
            m_voiceSlots[i] = kSentinel; // offsets +0x77 to +0x96 (0x77*4=0x1DC to 0x96*4=0x258)
        }

        // Set canary markers for debugging
        m_canary1 = 0;               // +0x97 (0x97*4=0x25C)
        m_canary2 = 0;               // +0x98 (0x260)
        m_canary3 = 0;               // +0x99 (0x264)
        m_magic_0x9A = 0xBADBADBA;   // +0x268
        m_magic_0x9B = 0xBEEFBEEF;   // +0x26C
        m_magic_0x9C = 0xEAC15A55;   // +0x270
        m_magic_0x9D = 0x91100911;   // +0x274

        m_field_0x9E = 0;   // +0x278 (0x9E*4)
        m_field_0x9F = 0;   // +0x27C

        m_byteField_0xA0 = 1;   // +0x280 (byte)
        m_field_0xA1 = 0;       // +0x284 (dword)
        m_field_0xA2 = 0;       // +0x288 (dword)

        // Zero three consecutive ints and three bytes (likely some state or array)
        // Offset mapping: int at 0x2C,0x2D,0x2E; byte at 0x2F,0x30,0x31
        for (int i = 0; i < 3; i++) {
            m_threeInts[i] = 0;        // +0x2C + i*4
            m_threeBytes[i] = 0;       // +0x2F + i (byte)
            m_threeIntsAlt[i] = 0;     // +0x30 + i*4 (overlaps? but following decompiler)
        }

        // Final low-level initialization with global data
        extern uint8_t DAT_01206a20; // some global
        lowLevelInit(&DAT_01206a20, 0xFFFF);
    }

private:
    // Vtable pointers
    void* m_vtable;                    // +0x00
    /* ... other members ... */
    void* m_subVtable1;                // +0x3C
    void* m_subVtable2;                // +0x48
    uint32_t m_field_0x1E;             // +0x78
    uint32_t m_field_0x1F;             // +0x7C
    uint32_t m_field_0x20;             // +0x80
    uint32_t m_field_0x21;             // +0x84
    uint32_t m_field_0x23;             // +0x8C
    uint32_t m_field_0x24;             // +0x90
    uint32_t m_field_0x25;             // +0x94
    uint32_t m_field_0x27;             // +0x9C
    uint32_t m_field_0x28;             // +0xA0
    uint32_t m_field_0x29;             // +0xA4
    uint8_t  m_byteField_0x2B;         // +0xAC? (actual offset 0xAC? but byte)
    uint8_t  m_byteField_0xAD;         // +0xAD
    uint8_t  m_byteField_0xAE;         // +0xAE
    uint8_t  m_byteField_0x33;         // +0xCC
    // Child manager
    void* m_childManager;              // +0x1C0 (0x70*4)
    void* m_childManager2;             // +0x1D0 (0x74*4)
    int*   m_childSize;                // +0x1D4 (0x75*4)
    uint32_t m_field_0x72;             // +0x1C8
    uint32_t m_field_0x71;             // +0x1C4
    uint32_t m_field_0x73;             // +0x1CC
    uint32_t m_field_0x76;             // +0x1D8
    uint32_t m_voiceSlots[32];         // +0x1DC to +0x258 (0x77 to 0x96 as dwords)
    uint32_t m_canary1;                // +0x25C
    uint32_t m_canary2;                // +0x260
    uint32_t m_canary3;                // +0x264
    uint32_t m_magic_0x9A;             // +0x268
    uint32_t m_magic_0x9B;             // +0x26C
    uint32_t m_magic_0x9C;             // +0x270
    uint32_t m_magic_0x9D;             // +0x274
    uint32_t m_field_0x9E;             // +0x278
    uint32_t m_field_0x9F;             // +0x27C
    uint8_t  m_byteField_0xA0;         // +0x280
    uint32_t m_field_0xA1;             // +0x284
    uint32_t m_field_0xA2;             // +0x288
    // Three ints and three bytes (from loop)
    uint32_t m_threeInts[3];           // +0x2C (first int at +0xB0? Actually 0x2C*4=0xB0)
    uint8_t  m_threeBytes[3];          // +0x2F (byte offsets: 0xBC,0xBD,0xBE)
    uint32_t m_threeIntsAlt[3];        // +0x30 (int at 0xC0,0xC4,0xC8)
    // Note: overlapping due to decompiler ambiguity; actual layout might differ.
};