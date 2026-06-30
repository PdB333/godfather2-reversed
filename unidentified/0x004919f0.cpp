// FUN_NAME: Entity::applyTemplateData
// Function address: 0x004919f0
// Reads a data template from a global table and applies it to the entity's physics/physics object.
// Templates are stored in a global array at 0x011a0f28, each entry 0x38 bytes.
// Parameters:
//   templateId (EAX) – index into the template table (must be < 0x1000)
//   extraParam (stack) – additional parameter passed to inner update function

class Entity; // Forward declaration

// Global template table entry definition
struct TemplateEntry {
    uint16_t field_0;   // +0x00
    uint16_t field_2;   // +0x02
    uint16_t field_4;   // +0x04
    // ... remaining 0x38 bytes (0x34 more bytes follow)
};

extern TemplateEntry gTemplateTable[0x1000]; // At 0x011a0f28, size 0x38 each

// External helper functions (defined elsewhere)
extern void FUN_006063b0();                   // Called on flag condition
extern void FUN_0060b020(uint32_t systemPtr, uint32_t param1, uint32_t extraParam);
extern void FUN_0060add0(uint32_t systemPtr, uint32_t physicsObj, uint32_t* templateData);

void Entity::applyTemplateData(uint32_t templateId, uint32_t extraParam)
{
    // Access the template table
    TemplateEntry* entry;
    if (templateId < 0x1000) {
        entry = &gTemplateTable[templateId];
    } else {
        entry = nullptr; // Invalid index; fall through to null pointer? (original does so)
    }
    // Store two ushort values as floats
    this->someFloat1 = (float)entry->field_2;  // +0x338
    this->someFloat2 = (float)entry->field_4;  // +0x33c

    // If a flag is set, call an extra function (possibly reset physics state)
    if (this->flagField != 0) {                // +0x350
        FUN_006063b0();
    }

    // Apply the template to a system (likely physics system)
    FUN_0060b020(
        *(uint32_t*)&this->systemManager,      // +0x14
        this->someParam,                        // +0x354
        extraParam
    );

    // Update a physics object with the template data
    FUN_0060add0(
        *(uint32_t*)&this->systemManager,      // +0x14
        this->physicsObject,                    // +0x320 (800 decimal)
        &this->templateData                     // +0x330 (base of stored template floats)
    );
}