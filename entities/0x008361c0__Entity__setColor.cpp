//FUNC_NAME: Entity::setColor
void __thiscall Entity::setColor(Entity *this, const float *rgba)
{
  // Copy 4 floats (RGBA) from source array to member at offset 0x20
  *(float *)((int)this + 0x20) = rgba[0];  // +0x20: r
  *(float *)((int)this + 0x24) = rgba[1];  // +0x24: g
  *(float *)((int)this + 0x28) = rgba[2];  // +0x28: b
  *(float *)((int)this + 0x2c) = rgba[3];  // +0x2c: a
}