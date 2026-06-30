/*
 * Function at 0x007394c0 - Destructor for a class (likely derived)
 * Sets vtable, stops sound resources, cleans up member pointer and sub-object.
 */

#include <cstdint>

// Forward declarations (assumed)
void stopSoundResource(uint32_t id); // FUN_007f6420
void* getAudioDataManager();         // FUN_0043b870 (uses DAT_01131040)
void clearAudioPointer(void* ptr, uint32_t flag); // FUN_00939860
void destroySubObject(void* obj);    // FUN_004daf90
void finalCleanup();                 // FUN_0080ea60

// Vtable constants (from data section)
extern void* PTR_LAB_00d630cc; // Most derived vtable
extern void* PTR_LAB_00d63090; // Base class vtable

class SomeClass {
public:
    // Destructor (__fastcall with this in ECX)
    void __fastcall ~SomeClass() {
        int iVar1 = *(int*)((uint8_t*)this + 0x5C); // offset +0x17 * 4 = 0x5C

        // Set vtable to most derived class (to allow proper cleanup)
        *(void**)this = &PTR_LAB_00d630cc;

        // Stop two sound resources (IDs 0xB and 0xF)
        stopSoundResource(0xB);
        stopSoundResource(0xF);

        // If the pointer at +0x5C is non-null, check and possibly clear
        if (iVar1 != 0) {
            uint32_t* audioMgr = (uint32_t*)getAudioDataManager();
            if ((audioMgr != nullptr) && (*(uint32_t*)((uint8_t*)audioMgr + 0x1C) != 0) && 
                (*(uint32_t*)((uint8_t*)audioMgr + 0x1C) != 0x48)) {
                    clearAudioPointer((void*)iVar1, 0);
            }
        }

        // Switch to base class vtable before destructing base
        *(void**)this = &PTR_LAB_00d63090;

        // Destroy sub-object at offset +0x68 (0x1A * 4)
        if (*(uint32_t*)((uint8_t*)this + 0x68) != 0) {
            destroySubObject((uint8_t*)this + 0x68);
        }

        // Final cleanup (e.g., deallocation?)
        finalCleanup();
    }
};