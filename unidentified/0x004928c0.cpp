// FUN_004928c0: GameEngine::createSingleton()
// Role: Initialize global singleton instance of the game engine (returns pointer to global object at 0x01210830).
// Calls base initializer FUN_00491c40 and sets up vtable pointer.

#include <cstdint>

// Forward declaration of base engine class
class EngineBase;

class GameEngine {
public:
    // Static singleton creation/retrieval
    static GameEngine* createSingleton() {
        // Call base engine initialization
        EngineBase::initialize(); // FUN_00491c40

        // Set global flags to zero
        s_globalFlag1 = 0; // _DAT_01210a50
        s_globalFlag2 = 0; // _DAT_01210a54

        // Set vtable pointer of global instance
        s_instance.vtable = &s_vtable; // PTR_LAB_00e34710

        // Return pointer to the global instance
        return &s_instance;
    }

private:
    // Vtable pointer (offset 0x00)
    const void* vtable;

    // Global singleton instance
    static GameEngine s_instance;

    // Global flags (not part of instance)
    static int s_globalFlag1; // +0x01210a50
    static int s_globalFlag2; // +0x01210a54

    // Vtable definition (from PTR_LAB_00e34710)
    static const void* s_vtable;
};