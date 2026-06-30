// FUNC_NAME: AptSystem::shutdown
#include <cassert>

// Forward declarations
void aptLockAcquire();
void aptLockRelease();
void aptDeleteMemory(void* ptr, size_t size); // Function pointer stored at DAT_0119caf8

// Global data (from static analysis)
extern void* gAptGlobal1; // DAT_0119cc14
extern void* gAptGlobal2; // DAT_0119cbb0
extern void* gAptGlobal3; // DAT_0119cbb8
extern void* gAptGlobal4; // DAT_0119cbbc
extern void* gAptGlobal5; // DAT_0119cc0c
extern void* gAptGlobal6; // DAT_0119cbf0
extern void* gAptGlobal7; // DAT_0119cbc8
extern void* gAptGlobal8; // DAT_0119cbc0
extern void* gAptGlobal9; // DAT_0119cbc4
extern void* gAptGlobal10; // DAT_0119cbcc
extern void* gAptGlobal11; // DAT_0119cbb4
extern void* gAptGlobal12; // DAT_0119cbac

extern AptString* gGlobalAptStrings[16]; // DAT_0119cb9c array of pointers, each 4 bytes
extern void (*gAptStringDestructorTable[])(AptString*); // DAT_0103aee0, indexed by (ptr & 0x7fff)

extern bool gAssertionMode; // DAT_01128fc4
extern void* assertionRaise(...); // callback

void AptSystem::shutdown()
{
    aptLockAcquire();

    if (gAptGlobal1 != 0) {
        aptLockRelease();
        aptDeleteMemory(gAptGlobal1, 0x48);
        gAptGlobal1 = 0;
    }

    if (gAptGlobal2 != 0) {
        aptLockRelease();
        aptDeleteMemory(gAptGlobal2, 0x4c);
        gAptGlobal2 = 0;
    }

    if (gAptGlobal3 != 0) {
        aptLockRelease();
        aptDeleteMemory(gAptGlobal3, 0x4c);
        gAptGlobal3 = 0;
    }

    aptDeleteMemory(gAptGlobal4, 4);
    gAptGlobal4 = 0;
    aptDeleteMemory(gAptGlobal5, 4);
    gAptGlobal5 = 0;
    aptDeleteMemory(gAptGlobal6, 0x3c0);
    gAptGlobal6 = 0;

    // Free series of 0x50-sized allocations
    if (gAptGlobal7 != 0) {
        aptLockRelease();
        aptDeleteMemory(gAptGlobal7, 0x50);
        gAptGlobal7 = 0;
    }
    if (gAptGlobal8 != 0) {
        aptLockRelease();
        aptDeleteMemory(gAptGlobal8, 0x50);
        gAptGlobal8 = 0;
    }
    if (gAptGlobal9 != 0) {
        aptLockRelease();
        aptDeleteMemory(gAptGlobal9, 0x50);
        gAptGlobal9 = 0;
    }
    if (gAptGlobal10 != 0) {
        aptLockRelease();
        aptDeleteMemory(gAptGlobal10, 0x50);
        gAptGlobal10 = 0;
    }
    if (gAptGlobal11 != 0) {
        aptLockRelease();
        aptDeleteMemory(gAptGlobal11, 0x50);
        gAptGlobal11 = 0;
    }
    if (gAptGlobal12 != 0) {
        aptLockRelease();
        aptDeleteMemory(gAptGlobal12, 0x50);
        gAptGlobal12 = 0;
    }

    // Release global APT strings
    for (int i = 0; i < 16; ++i) {
        AptString* str = gGlobalAptStrings[i];
        assert(str->getRefCount() == 1); // ensure no other references

        // Call destructor via vtable-like dispatch
        gAptStringDestructorTable[str->someOffset & 0x7fff](str);
        gGlobalAptStrings[i] = 0;
    }
}