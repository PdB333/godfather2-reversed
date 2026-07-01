// FUNC_NAME: FamilyManager::FamilyManager
// Address: 0x0080c150
// Constructor for FamilyManager. Initializes all fields to default values.
// Many fields are set to a global default object pointer (gDefaultObject).
// Specific fields: +0x44 = 4 (max families?), +0x48 = 5000 (reputation threshold?).

#include <cstdint>

// Global default object pointer (likely null or sentinel)
extern void* gDefaultObject;

void __fastcall FamilyManager::FamilyManager(FamilyManager* this) {
    // Clear first 8 dwords (offset 0x00 to 0x1C)
    this->field_0x00 = 0;
    this->field_0x04 = 0;
    this->field_0x08 = 0;
    this->field_0x0C = 0;
    this->field_0x10 = 0;
    this->field_0x14 = 0;
    this->field_0x18 = 0;
    this->field_0x1C = 0;

    // +0x20: pointer to default object
    this->field_0x20 = gDefaultObject;

    // Clear next 7 dwords (offset 0x24 to 0x3C)
    this->field_0x24 = 0;
    this->field_0x28 = 0;
    this->field_0x2C = 0;
    this->field_0x30 = 0;
    this->field_0x34 = 0;
    this->field_0x38 = 0;
    this->field_0x3C = 0;

    // +0x40: pointer to default object
    this->field_0x40 = gDefaultObject;

    // +0x44: max families (4)
    this->maxFamilies = 4;

    // +0x48: reputation threshold (5000)
    this->reputationThreshold = 5000;

    // Set fields +0x4C to +0x88 (16 dwords) to default object
    this->field_0x4C = gDefaultObject;
    this->field_0x50 = gDefaultObject;
    this->field_0x54 = gDefaultObject;
    this->field_0x58 = gDefaultObject;
    this->field_0x5C = gDefaultObject;
    this->field_0x60 = gDefaultObject;
    this->field_0x64 = gDefaultObject;
    this->field_0x68 = gDefaultObject;
    this->field_0x6C = gDefaultObject;
    this->field_0x70 = gDefaultObject;
    this->field_0x74 = gDefaultObject;
    this->field_0x78 = gDefaultObject;
    this->field_0x7C = gDefaultObject;
    this->field_0x80 = gDefaultObject;
    this->field_0x84 = gDefaultObject;
    this->field_0x88 = gDefaultObject;

    // Clear fields +0x8C to +0x98 (4 dwords)
    this->field_0x8C = 0;
    this->field_0x90 = 0;
    this->field_0x94 = 0;
    this->field_0x98 = 0;

    // Set fields +0x9C to +0xBC (9 dwords) to default object
    this->field_0x9C = gDefaultObject;
    this->field_0xA0 = gDefaultObject;
    this->field_0xA4 = gDefaultObject;
    this->field_0xA8 = gDefaultObject;
    this->field_0xAC = gDefaultObject;
    this->field_0xB0 = gDefaultObject;
    this->field_0xB4 = gDefaultObject;
    this->field_0xB8 = gDefaultObject;
    this->field_0xBC = gDefaultObject;
}