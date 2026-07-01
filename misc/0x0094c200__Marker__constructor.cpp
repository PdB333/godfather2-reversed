// FUNC_NAME: Marker::constructor
// 0x0094c200: Marker constructor - initializes waypoint/marker object with ID, parent, transform, color, and scale
class Marker {
public:
    // Assuming this is a constructor, returns this pointer
    // Parameters:
    //   id: unique identifier
    //   typeId: another identifier for type/category
    //   parentNode: pointer to parent list node (or null) for insertion into marker list
    //   color: optional RGBA color (4 floats), may be null
    //   flags: initial flags
    //   parentObject: some parent handle? (passed to sub init)
    //   scale: uniform scale factor
    //   radius: radius (stored squared)
    //   additionalParam: another handle (passed to sub init)
    Marker* __thiscall constructor(uint id, uint typeId, ListNode* parentNode, float* color, uint flags, void* parentObject, float scale, float radius, void* additionalParam);

    // Members (offsets in bytes from this):
    uint m_id;                              // +0x00
    uint m_typeId;                          // +0x04
    char m_name[16];                        // +0x08 (from snprintf)
    // Many other fields follow...
    // For brevity, only show those directly used:
    uint m_flags;                           // +0x11C (0x47*4)
    float m_scale;                          // +0x120 (0x48*4)
    float m_radiusSq;                       // +0x124 (0x49*4)
    ListNode m_node;                        // +0x168 (0x5a*4)  // prev/next for linked list
    float m_defaultColor;                   // +0x1D8 (0x76*4)  // some global default
    float m_color[4];                       // +0x130 (0x4c*4)  // from getSomeTransform?
    float m_customColor[4];                 // +0x140 (0x50*4)  // from param_5
    // ... many zeros init
};

// Linked list node structure (assumed)
struct ListNode {
    ListNode* prev;  // +0x00
    ListNode* next;  // +0x04
};

// External globals
extern float g_defaultFloatValue;            // _DAT_00d5780c
extern float g_anotherDefault;               // DAT_00d5ccf8
extern const char* s_markerPrefix;           // PTR_s_marker__00e56a54

// Sub-functions (addresses)
void __thiscall FUN_005c0a30();              // probably some engine init
void* __thiscall FUN_00950b20();              // returns pointer to 4 floats (e.g., world transform)
void __thiscall FUN_0094b290(void* param);    // attach to parent object
void __thiscall FUN_00948b20(void* param);    // some additional init
bool __thiscall FUN_0094b9b0();              // checks condition, returns bool

