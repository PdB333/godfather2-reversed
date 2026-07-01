// FUNC_NAME: AmbientEffect::AmbientEffect

#include <cstdint>

// External globals (from the binary)
extern float g_globalScale;         // 0x00e445c8
extern float g_constantFloat;       // 0x00d5780c
extern void* g_vtable;              // 0x00d7cb78

// Callees (engine functions)
extern void globalInit(void);                                     // 0x0060ffd0
extern void setupPositions(const void* positions);                // 0x00610040
extern void initSubObject(void* subObject);                       // 0x00610160

// Config structure for property pairs
struct PropertyPair {
    float value;        // +0x00
    float unk[3];       // +0x04
    float key;          // +0x10
};

struct EffectConfig {
    uint8_t pad[0x1C];                    // +0x00
    PropertyPair** propertyArray;         // +0x1C
    uint16_t propertyCount;               // +0x20
};

// Hypothetical class representing an ambient effect
class AmbientEffect {
public:
    void** vtable;          // +0x00
    void* resourceManager;  // +0x04
    uint8_t flag;           // +0x08
    float propA;            // +0x0C
    // padding 0x10-0x1B (not used)
    float propB;            // +0x1C
    float propC;            // +0x20
    float propD;            // +0x24
    int32_t intField1;      // +0x28
    int32_t intField2;      // +0x2C
    // sub-object at +0x30 (size unknown)
    uint8_t subObject[1];   // placeholder
};

// Constructor
AmbientEffect* AmbientEffect::AmbientEffect(void* resourceManager, EffectConfig* config) {
    // Call virtual init on resource manager (offset +0x08 -> vtable +4)
    auto resourceVtable = *reinterpret_cast<void***>(reinterpret_cast<char*>(resourceManager) + 8);
    reinterpret_cast<void(*)(void)>(resourceVtable[1])();

    // Base initialisation
    this->resourceManager = resourceManager;
    this->vtable = &g_vtable;
    this->flag = 0;
    this->propA = 0.0f;
    this->intField1 = 0;
    this->intField2 = 0;

    globalInit();

    this->propB = 0.0f;
    this->propC = 0.0f;
    this->propD = 0.0f;

    // Load property pairs from config
    if (config->propertyCount != 0) {
        for (uint32_t i = 0; i < config->propertyCount; ++i) {
            PropertyPair* pair = config->propertyArray[i];
            float key = pair->key;
            float value = pair->value;

            // Bitwise categorisation (original optimisation)
            uint32_t bits = reinterpret_cast<uint32_t&>(key);
            if (bits < 0x24e34aa1) {
                // Small positive floats
                if (key == 9.857198e-17f) {
                    this->propD = value;
                } else if (key == 9.8571964e-17f) {
                    this->propB = value;
                } else if (key == 9.857197e-17f) {
                    this->propC = value;
                }
            } else {
                // Large negative floats
                if (key == -3.6446247e+24f) {
                    this->propA = value * g_globalScale;
                }
            }
        }
    }

    // Prepare four positions for further setup
    struct Position { float x, y, z, w; };
    Position positions[4] = {
        { g_constantFloat, 0.0f, 0.0f, 0.0f },
        { g_constantFloat, 0.0f, 0.0f, 0.0f },
        { g_constantFloat, 0.0f, 0.0f, 0.0f },
        { g_constantFloat, 0.0f, 0.0f, 0.0f }
    };
    setupPositions(positions);

    // Second virtual call – init sub-object if needed
    auto ret = reinterpret_cast<int32_t(*)(void)>(resourceVtable[1])();
    if (ret != 0) {
        initSubObject(&this->subObject);
    }

    return this;
}