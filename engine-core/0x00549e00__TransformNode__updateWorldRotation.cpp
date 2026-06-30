// FUNC_NAME: TransformNode::updateWorldRotation
void __thiscall TransformNode::updateWorldRotation(void)
{
    // local variables
    char rotationBuffer[12];           // buffer for virtual function output
    float quatX, quatY, quatZ;        // components read from stack after virtual call
    float identityW = 1.0f;           // constant from DAT_00e2b1a4 (likely identity quaternion w)
    char transformBuffer[12];         // buffer for second initialization

    // call virtual function at vtable+0x90 from the sub-object at offset 0x10c
    // this function likely extracts the rotation from the parent transform at this+0x110
    // and writes three floats into rotationBuffer
    (*(void (__thiscall**)(void*, char*, void*, int))(*((int*)this + 0x10c) + 0x90))
        (this, rotationBuffer, (void*)((int)this + 0x110), 1);

    // copy the extracted rotation components into the object's rotation quaternion fields
    // offsets 0x40,0x44,0x48 are x,y,z; offset 0x4c is w (set to identity)
    *(float*)((int)this + 0x40) = quatX;
    *(float*)((int)this + 0x44) = quatY;
    *(float*)((int)this + 0x48) = quatZ;
    *(float*)((int)this + 0x4c) = identityW;

    // initialize the sub-object at offset 0x10 from a copy of the parent transform?
    // FUN_004b59d0 likely copies transform data from this+0x10 into transformBuffer
    FUN_004b59d0(transformBuffer, (void*)((int)this + 0x10));
}