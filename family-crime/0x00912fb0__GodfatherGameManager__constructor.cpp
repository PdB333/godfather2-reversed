// FUNC_NAME: GodfatherGameManager::constructor
// Function at 0x00912fb0: Constructor for GodfatherGameManager singleton
// Calls base class constructor at 0x00957ed0, initializes vtable pointers and members.
// MEMBER: DAT_01130018 (global pointer to singleton instance)

// .text:00912fb0
class GodfatherGameManager : public SomeBaseClass // base class at FUN_00957ed0
{
public:
    // Vtable pointers (multiple inheritance)
    // +0x00: vtable for primary class (PTR_FUN_00d84558)
    // +0x10: vtable for secondary interface (PTR_LAB_00d84530)
    // +0x50: vtable for another interface (PTR_LAB_00d8452c, initially PTR_LAB_00d84528)
    // +0x54: some flag (0)
    // +0x7c: some byte flag (0)

    // Static singleton global pointer
    static GodfatherGameManager* s_pInstance; // DAT_01130018

    // Constructor
    // param_1: this pointer
    // Returns: this
    __fastcall GodfatherGameManager()
    {
        // Call base class constructor
        SomeBaseClass_constructor(); // FUN_00957ed0

        // Initialize vtable pointer at +0x50 (first assignment)
        this->m_vtableInterface1 = &PTR_LAB_00d84528; // +0x50

        // Store this as global singleton
        s_pInstance = this;

        // Clear member at +0x54
        this->m_flag1 = 0; // +0x54

        // Clear byte at +0x7c
        *(char*)((int)this + 0x7c) = 0;

        // Set primary vtable pointer at +0x00
        this->m_vtablePrimary = &PTR_FUN_00d84558; // +0x00

        // Set vtable pointer at +0x10
        this->m_vtableSecondary = &PTR_LAB_00d84530; // +0x10

        // Reassign vtable pointer at +0x50 (final value)
        this->m_vtableInterface1 = &PTR_LAB_00d8452c; // +0x50

        // Return this (implicit)
    }

    // Member variables (offsets relative to this)
    // +0x00: void* m_vtablePrimary;
    // +0x10: void* m_vtableSecondary;
    // +0x50: void* m_vtableInterface1;
    // +0x54: int m_flag1;
    // +0x7c: char m_byteFlag7c;
};

// Global singleton pointer
GodfatherGameManager* GodfatherGameManager::s_pInstance; // DAT_01130018