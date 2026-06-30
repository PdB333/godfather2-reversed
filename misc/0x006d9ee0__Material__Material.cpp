// FUNC_NAME: Material::Material
// Address: 0x006d9ee0
// Software render state material constructor. Initializes default diffuse/ambient colors, alpha, and other render parameters.

#include <cstdint>

class Material {
public:
    // Vtable pointer (offset 0x00)
    void* m_vtable;

    // Offset 0x04: flags or zero
    uint32_t m_flags;

    // Offset 0x08: pad? byte zeroed
    uint8_t m_pad[4];  // // exact size? but actually 4 bytes, first byte set to 0

    // Offset 0x0C: alpha (0xFF = fully opaque)
    uint32_t m_alpha;

    // Offset 0x10: zero
    uint32_t m_field10;

    // Offset 0x14: zero
    uint32_t m_field14;

    // Offset 0x18-0x1C: padding? Not set.

    // Offset 0x20: diffuse color (loaded from global)
    uint32_t m_diffuseColor;

    // Offset 0x24: ambient color (loaded from global)
    uint32_t m_ambientColor;

    // Offset 0x28: specular color (loaded from global)
    uint32_t m_specularColor;

    // Offset 0x2C: same as specular?
    uint32_t m_specularColor2;

    // Offset 0x30: zero
    uint32_t m_field30;

    // Offset 0x34: zero
    uint32_t m_field34;

    // Offset 0x38: zero
    uint32_t m_field38;

    // Offset 0x3C: zero
    uint32_t m_field3C;

    // Offset 0x40: zero
    uint32_t m_field40;

    // Offset 0x44-0x48: not set.

    // Offset 0x50: copy of ambient color (from 0x24)
    uint32_t m_field50;

    // Offset 0x54: another copy of ambient color
    uint32_t m_field54;

    // Offset 0x58: zero
    uint32_t m_field58;

    // Constructor
    __fastcall Material(void* self) : m_vtable((void*)&PTR_FUN_00d5f5b0) {
        // This function is called as __fastcall with ECX = this.
        uint32_t uVar1 = *(uint32_t*)0x00d5780c;   // Default ambient color?
        uint32_t uVar2 = *(uint32_t*)0x00d5e288;   // Default diffuse color?
        uint32_t uVar3 = *(uint32_t*)0x00d5cf70;   // Default specular color?

        m_alpha = 0xFF;
        m_flags = 0;
        m_field10 = 0;
        m_field14 = 0;
        m_diffuseColor = uVar2;
        m_specularColor = uVar3;
        m_specularColor2 = uVar3;
        m_ambientColor = uVar1;
        // Zero fields at offset 0x30-0x40
        m_field30 = 0;
        m_field34 = 0;
        m_field38 = 0;
        m_field3C = 0;
        m_field40 = 0;
        // Set field50 and field54 to ambient color
        m_field50 = uVar1;
        m_field54 = uVar1;
        m_field58 = 0;
        // Zero the first byte of field at offset 0x08 (m_pad[0])
        *((uint8_t*)(this + 0x08)) = 0;
    }
};
// Note: PTR_FUN_00d5f5b0 and global constants should be defined elsewhere in the translation unit.