Marker* Marker::constructor(uint id, uint typeId, ListNode* parentNode, float* color, uint flags, void* parentObject, float scale, float radius, void* additionalParam) {
    this->m_id = id;
    this->m_typeId = typeId;
    this->m_flags = 2;                      // +0x46*4 = 0x118? Actually param_1[0x46] = 2 => offset 0x118
    this->m_flags = flags;                  // +0x47*4 (overwrites previous? Actually it's separate field? Let's assume m_flags at 0x118 and m_flags2 at 0x11C? The decomp shows param_1[0x47]=flags, so that's consistent with m_flags at 0x11C. But also set m_flags=2 earlier? Wait: param_1[0x46] = 2 and param_1[0x47] = param_6. So they are different fields. We'll name m_subType = 2 and m_flags = flags.
    m_subType = 2;                          // +0x118
    m_flags = flags;                        // +0x11C
    m_scale = 0.0f;                         // +0x120
    m_radiusSq = radius * radius;           // +0x124
    // ... many zeros follow in decomp (0x55-0x59, etc.)
    // Initialize many fields to 0 (omitted for brevity, but in real code we'd list them)

    // Linked list insertion
    if (parentNode == nullptr) {
        parentNode = nullptr;  // redundant
    } else {
        parentNode = (ListNode*)((uint)parentNode + 0x48);  // adjust pointer? This is suspicious: adding 0x48 to parentNode pointer seems like it's treating parentNode as offset into some struct? Actually in the decomp, param_4 is int, but if param_4 !=0, it does param_4 = param_4 + 0x48. That could be adding offset to get the ListNode* from a parent object? Possibly parentNode is actually a pointer to an object that contains a ListNode at offset 0x48? But the code then uses param_4 as ListNode*. To be faithful, we'll assume parentNode is actually a ListNode* and the addition is to get something else? However, the decomp suggests parentNode is a pointer to a node, and it adds 0x48 to get to a field? No, it adds after checking param_4 !=0. It's likely a bug in decomp: param_4 is an integer (maybe an ID) and they treat it as pointer? But then they dereference *(param_4+4) - that would be reading from memory. So param_4 must be a pointer. The +0x48 could be a field offset within that object to get the list node. But then they set param_1[0x5a]=param_4, meaning they store this adjusted pointer. So parentNode parameter is actually a pointer to an object that has a list node at offset 0x48. So we'll rename parentNode to parentObj, and inside we compute its list node address as ((ListNode*)((char*)parentObj + 0x48)). 
    // Let's change: 
    // param_4 is a pointer to an object with a list node at offset 0x48.
    // So we calculate: ListNode* parentListNode = (parentObj != nullptr) ? (ListNode*)((char*)parentObj + 0x48) : nullptr;
    }
    m_node.prev = parentListNode;
    m_node.next = nullptr;
    if (parentListNode != nullptr) {
        m_node.next = parentListNode->next;  // original next becomes our next
        parentListNode->next = &m_node;       // link parent to us
    }
    // Also set m_node.prev? Actually the code sets param_1[0x5b] = *(param_4+4) (that's the next pointer). So m_node.next = parentListNode->next.
    // Then it sets *(param_4+4) = param_1+0x5a (which is address of m_node). So parentListNode->next = &m_node.
    // The prev pointer (m_node.prev) is set to parentListNode? Not explicitly; but in the code param_1[0x5a]=param_4, so m_node.prev = parentListNode. Yes.
    m_node.prev = parentListNode;
    // The code also sets param_1[0x5b] (m_node.next) from parentListNode->next, then sets parentListNode->next = &m_node.
    // So:
    m_node.next = (parentListNode != nullptr) ? parentListNode->next : nullptr;
    if (parentListNode != nullptr) {
        parentListNode->next = &m_node;
    }

    // Call some sub-inits
    FUN_005c0a30();  // some global engine init

    // Get default color/transform from global
    float* worldTransform = (float*)FUN_00950b20();
    if (worldTransform == nullptr) {
        m_color[0] = 0.0f;
        m_color[1] = 0.0f;
        m_color[2] = 0.0f;
        m_color[3] = 0.0f;
    } else {
        m_color[0] = worldTransform[0];
        m_color[1] = worldTransform[1];
        m_color[2] = worldTransform[2];
        m_color[3] = g_defaultFloatValue;  // _DAT_00d5780c
    }

    // Set custom color from param_5 (color pointer)
    if (color == nullptr) {
        m_customColor[0] = 0.0f;
        m_customColor[1] = 0.0f;
        m_customColor[2] = 0.0f;
        m_customColor[3] = 0.0f;
    } else {
        m_customColor[0] = color[0];
        m_customColor[1] = color[1];
        m_customColor[2] = color[2];
        m_customColor[3] = color[3];
    }

    FUN_0094b290(parentObject);   // attach to parent
    FUN_00948b20(additionalParam); // additional setup

    // Update scale if different
    if (m_scale != scale) {
        m_scale = scale;
        m_flags |= 0x200000;
    }

    // Check some condition from FUN_0094b9b0
    if (!((m_flags >> 7) & 1) && !FUN_0094b9b0()) {
        m_flags |= 0x40000;
    }

    // Zero some bytes
    *(char*)(this + 0x54) = 0;   // byte at offset 0x150? Actually (int)(param_1+0x54) -> offset 0x150? Wait: param_1 is pointer to int, so (param_1+0x54) is address of param_1[0x54] which is offset 0x150 in bytes. That's a byte? The decomp says *(undefined1 *)(param_1 + 0x54) = 0; so it's a byte at offset 0x150. Similarly +0x151, +0x152, +0x153.
    *(char*)((char*)this + 0x151) = 0;
    *(char*)((char*)this + 0x152) = 0;
    *(char*)((char*)this + 0x153) = 0;

    // Also a byte at offset (char*)this + 0x1dd set to 0 earlier.
    // And at +(param_1+0x77) set to 1 (byte at offset 0x1DC)
    *(char*)((char*)this + 0x1DC) = 1;   // from *(undefined1 *)(param_1 + 0x77) = 1; offset 0x1DC

    // And at offset +0x1DD = 0 (from *(undefined1 *)((int)param_1 + 0x1dd) = 0)
    *(char*)((char*)this + 0x1DD) = 0;

    // Also set m_defaultColor and m_anotherDefault from globals
    m_defaultColor = g_defaultFloatValue;  // from _DAT_00d5780c
    m_anotherDefault = g_anotherDefault;   // from DAT_00d5ccf8? Actually param_1[0x79] and [0x7a] both set to uVar2 which is DAT_00d5ccf8. So two fields.

    // snprintf for name
    snprintf((char*)this + 8, 0x10, "%s%u", s_markerPrefix, id);

    // Many more fields set to 0, omitted.

    return this;
}