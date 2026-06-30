// FUNC_NAME: AnimationPoseBuilder::buildPoseFromTemplate
void __thiscall AnimationPoseBuilder::buildPoseFromTemplate(void* thisPointer, int templateData, int** outPosePtr, int fallbackData, uint flags, int* outResult)
{
    byte stateByte;          // +0x1c in thisPointer
    int* destPose;           // output pose structure
    void* templateStruct;    // pointer to template data if found
    int extraECX;            // leftover from inlining (original ECX register value)

    stateByte = *(byte*)((int)thisPointer + 0x1c);
    destPose = *outPosePtr;  // outPosePtr points to a pointer to the destination pose structure
    templateStruct = getTemplateData();  // FUN_00672a80: returns pointer to template or 0

    if (templateStruct != 0) {
        // If flags bit 2 is set, initialize from default data
        if ((flags & 4) != 0) {
            initializeFromDefault(fallbackData, 0, 0, outResult);  // FUN_00674d40
        } else {
            *outResult = 0;
        }

        // Check template's left/right child pointers (+0x4c, +0x50)
        if ((*(int*)((int)templateStruct + 0x50) == 0) && (*(int*)((int)templateStruct + 0x4c) == 0)) {
            // No children – clear both
            *(int*)(destPose + 0x11c) = 0;
            *(int*)(destPose + 0x118) = 0;
        } else if (*(short*)((int)templateStruct + 0x5a) == 1) {
            // Right child active? – store right pointer
            *(int*)(destPose + 0x11c) = (int)templateStruct + 0x68;
        } else {
            // Left child active – store left pointer
            *(int*)(destPose + 0x118) = (int)templateStruct + 0x68;
        }

        // Copy transformation data from template to destPose
        // Offsets: template +0x14..0x5c mapped to dest +0xcc..0x120
        *(int*)(destPose + 0x30) = 0;
        *(int*)(destPose + 0xcc) = *(short*)((int)templateStruct + 0x14);
        *(int*)(destPose + 0xd0) = *(int*)((int)templateStruct + 0x18);
        *(int*)(destPose + 0xd4) = *(int*)((int)templateStruct + 0x1c);
        *(int*)(destPose + 0xd8) = *(int*)((int)templateStruct + 0x20);
        *(int*)(destPose + 0xdc) = *(int*)((int)templateStruct + 0x24);
        *(int*)(destPose + 0xe0) = *(int*)((int)templateStruct + 0x28);
        *(int*)(destPose + 0xe4) = *(int*)((int)templateStruct + 0x2c);
        *(int*)(destPose + 0xe8) = *(short*)((int)templateStruct + 0x30);
        *(int*)(destPose + 0xec) = *(int*)((int)templateStruct + 0x34);
        *(int*)(destPose + 0xf0) = *(int*)((int)templateStruct + 0x38);
        *(int*)(destPose + 0xf4) = *(int*)((int)templateStruct + 0x3c);
        *(int*)(destPose + 0xf8) = *(int*)((int)templateStruct + 0x40);
        *(int*)(destPose + 0xfc) = *(int*)((int)templateStruct + 0x44);
        *(int*)(destPose + 0x100) = *(int*)((int)templateStruct + 0x48);
        *(int*)(destPose + 0x10c) = *(int*)((int)templateStruct + 0x4c);
        *(int*)(destPose + 0x110) = *(int*)((int)templateStruct + 0x50);
        *(int*)(destPose + 0x114) = *(int*)((int)templateStruct + 0x54);
        *(int*)(destPose + 0x120) = *(short*)((int)templateStruct + 0x58);
        *(short*)(destPose + 0x108) = *(short*)((int)templateStruct + 0x5c);
        return;
    }

    // Fallback: no template found – use provided data and reinitialize
    // extraECX is the value of ECX after the call to getTemplateData (inlined variable)
    *(int*)(destPose + 0x20) = extraECX;                        // likely current pose buffer or entity pointer
    *(int**)(destPose + 0x24) = &LAB_00672a40;                 // function pointer / jump table
    *(int*)(destPose + 0x40) = *(int*)(extraECX + 0x2c);       // copy two fields from some source
    *(int*)(destPose + 0x44) = *(int*)(extraECX + 0x30);
    initializeFromFallback(fallbackData, templateData, stateByte, outResult); // FUN_00672b00
    if (*outResult == 0) {
        destPose = *outPosePtr;  // re-read (pointer might have been changed by initializeFromFallback?)
        *(int*)(destPose + 0x20) = 0;
        *(int*)(destPose + 0x24) = 0;
        *(int*)(destPose + 0x40) = 0;
        *(int*)(destPose + 0x44) = 0;
    }
}