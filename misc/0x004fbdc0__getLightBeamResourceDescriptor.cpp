// FUNC_NAME: getLightBeamResourceDescriptor
// Function at 0x004fbdc0: initializes and returns a static resource descriptor for "LightBeam" resource type.
// Used by EARS asset manager to register a custom resource (e.g., .lbm files).

// External vtable pointer (likely for the resource descriptor class)
extern void* g_objVtable_00e37aa0;

// Structure for resource descriptor (offsets relative to base 0x01219078)
struct LightBeamResourceDescriptor {
    void* vtable;           // +0x00: pointer to vtable
    const char* name;       // +0x04: resource type name ("LightBeam")
    unsigned int fileCode;  // +0x08: magic file extension code (0x2e6c626d = ".lbm")
    unsigned int field_0c;  // +0x0c: unknown (0)
    unsigned int version;   // +0x10: version or flags (1)
    unsigned int field_14;  // +0x14: unknown (0)
    unsigned int bufSize;   // +0x18: default buffer size (0x800 = 2048)
    unsigned int field_1c;  // +0x1c: unknown (0)
    unsigned int field_20;  // +0x20: unknown (0)
    unsigned int field_24;  // +0x24: unknown (0)
};

// Static global descriptor
LightBeamResourceDescriptor g_lightBeamDescriptor;

LightBeamResourceDescriptor* getLightBeamResourceDescriptor(void)
{
    g_lightBeamDescriptor.vtable   = &g_objVtable_00e37aa0;
    g_lightBeamDescriptor.name     = "LightBeam";
    g_lightBeamDescriptor.fileCode = 0x2e6c626d; // ".lbm"
    g_lightBeamDescriptor.field_0c = 0;
    g_lightBeamDescriptor.version  = 1;
    g_lightBeamDescriptor.field_14 = 0;
    g_lightBeamDescriptor.bufSize  = 0x800; // 2048
    g_lightBeamDescriptor.field_1c = 0;
    g_lightBeamDescriptor.field_20 = 0;
    g_lightBeamDescriptor.field_24 = 0;
    return &g_lightBeamDescriptor;
}