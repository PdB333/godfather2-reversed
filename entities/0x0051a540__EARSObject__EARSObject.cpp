// FUNC_NAME: EARSObject::EARSObject

void initializeBase(void);            // corresponds to FUN_0051a650
void finalizeConstruction(void* thisObj); // corresponds to FUN_009c8eb0

class EARSObject {
public:
    // Constructor with creation flags (bitmask)
    EARSObject(byte creationFlags);
    // ... other members
};

EARSObject::EARSObject(byte creationFlags) {
    // Perform base initialization (vtable setup, common fields)
    initializeBase();

    // If bit 0 is set, run post-construction logic
    if (creationFlags & 1) {
        finalizeConstruction(this);
    }
}