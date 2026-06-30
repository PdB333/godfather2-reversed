// FUNC_NAME: SimNpc::initializeFromTemplate
void __thiscall SimNpc::initializeFromTemplate(int thisPtr, int templateId, int* outData, int resourceHandle, uint flags, int* outError)
{
    byte isTemplate = *(byte*)(thisPtr + 0x1c); // +0x1c: flag indicating if this is a template instance
    int dataPtr = *outData; // pointer to the output structure being initialized
    int templateData = FUN_00672a80(); // get template data (likely from a pool or manager)

    if (templateData != 0) {
        // Template found: copy data from template into output structure
        if ((flags & 4) == 0) {
            *outError = 0;
        } else {
            FUN_00674d40(resourceHandle, 0, 0, outError); // load additional data from resource
        }

        // Handle attachment pointers (left/right hand)
        if (*(int*)(templateData + 0x50) == 0 && *(int*)(templateData + 0x4c) == 0) {
            // No attachments: clear both pointers
            *(int*)(dataPtr + 0x11c) = 0; // +0x11c: left hand attachment pointer
            *(int*)(dataPtr + 0x118) = 0; // +0x118: right hand attachment pointer
        } else if (*(short*)(templateData + 0x5a) == 1) {
            // Left-handed: set left hand attachment
            *(int*)(dataPtr + 0x11c) = templateData + 0x68; // +0x68: attachment data
        } else {
            // Right-handed: set right hand attachment
            *(int*)(dataPtr + 0x118) = templateData + 0x68;
        }

        // Clear unknown flag at +0x30
        *(int*)(dataPtr + 0x30) = 0;

        // Copy transform/animation data from template (offsets 0x14..0x5c)
        *(int*)(dataPtr + 0xcc) = (int)*(short*)(templateData + 0x14); // +0xcc: short
        *(float*)(dataPtr + 0xd0) = *(float*)(templateData + 0x18);   // +0xd0: float
        *(float*)(dataPtr + 0xd4) = *(float*)(templateData + 0x1c);
        *(float*)(dataPtr + 0xd8) = *(float*)(templateData + 0x20);
        *(float*)(dataPtr + 0xdc) = *(float*)(templateData + 0x24);
        *(float*)(dataPtr + 0xe0) = *(float*)(templateData + 0x28);
        *(float*)(dataPtr + 0xe4) = *(float*)(templateData + 0x2c);
        *(int*)(dataPtr + 0xe8) = (int)*(short*)(templateData + 0x30); // +0xe8: short
        *(float*)(dataPtr + 0xec) = *(float*)(templateData + 0x34);
        *(float*)(dataPtr + 0xf0) = *(float*)(templateData + 0x38);
        *(float*)(dataPtr + 0xf4) = *(float*)(templateData + 0x3c);
        *(float*)(dataPtr + 0xf8) = *(float*)(templateData + 0x40);
        *(float*)(dataPtr + 0xfc) = *(float*)(templateData + 0x44);
        *(float*)(dataPtr + 0x100) = *(float*)(templateData + 0x48);
        *(int*)(dataPtr + 0x10c) = *(int*)(templateData + 0x4c);   // +0x10c: int
        *(int*)(dataPtr + 0x110) = *(int*)(templateData + 0x50);   // +0x110: int
        *(int*)(dataPtr + 0x114) = *(int*)(templateData + 0x54);   // +0x114: int
        *(int*)(dataPtr + 0x120) = (int)*(short*)(templateData + 0x58); // +0x120: short
        *(short*)(dataPtr + 0x108) = *(short*)(templateData + 0x5c); // +0x108: short
        return;
    }

    // No template found: use default values from this object
    *(int*)(dataPtr + 0x20) = thisPtr; // +0x20: pointer to owner
    *(int*)(dataPtr + 0x24) = (int)&LAB_00672a40; // +0x24: default function pointer (vtable?)
    *(float*)(dataPtr + 0x40) = *(float*)(thisPtr + 0x2c); // +0x40: copy from this
    *(float*)(dataPtr + 0x44) = *(float*)(thisPtr + 0x30); // +0x44: copy from this
    FUN_00672b00(resourceHandle, templateId, isTemplate, outError); // fallback initialization
    if (*outError == 0) {
        // Clear default values if initialization succeeded
        int dataPtr = *outData;
        *(int*)(dataPtr + 0x20) = 0;
        *(int*)(dataPtr + 0x24) = 0;
        *(int*)(dataPtr + 0x40) = 0;
        *(int*)(dataPtr + 0x44) = 0;
    }
}