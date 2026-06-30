// FUNC_NAME: ParticleEmitter::initializeFromConfig
class ParticleEmitter {
public:
    // vtable at 0x00e37d00
    virtual void unknownVirtual(); // stub

    void initializeFromConfig(void* config); // function at 0x00500b50

    // Offsets (guessed):
    // +0x00: vtable pointer
    // +0x04-0x08: possibly other data
    // +0x24: (through config pointer) flags
    // +0x30: (through config) base scale
    // +0x09: (local array index, 9th element) source object pointer
    // +0x0a: (10th element) final scale
    // +0x0b: (11th element) computed scale
    // +0x0c: (12th element) some float field
    // +0x0d: (13th element) some int field
    // +0x0f: (15th element) duration
    // +0x10: (16th element) start delay
    // +0x11: (17th element) resource handle
    // +0x12: (18th element) resource ID
    // etc.

    // Member fields inferred from offsets:
    // +0x00: vtable
    // +0x04: ...?
    // +0x09: void* m_configSource; (pointer to config object)
    // +0x0a: float m_scaleFinal;
    // +0x0b: float m_scaleBase;
    // +0x0c: float m_unknown;
    // +0x0d: int m_flags; (0x00 = not initialized?)
    // +0x0f: float m_duration;
    // +0x10: float m_delay;
    // +0x11: int m_resourceHandle;
    // +0x12: int m_resourceID;

    // Note: The config pointer passed as argument is also used to read flags at offset +0x24 and +0xd (of config).
};

// Global constants
const int MAX_RESOURCE_COUNT = 0x13; // 19
extern int g_maxResourceCount; // DAT_010c2328
extern float g_defaultDuration; // DAT_00e2b1a4

// Forward declarations of helper functions
void baseConstructor(); // FUN_00533cc0
int getResourceID(); // FUN_004dafd0
int allocateResource(int type); // FUN_004eb950
float getRandomFloat(); // FUN_004e41b0
void finalizeInit(ParticleEmitter* self); // FUN_00500980

void ParticleEmitter::initializeFromConfig(void* config) {
    baseConstructor();
    this->vtable = &PTR_FUN_00e37d00; // Set vtable

    // Check if config is already processed (byte at config+0xd)
    if (*(char*)(config + 0xd) == '\0') {
        // Save config pointer
        this->m_configSource = config;
        this->m_resourceHandle = 0;

        // Get resource ID
        int resId = getResourceID();
        this->m_resourceID = resId;

        // Check flags in config: bit 30 (0x40000000) for ignore global?
        if ((*(uint*)(config + 0x24) & 0x40000000) == 0) {
            int handle;
            if (g_maxResourceCount < 0x13) {
                handle = allocateResource(1); // type 1
            } else {
                handle = 0;
            }
            this->m_resourceHandle = handle;

            if (handle == 0) {
                // Set byte at config+0xc to indicate failure? (unclear)
                *(char*)(config + 0xc) = 1;
                return;
            }

            // Initialize allocated resource float field at +0x10 to 0.0
            *(float*)(handle + 0x10) = 0.0f;
        }

        // Check flag bit 2 (0x4) for random scale
        if ((*(char*)(config + 0x24) & 4) == 0) {
            // Use base scale directly
            this->m_scaleBase = *(float*)(config + 0x30);
        } else {
            // Randomize scale
            float rand = getRandomFloat();
            this->m_scaleBase = rand * *(float*)(config + 0x30);
        }

        // Set duration from global default
        this->m_duration = g_defaultDuration;

        // Final scale equals computed scale
        this->m_scaleFinal = this->m_scaleBase;
        this->m_delay = 0.0f;

        // Finalize initialization
        finalizeInit(this);
    }
}