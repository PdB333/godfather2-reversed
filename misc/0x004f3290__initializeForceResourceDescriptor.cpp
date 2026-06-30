// FUNC_NAME: initializeForceResourceDescriptor

struct ForceResourceDescriptor {
    void* vtable;         // +0x00
    const char* name;     // +0x04
    uint32_t fourCC;      // +0x08
    bool flag1;           // +0x0C
    bool flag2;           // +0x10
    bool flag3;           // +0x14
    uint32_t size;        // +0x18
    bool flag4;           // +0x1C
    bool flag5;           // +0x20
    bool flag6;           // +0x24
};

// Static singleton initialization of the Force resource descriptor
ForceResourceDescriptor* initializeForceResourceDescriptor() {
    static ForceResourceDescriptor desc;
    desc.vtable = &PTR_LAB_00e376c0;  // Virtual function table
    desc.name   = "Force";            // Friendly resource type name
    desc.fourCC = 0x2e667263;         // Four-character code (e.g., ".frc" or magic)
    desc.flag1  = true;               // +0x0C
    desc.flag2  = true;               // +0x10
    desc.flag3  = false;              // +0x14
    desc.size   = 0x800;              // +0x18 (likely buffer size or limit)
    desc.flag4  = false;              // +0x1C
    desc.flag5  = false;              // +0x20
    desc.flag6  = false;              // +0x24
    return &desc;
}

// In memory, the static instance is at 0x01218f60 (address of desc).
// The function returns the pointer to the descriptor.