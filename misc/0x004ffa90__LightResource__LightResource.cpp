// FUNC_NAME: LightResource::LightResource

// Light resource descriptor initializer function at 0x004ffa90
// Initializes a static global instance of LightResource (size 0x28 bytes)
class LightResource {
public:
    // +0x00: vtable pointer (points to LightResource vtable at 0x00e37bb8)
    void* vtablePtr;

    // +0x04: pointer to type name string "Light"
    const char* typeName;

    // +0x08: four character code (little-endian) – "lit." = 0x2e6c6974
    uint32_t fourCC;

    // +0x0C: unknown (zero)
    uint32_t flags;

    // +0x10: version number (9)
    uint32_t version;

    // +0x14: padding/unknown (zero)
    uint32_t pad1;

    // +0x18: maximum size or resource flag (0x800)
    uint32_t maxSize;

    // +0x1C: unknown (zero)
    uint32_t unk1;

    // +0x20: unknown (zero)
    uint32_t unk2;

    // +0x24: unknown (zero)
    uint32_t unk3;
};

// Static instance of LightResource at address 0x012190a0
LightResource gLightResource;

// Constructor (static initializer) for the global instance
__thiscall LightResource::LightResource() {
    this->vtablePtr = (void*)0x00e37bb8;  // LightResource vtable
    this->typeName = "Light";
    this->fourCC = 0x2e6c6974;            // "lit." in little-endian
    this->flags = 0;
    this->version = 9;
    this->pad1 = 0;
    this->maxSize = 0x800;
    this->unk1 = 0;
    this->unk2 = 0;
    this->unk3 = 0;
}