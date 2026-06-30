// FUNC_NAME: EARS::Framework::SceneNode::updateWorldTransform

void __fastcall SceneNode::updateWorldTransform()
{
    // Call reset or init function (e.g., clear temporary data)
    FUN_00612a60(); // placeholder: possibly sets identity matrix or clears stack

    // Combine first local transform component (rotation?) from stored offsets
    // Offsets: 0xBC, 0xC4, 0xC0 correspond to x, z, y storage order? 
    // Build a 4D vector (x, y, z, w) with w = 0
    Vector4 tempVec;
    tempVec.x = *(float*)(this + 0xBC); // x component (from +0xBC)
    tempVec.y = *(float*)(this + 0xC4); // y component (from +0xC4)
    tempVec.z = *(float*)(this + 0xC0); // z component (from +0xC0)
    tempVec.w = 0.0f;

    // Apply parent transform (at +0x10) with local transform component (at +0xA4)
    // Result stored in tempVec
    FUN_0060add0(*(void**)(this + 0x10), *(void**)(this + 0xA4), &tempVec);

    // Second local transform component (possibly scale or another rotation)
    tempVec.x = *(float*)(this + 0xD0);
    tempVec.y = *(float*)(this + 0xD4);
    tempVec.z = *(float*)(this + 0xD8);
    tempVec.w = 0.0f;

    FUN_0060add0(*(void**)(this + 0x10), *(void**)(this + 0xA8), &tempVec);

    // Release/delete any existing transform objects if present
    if (*(int*)(this + 0xAC) != 0) {
        FUN_006063b0(); // likely free or release memory
    }
    if (*(int*)(this + 0xB0) != 0) {
        FUN_006063b0();
    }

    // Third transform combination (position?)
    tempVec.x = *(float*)(this + 200); // offset 0xC8
    tempVec.y = 0.0f;
    tempVec.z = 0.0f;
    tempVec.w = 0.0f;

    FUN_0060add0(*(void**)(this + 0x14), *(void**)(this + 0xB4), &tempVec);

    // Final world transform matrix write to offset 0xF0
    FUN_0060b020(*(void**)(this + 0x10), *(void**)(this + 0xB8), (void*)(this + 0xF0));

    return;
}