// FUNC_NAME: GameObject::calcDistanceTo

void __thiscall GameObject::calcDistanceTo(GameObject *this, GameObject *target)
{
    // this position at offsets: x=0x180, y=0x184, z=0x188
    // target position at offsets: x=0x70, y=0x74, z=0x78
    float dx = *(float*)((uint8_t*)this + 0x180) - *(float*)((uint8_t*)target + 0x70);
    float dy = *(float*)((uint8_t*)this + 0x184) - *(float*)((uint8_t*)target + 0x74);
    float dz = *(float*)((uint8_t*)this + 0x188) - *(float*)((uint8_t*)target + 0x78);

    // Store distance at offset 0x194 and mark as valid at offset 0x198
    *(float*)((uint8_t*)this + 0x194) = sqrt(dx*dx + dy*dy + dz*dz);
    *(int*)((uint8_t*)this + 0x198) = 1;
}