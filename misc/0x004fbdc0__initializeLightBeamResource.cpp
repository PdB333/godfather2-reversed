// FUNC_NAME: initializeLightBeamResource

// Structure representing the LightBeam resource descriptor
struct LightBeamResource {
    void*       vtable;       // +0x00 (0x01219078)
    const char* name;         // +0x04 (0x0121907c)
    uint32_t    nameTag;      // +0x08 (0x01219080) - e.g. "lbm." (0x2e6c626d)
    uint32_t    field_0C;     // +0x0C (0x01219084)
    uint32_t    field_10;     // +0x10 (0x01219088)
    uint32_t    field_14;     // +0x14 (0x0121908c)
    uint32_t    field_18;     // +0x18 (0x01219090)
    uint32_t    field_1C;     // +0x1C (0x01219094)
    uint32_t    field_20;     // +0x20 (0x01219098)
    uint32_t    field_24;     // +0x24 (0x0121909c)
};

// Global singleton for the LightBeam resource
LightBeamResource gLightBeamResource;

// Initializes and returns a pointer to the global LightBeam resource
LightBeamResource* initializeLightBeamResource(void) {
    gLightBeamResource.vtable  = &PTR_LAB_00e37aa0; // external function table
    gLightBeamResource.name    = "LightBeam";
    gLightBeamResource.nameTag = 0x2e6c626d;       // "lbm." (little‑endian __mbl__)
    gLightBeamResource.field_0C = 0;
    gLightBeamResource.field_10 = 1;
    gLightBeamResource.field_14 = 0;
    gLightBeamResource.field_18 = 0x800;           // size or resource ID
    gLightBeamResource.field_1C = 0;
    gLightBeamResource.field_20 = 0;
    gLightBeamResource.field_24 = 0;
    return &gLightBeamResource;
}