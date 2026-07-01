// FUNC_NAME: PlayerSM::~PlayerSM
// Address: 0x008494c0
// Role: Destructor for PlayerSM class (likely Player State Machine).
// Releases owned sub-components and calls base destructor.

#include <cstdint>

// Known class from EARS engine (The Godfather 2)
class PlayerSM {
public:
    // Vtable pointer at +0x00 (set to destructor safe table)
    void* vtable; // PTR_FUN_00d74cb4

    // Additional vtable/interface pointers (multiple inheritance)
    // Offset 0x3C (param_1[0xf]) - pointer to a base/interface vtable
    void* m_pInterface1; // PTR_LAB_00d74ca4
    // Offset 0x48 (param_1[0x12]) - another interface vtable
    void* m_pInterface2; // PTR_LAB_00d74ca0

    // Embedded base class object (size unknown) at offset 0x7C
    // This is initialized by FUN_00408310
    uint8_t m_baseObject[/* size? */]; // +0x7C

    // Owned sub-components with custom destructors:
    // Pair: (object pointer at +0x5C, destructor function pointer at +0x68)
    void* m_pComponentA; // +0x5C (param_1[0x17])
    void (*m_pComponentADtor)(void*); // +0x68 (param_1[0x1a])

    // Another pair: (object pointer at +0x6C, destructor at +0x78)
    void* m_pComponentB; // +0x6C (param_1[0x1b])
    void (*m_pComponentBDtor)(void*); // +0x78 (param_1[0x1e])

    // Component freed by a known function (FUN_009c8f10)
    void* m_pComponentC; // +0x94 (param_1[0x25])
};

// Forward declarations of external functions (from the game binary)
void FUN_00408310(void* baseObj);   // Base class destructor (subobject at +0x7C)
void FUN_008499e0(PlayerSM* this_); // Main destructor body
void FUN_009c8f10(void* comp);      // Specific component destructor
void FUN_0046c640(void);            // Global cleanup (e.g., manager deregistration)

// Destructor implementation
PlayerSM::~PlayerSM() {
    // Step 1: Set vtable to destructor-safe version
    vtable = reinterpret_cast<void*>(0x00d74cb4);

    // Step 2: Set extra interface pointers to destructor-safe tables
    m_pInterface1 = reinterpret_cast<void*>(0x00d74ca4);
    m_pInterface2 = reinterpret_cast<void*>(0x00d74ca0);

    // Step 3: Destroy embedded base class (subobject at offset 0x7C)
    FUN_00408310(&m_baseObject);

    // Step 4: Call derived class destructor body (additional cleanup)
    FUN_008499e0(this);

    // Step 5: Release owned components (if non-null)
    if (m_pComponentC != nullptr) {
        FUN_009c8f10(m_pComponentC);
    }
    if (m_pComponentB != nullptr) {
        // Call destructor function pointer stored for this component
        m_pComponentBDtor(m_pComponentB);
    }
    if (m_pComponentA != nullptr) {
        m_pComponentADtor(m_pComponentA);
    }

    // Step 6: Global finalization (often dereferences singleton or manager)
    FUN_0046c640();
}