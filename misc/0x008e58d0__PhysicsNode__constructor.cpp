// FUNC_NAME: PhysicsNode::constructor
// This function is a constructor for a PhysicsNode (or similar class) in the EARS engine.
// Initializes the object with a vtable pointer, function tables, and debug sentinel values.
// Address: 0x008e58d0

class PhysicsNode {
public:
    // +0x00: vtable pointer
    // +0x3C (offset 0x0F words): pointer to second function table
    // +0x48 (offset 0x12 words): pointer to third function table
    // +0x50 (offset 0x14 words): block of 4-member groups (17 groups) filled with sentinel values
    // +0x190 (offset 0x64 words): end of last group

    // ... (actual members not fully known, but the constructor fills many fields with magic constants)
};

// Base class initialization routine
extern void __thiscall initializeBase(PhysicsNode* base, void* param); // approximated

PhysicsNode* __thiscall PhysicsNode::constructor(PhysicsNode* this, void* param2) {
    // Call base class initializer (likely sets up own vtable and fields)
    initializeBase(this, param2);

    // Set vtable pointer (first member)
    this->vtable = (void*)0x00d8045c; // pointer to vtable

    // Set additional function tables
    *(void**)((unsigned char*)this + 0x3C) = (void*)0x00d8044c; // +0x3C: pointer to some table
    *(void**)((unsigned char*)this + 0x48) = (void*)0x00d80448; // +0x48: pointer to another table

    // Initialize "dead zone" fields to 0
    *(int*)((unsigned char*)this + 0x50) = 0; // offset 0x50
    *(int*)((unsigned char*)this + 0x54) = 0;
    *(int*)((unsigned char*)this + 0x58) = 0;
    *(int*)((unsigned char*)this + 0x5C) = 0;

    // Fill 17 groups of 4 words each with sentinel values.
    // These groups are scattered at specific offsets.
    // Each group: {0xBADBADBA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911}
    struct SentinelGroup {
        unsigned int a; // 0xBADBADBA
        unsigned int b; // 0xBEEFBEEF
        unsigned int c; // 0xEAC15A55
        unsigned int d; // 0x91100911
    };

    // Group start offsets (in bytes)
    // Offsets: 0x50, 0x74, 0x84, 0x98, 0xA8, 0xBC, 0xCC, 0xE0, 0xF0, 0x104, 0x114, 0x128, 0x138, 0x14C, 0x15C, 0x170, 0x180
    static const unsigned int groupOffsets[] = {
        0x50, 0x74, 0x84, 0x98, 0xA8, 0xBC, 0xCC, 0xE0, 0xF0,
        0x104, 0x114, 0x128, 0x138, 0x14C, 0x15C, 0x170, 0x180
    };
    const int numGroups = sizeof(groupOffsets) / sizeof(groupOffsets[0]);

    for (int i = 0; i < numGroups; ++i) {
        unsigned char* base = (unsigned char*)this + groupOffsets[i];
        SentinelGroup* sg = (SentinelGroup*)base;
        sg->a = 0xBADBADBA;
        sg->b = 0xBEEFBEEF;
        sg->c = 0xEAC15A55;
        sg->d = 0x91100911;
    }

    // Note: Additional fields may exist beyond the last group.
    // The function returns 'this' as per constructor convention.
    return this;
}