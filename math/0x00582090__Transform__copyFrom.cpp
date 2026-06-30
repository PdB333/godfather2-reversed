// FUNC_NAME: Transform::copyFrom
void Transform::copyFrom(const Transform& source)
{
    // Copy rotation (quaternion) at offset 0x10-0x1C
    *(int*)(this + 0x10) = *(int*)((int)&source + 0x10);
    *(int*)(this + 0x14) = *(int*)((int)&source + 0x14);
    *(int*)(this + 0x18) = *(int*)((int)&source + 0x18);
    *(int*)(this + 0x1C) = *(int*)((int)&source + 0x1C);
    // Copy translation (x,y,z) at offset 0x20-0x28
    *(int*)(this + 0x20) = *(int*)((int)&source + 0x20);
    *(int*)(this + 0x24) = *(int*)((int)&source + 0x24);
    *(int*)(this + 0x28) = *(int*)((int)&source + 0x28);
    // Copy scale at offset 0x2C
    *(int*)(this + 0x2C) = *(int*)((int)&source + 0x2C);
    // Copy update flag at offset 0x30
    *(byte*)(this + 0x30) = *(byte*)((int)&source + 0x30);
    // Copy handle/resource pointer at offset 0x60
    *(int*)(this + 0x60) = *(int*)((int)&source + 0x60);
    // Acquire reference on shared data pointed by source's offset 0x64
    acquireReference(*(void**)((int)&source + 0x64)); // FUN_00591cb0
    // Copy the reference pointer itself at offset 0x68
    *(int*)(this + 0x68) = *(int*)((int)&source + 0x68);
}