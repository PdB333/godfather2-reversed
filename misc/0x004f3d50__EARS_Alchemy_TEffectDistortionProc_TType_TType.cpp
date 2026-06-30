// Xbox PDB: EARS::Alchemy::TEffectDistortionProc::TType::TType
// FUNC_NAME: DistortionProcessor::initializeStaticData
#include <cstdint>

// Static data structure for distortion shader processor
struct DistortionStaticData {
    void** vtable;               // +0x00
    const char* shaderName;      // +0x04
    uint32_t magic;              // +0x08  // 0x2e647470 = ".dtp" in little-endian? ("ptd.")
    uint32_t field0C;            // +0x0C
    uint32_t field10;            // +0x10
    uint32_t field14;            // +0x14
    uint32_t bufferSize;         // +0x18  // 0x800 = 2048
    uint32_t field1C;            // +0x1C
    uint32_t field20;            // +0x20
    uint32_t field24;            // +0x24
};

// Global static data for the distortion processor
// Addresses are relative to base 0x01218f88
extern void* PTR_LAB_00e37758;   // likely vtable pointer
extern DistortionStaticData gDistortionStaticData;

// Initialize static fields and return pointer to the static data
DistortionStaticData* DistortionProcessor::initializeStaticData() {
    gDistortionStaticData.vtable = &PTR_LAB_00e37758;
    gDistortionStaticData.shaderName = "DistortionProc";
    gDistortionStaticData.magic = 0x2e647470; // ".dtp" magic bytes
    gDistortionStaticData.field0C = 0;
    gDistortionStaticData.field10 = 1;
    gDistortionStaticData.field14 = 0;
    gDistortionStaticData.bufferSize = 0x800;
    gDistortionStaticData.field1C = 0;
    gDistortionStaticData.field20 = 0;
    gDistortionStaticData.field24 = 0;
    return &gDistortionStaticData;
}