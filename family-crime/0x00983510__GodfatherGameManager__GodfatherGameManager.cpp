// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x00983510
// EARS engine constructor with optional placement flag

extern void* PTR_FUN_00d90890;   // VFT for base class (e.g., Framework::Singleton)
extern void* PTR_LAB_00d90868;   // VFT for second base (e.g., IUpdateable)
extern void* PTR_LAB_00d90864;   // Temporary VFT for derived subobject initialization
extern void* PTR_LAB_00d90860;   // Final VFT for GodfatherGameManager

extern int g_gameManagerReady;   // _DAT_01130904 – global singleton flag

// Sub-object constructors (likely for member components)
extern void ConstructComponent(void* addr);          // FUN_009c8f10
extern void GlobalInit_Godfather();                   // FUN_005c16e0  (global subsystems)
extern void SelfDestructIfNeeded(GodfatherGameManager* obj); // FUN_005c4480 (delete/unregister)

class GodfatherGameManager {
public:
    /* +0x00 */ void* vftable;               // primary VFT
    /* +0x04 */ void* secondVFT;             // secondary interface VFT
    /* +0x08..0x12 */ // other members (unknown)
    /* +0x13 */ void* subVFT;                // VFT for derived part (swapped during init)
    /* +0x15 */ SubComponent m_componentA;   // e.g., InputManager?? (size? )
    /* +0x16 */ SubComponent m_componentB;   // e.g., CameraManager?? (size? )

    GodfatherGameManager(byte flags) {
        // Chain VFTs for base classes
        this->vftable     = &PTR_FUN_00d90890;   // base class
        this->secondVFT   = &PTR_LAB_00d90868;   // second base interface
        this->subVFT      = &PTR_LAB_00d90864;   // temporary VFT for derived subobject

        // Initialize embedded components by calling their constructors
        ConstructComponent(&this->m_componentB);  // offset +0x16
        ConstructComponent(&this->m_componentA);  // offset +0x15

        // Finalize the VFT for the most-derived class
        this->subVFT = &PTR_LAB_00d90860;

        // Mark singleton as ready (reset global flag)
        g_gameManagerReady = 0;

        // Perform global framework initialization (register managers, etc.)
        GlobalInit_Godfather();

        // If the allocation was not placement-new (flags & 1), 
        // the constructor may have been called from within operator new;
        // this call might clean up on failure or perform a self-deregistration.
        if (flags & 1) {
            SelfDestructIfNeeded(this);
        }
    }
};