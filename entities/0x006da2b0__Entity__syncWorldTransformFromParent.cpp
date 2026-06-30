// FUNC_NAME: Entity::syncWorldTransformFromParent
void __fastcall Entity::syncWorldTransformFromParent(Entity* this) // param_1 = this
{
    int* parentField = (int*)((int)this + 0x10); // +0x10: parent pointer (or attachment pointer)
    if (*parentField != 0 && *parentField != 0x48) {
        int basePtr;
        if (*parentField == 0) {
            basePtr = 0;
        } else {
            basePtr = *parentField - 0x48; // subtract offset to get parent object base
        }
        // Copy 48 bytes (likely a 4x3 affine matrix) from parent transform to this transform
        *(int64_t*)((int)this + 0x20) = *(int64_t*)(basePtr + 0x60); // +0x20: own world transform
        *(int64_t*)((int)this + 0x28) = *(int64_t*)(basePtr + 0x68);
        *(int64_t*)((int)this + 0x30) = *(int64_t*)(basePtr + 0x70);
        *(int64_t*)((int)this + 0x38) = *(int64_t*)(basePtr + 0x78);
        *(int64_t*)((int)this + 0x40) = *(int64_t*)(basePtr + 0x80);
        *(int64_t*)((int)this + 0x48) = *(int64_t*)(basePtr + 0x88); // +0x48: end of transform (12 floats)
    }
}