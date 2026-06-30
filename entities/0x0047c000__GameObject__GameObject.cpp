// FUNC_NAME: GameObject::GameObject
// Constructor for a base game object in EA EARS engine. Sets up primary and secondary vtable pointers and initializes fields.
// Address: 0x0047c000

extern void *PTR_FUN_00e3314c;    // Primary vtable
extern void *PTR_LAB_00e33168;    // Secondary vtable 1 (offset +0x3C)
extern void *PTR_LAB_00e33178;    // Secondary vtable 2 (offset +0x48)

class GameObject {
public:
    // Vtable pointers (multiple inheritance)
    void **m_pVTable;              // +0x00
    // Alignment/padding?
    void *m_pSecondaryVTable1;     // +0x3C (param_1[0x0F])
    void *m_pSecondaryVTable2;     // +0x48 (param_1[0x12])
    int32_t m_field0x50;           // +0x50 (param_1[0x14])
    int16_t m_field0x54;           // +0x54 (*(undefined2*)(param_1+0x15))
    int16_t m_field0x56;           // +0x56 (*(undefined2*)((int)param_1+0x56))
    int32_t m_field0x58;           // +0x58 (param_1[0x16])

    __thiscall GameObject(uint32_t param2);
};

// Forward declaration of base initialization function
extern void FUN_0046c590(uint32_t param2); // Likely base class constructor or init

__thiscall GameObject::GameObject(uint32_t param2) {
    // Call base initializer with the argument (e.g., a type ID or creation flags)
    FUN_0046c590(param2);

    // Set up vtable pointers
    m_pVTable = &PTR_FUN_00e3314c;        // Primary vtable
    m_pSecondaryVTable1 = &PTR_LAB_00e33168; // Secondary vtable for interface 1
    m_pSecondaryVTable2 = &PTR_LAB_00e33178; // Secondary vtable for interface 2

    // Zero-initialize remaining fields
    m_field0x50 = 0;
    m_field0x54 = 0;
    m_field0x56 = 0;
    m_field0x58 = 0;

    // Return this pointer (implicit in __thiscall)
}