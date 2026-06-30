// Xbox PDB: EARS::Alchemy::TEffectForce::TType::TType
// FUNC_NAME: initForceFeedbackConfig
// Function at 0x004f3290: Initializes the global ForceFeedback configuration structure.
// Returns pointer to the static instance.
// Offsets inside struct (from base 0x01218f60):
// +0x00: vtable pointer (void*)
// +0x04: name (const char*) -> "Force"
// +0x08: fourCC (int) -> 0x2e667263 (".frc" in little-endian)
// +0x0c: enabled1 (int) -> 1
// +0x10: enabled2 (int) -> 1
// +0x14: someFlag (int) -> 0
// +0x18: maxForce (int) -> 0x800 (2048)
// +0x1c: unknown0 (int) -> 0
// +0x20: unknown1 (int) -> 0
// +0x24: unknown2 (int) -> 0

struct ForceFeedbackConfig {
    void* vtable;          // +0x00
    const char* name;      // +0x04
    int fourCC;            // +0x08
    int enabled1;          // +0x0c
    int enabled2;          // +0x10
    int someFlag;          // +0x14
    int maxForce;          // +0x18
    int unknown0;          // +0x1c
    int unknown1;          // +0x20
    int unknown2;          // +0x24
};

// Extern declaration of the global configuration object (defined at 0x01218f60)
extern ForceFeedbackConfig g_forceFeedbackConfig;

ForceFeedbackConfig* initForceFeedbackConfig(void)
{
    g_forceFeedbackConfig.vtable = (void*)0x00e376c0; // PTR_LAB_00e376c0
    g_forceFeedbackConfig.name = "Force";
    g_forceFeedbackConfig.fourCC = 0x2e667263; // ".frc"
    g_forceFeedbackConfig.enabled1 = 1;
    g_forceFeedbackConfig.enabled2 = 1;
    g_forceFeedbackConfig.someFlag = 0;
    g_forceFeedbackConfig.maxForce = 0x800; // 2048
    g_forceFeedbackConfig.unknown0 = 0;
    g_forceFeedbackConfig.unknown1 = 0;
    g_forceFeedbackConfig.unknown2 = 0;

    return &g_forceFeedbackConfig;
}