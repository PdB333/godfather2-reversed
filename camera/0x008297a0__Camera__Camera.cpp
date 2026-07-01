// FUNC_NAME: Camera::Camera

// Constructor for Camera class at 0x008297a0
// Initializes camera with global defaults and zeroed matrix/state fields.
// Object size: at least 0xA8 bytes (0x2A * 4)
class Camera {
public:
    // +0x00: vtable pointer
    void* vtable;

    // -- matrix / state areas (24 ints = 96 bytes) --
    // +0x50: 4 ints (index 0x14..0x17)
    int   unk50[4];

    // +0x60: 2 ints (index 0x18..0x19) set to defaultVal
    int   unk60;
    int   unk64;

    // +0x68: 1 int (index 0x1a) set to 0
    int   unk68;

    // +0x70: 4 ints (index 0x1c..0x1f) set to 0
    int   unk70[4];

    // +0x80: 4 ints (index 0x20..0x23) set to 0
    int   unk80[4];

    // -- float / vector fields --
    // +0x90: initialized from DATA_0xd5ddec
    float float90;

    // +0x94: initialized from DATA_0xd5780c (defaultVal)
    float float94;

    // +0x98: initialized from DATA_0xd5780c (defaultVal)
    float float98;

    // +0x9C: initialized from DATA_0xd5eee4
    float float9C;

    // +0xA0: initialized from DATA_0xd5780c (defaultVal)
    float floatA0;

    // +0xA4: initialized from DATA_0xd5780c (defaultVal)
    float floatA4;

    // Constructor (fastcall / thiscall)
    Camera* __fastcall Constructor() {
        // Call base constructor (likely Camera or Framework::Object)
        // Address 0x008334a0
        baseConstructor();

        // Load global constants (these are likely 1.0f / -1.0f / etc.)
        float defaultVal = *(float*)0x00d5780c; // e.g., 1.0f
        float val90      = *(float*)0x00d5ddec;
        float val9C      = *(float*)0x00d5eee4;

        // Set vtable
        this->vtable = (void*)0x00d7333c;

        // Initialize float/vector fields
        this->float90 = val90;
        this->float9C = val9C;
        this->float94 = defaultVal;
        this->float98 = defaultVal;
        this->floatA0 = defaultVal;
        this->floatA4 = defaultVal;

        // Zero out matrix/state groups
        this->unk50[0] = 0;
        this->unk50[1] = 0;
        this->unk50[2] = 0;
        this->unk50[3] = 0;

        // Set two fields to defaultVal (not zero)
        this->unk60 = *(int*)&defaultVal; // reinterpret cast
        this->unk64 = *(int*)&defaultVal;

        this->unk68 = 0;

        this->unk70[0] = 0;
        this->unk70[1] = 0;
        this->unk70[2] = 0;
        this->unk70[3] = 0;

        this->unk80[0] = 0;
        this->unk80[1] = 0;
        this->unk80[2] = 0;
        this->unk80[3] = 0;

        return this;
    }

private:
    // Placeholder for base constructor call
    void baseConstructor();
};