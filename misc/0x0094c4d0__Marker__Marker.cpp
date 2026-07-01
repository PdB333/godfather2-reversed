// FUNC_NAME: Marker::Marker

// Address: 0x0094c4d0
// Constructor for Marker class (EA EARS engine). Initializes a marker object with ID, type, flags, radius, and other fields.
// The marker name is generated as "marker<id>" via snprintf.

Marker::Marker(uint32_t id, uint32_t type, uint32_t arg4, uint32_t flags, uint32_t arg6, float radius)
{
    // Internal init (likely sets up some global state)
    FUN_005c0a30();

    uint32_t defaultVal1 = g_defaultValue;   // _DAT_00d5780c
    uint32_t defaultVal2 = g_anotherDefault; // DAT_00d5ccf8

    // Core fields
    m_type = type;                       // +0x04
    m_markerSubType = 3;                 // +0x118 (index 0x46)
    m_id = id;                           // +0x00
    m_flags = flags;                     // +0x11C (index 0x47)
    m_radius = 0.0f;                     // +0x120 (index 0x48)
    // Clear many zero fields (offsets 0x124 to 0x1D4)
    m_field49 = 0;                       // +0x124
    m_field4A = 0;                       // +0x128
    m_field55 = 0;                       // +0x154
    m_field56 = 0;                       // +0x158
    m_field57 = 0;                       // +0x15C
    m_field58 = 0;                       // +0x160
    m_field59 = 0;                       // +0x164
    m_field5A = 0;                       // +0x168
    m_field5B = 0;                       // +0x16C
    m_field5C = arg4;                    // +0x170 (index 0x5C)
    m_field64 = 0;                       // +0x190 (index 0x64)
    // ... (many more zeros from +0x194 to +0x1D4)
    m_field65 = 0;                       // +0x194
    m_field66 = 0;                       // +0x198
    m_field67 = 0;                       // +0x19C
    m_field68 = 0;                       // +0x1A0
    m_field69 = 0;                       // +0x1A4
    m_field6A = 0;                       // +0x1A8
    m_field6B = 0;                       // +0x1AC
    m_field6C = 0;                       // +0x1B0
    m_field6D = 0;                       // +0x1B4
    m_field6E = 0;                       // +0x1B8
    m_field6F = 0;                       // +0x1BC
    m_field70 = 0;                       // +0x1C0
    m_field71 = 0;                       // +0x1C4
    m_field72 = 0;                       // +0x1C8
    m_field73 = 0;                       // +0x1CC
    m_field74 = 0;                       // +0x1D0
    m_field75 = 0;                       // +0x1D4

    m_field76 = defaultVal1;             // +0x1D8 (index 0x76)
    m_byteAt1DC = 1;                     // +0x1DC (byte)
    m_byteAt1DD = 0;                     // +0x1DD (byte)
    m_field78 = 0;                       // +0x1E0 (index 0x78)
    m_field79 = defaultVal2;             // +0x1E4 (index 0x79)
    m_field7A = defaultVal2;             // +0x1E8 (index 0x7A)
    m_field80 = 0;                       // +0x200 (index 0x80)
    m_field7F = 0;                       // +0x1FC (index 0x7F)
    m_field7E = 0;                       // +0x1F8 (index 0x7E)
    m_field7D = 0;                       // +0x1F4 (index 0x7D)
    m_field7C = 0;                       // +0x1F0 (index 0x7C)
    m_field84 = 0;                       // +0x210 (index 0x84)
    m_field85 = 0;                       // +0x214 (index 0x85)
    m_field86 = 0;                       // +0x218 (index 0x86)
    m_field87 = 0;                       // +0x21C (index 0x87)

    // Generate marker name: "marker" + id
    __snprintf(m_name, 16, "%s%u", g_markerNamePrefix, id); // m_name at +0x08

    m_byteAt18 = 0;                      // +0x18 (byte from index 6)
    m_field4F = 0;                       // +0x13C (index 0x4F)
    m_field4E = 0;                       // +0x138 (index 0x4E)
    m_field4D = 0;                       // +0x134 (index 0x4D)
    m_field4C = 0;                       // +0x130 (index 0x4C)
    m_field53 = 0;                       // +0x14C (index 0x53)
    m_field52 = 0;                       // +0x148 (index 0x52)
    m_field51 = 0;                       // +0x144 (index 0x51)
    m_field50 = 0;                       // +0x140 (index 0x50)

    // Initialize sub-object/resource with arg6
    initInternal(arg6);                  // FUN_0094b290

    // Handle radius parameter
    if (m_radius != radius) {
        m_radius = radius;
        m_flags |= 0x200000;
    }

    // Check a flag: if bit 7 is clear, call a function that may set another flag
    if (((m_flags >> 7) & 1) == 0) {
        char checkResult = checkSomeCondition(); // FUN_0094b9b0
        if (checkResult == '\0') {
            m_flags |= 0x40000;
        }
    }

    // Zero out a few more bytes (at +0x153, +0x152, +0x151, +0x150)
    m_byteAt153 = 0;                     // +0x153
    m_byteAt152 = 0;                     // +0x152
    m_byteAt151 = 0;                     // +0x151
    m_byteAt150 = 0;                     // +0x150 (byte from param_1[0x54] cast to byte)

    return this;
}