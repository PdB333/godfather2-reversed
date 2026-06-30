// FUNC_NAME: EAGameProperty::operator=
// Address: 0x004bc5b0
// This function is the assignment operator for an unspecified 52-byte structure.
// The structure contains:
//   - 3 dwords (bytes 0-11) – likely a Vector3 (x, y, z) or similar
//   - 3 sub-objects of 12 bytes each (bytes 12, 24, 36) – copied via FUN_00498500
//   - 1 dword at byte 48 (offset 0x30) – additional data

class EAGameProperty {
public:
    // +0x00: First three dwords (12 bytes)
    float field_0x00[3];  // e.g., position/scale

    // Sub-objects at +0x0C, +0x18, +0x24 (each 12 bytes)
    // In the original code these are likely strings or handles.
    // They are copied by the helper function FUN_00498500 (rename to copySubObject).

    // +0x30: Final dword (4 bytes)
    int field_0x30;       // e.g., flags or ID

    // Helper function for copying a 12-byte sub-object (defined elsewhere)
    static void copySubObject(void *dst, const void *src);

    // Assignment operator
    EAGameProperty& operator=(const EAGameProperty &other) {
        // Copy first three dwords (Vector3 equivalent)
        field_0x00[0] = other.field_0x00[0];
        field_0x00[1] = other.field_0x00[1];
        field_0x00[2] = other.field_0x00[2];

        // Copy three sub‑objects at offsets 12, 24, 36 from this/other
        copySubObject(reinterpret_cast<char *>(this) + 12,
                      reinterpret_cast<const char *>(&other) + 12);
        copySubObject(reinterpret_cast<char *>(this) + 24,
                      reinterpret_cast<const char *>(&other) + 24);
        copySubObject(reinterpret_cast<char *>(this) + 36,
                      reinterpret_cast<const char *>(&other) + 36);

        // Copy final dword at offset 48 (0x30)
        field_0x30 = other.field_0x30;

        return *this;
    }
};