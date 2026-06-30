// FUNC_NAME: EARSObject::EARSObject
// Address: 0x6b9410
// This function is the constructor for the base EARSObject class.
// It initializes the vtable pointer, two unknown function pointers,
// and debug sentinel markers typical of EA's EARS engine.

#include <cstdint>

// Extern declarations for vtable and other constant pointers
extern void* vtable_EARSObject;          // PTR_FUN_00d5e618
extern void* data_EARSObject_f_3C;       // PTR_LAB_00d5e608
extern void* data_EARSObject_f_48;       // PTR_LAB_00d5e604

// Forward declaration of the base constructor called at 0x0046c590
void ConstructEARSBase(uint32_t param2);

class EARSObject {
public:
    // +0x00 : vtable pointer
    void* m_vtable;

    // +0x3C : unknown pointer (maybe function table or string)
    void* m_pData3C;

    // +0x48 : unknown pointer (maybe function table or string)
    void* m_pData48;

    // +0x50 : some integer, zeroed
    uint32_t m_field50;

    // +0x54 : debug sentinel
    uint32_t m_magicBad;

    // +0x58 : debug sentinel
    uint32_t m_magicBeef;

    // +0x5C : debug sentinel (0xEAC15A55)
    uint32_t m_magicEac1;

    // +0x60 : debug sentinel (0x91100911)
    uint32_t m_magic9110;

    // +0x64 : some integer, zeroed
    uint32_t m_field64;

    // +0x68 : two‑byte field
    uint16_t m_field68;

    // +0x6A : two‑byte field
    uint16_t m_field6A;

    // +0x6C : some integer, zeroed
    uint32_t m_field6C;

    // +0x70 : some integer, zeroed
    uint32_t m_field70;

    EARSObject(uint32_t param2) {
        // Call base object constructor (likely sets up a different vtable)
        ConstructEARSBase(param2);

        // Clear field at +0x50
        m_field50 = 0;

        // Set vtable for this class
        m_vtable = &vtable_EARSObject;

        // Set two pointers to global data/tables
        m_pData3C = &data_EARSObject_f_3C;
        m_pData48 = &data_EARSObject_f_48;

        // Place debug sentinel values to detect memory corruption/use‑after‑free
        m_magicBad   = 0xBADBADBA;
        m_magicBeef  = 0xBEEFBEEF;
        m_magicEac1  = 0xEAC15A55;
        m_magic9110  = 0x91100911;

        // Zero remaining fields
        m_field64 = 0;
        m_field68 = 0;
        m_field6A = 0;
        m_field6C = 0;
        m_field70 = 0;
    }
};