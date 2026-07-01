// FUNC_NAME: Entity::initFromData
undefined4 * __thiscall Entity::initFromData(undefined4 *this, int data, undefined4 param_3)
{
  uint hash;
  uint i;
  
  FUN_008cee80(data, param_3);
  i = 0;
  *this = &PTR_FUN_00d75318; // vtable
  *(undefined1 *)(this + 0x10) = 0; // +0x10 flags byte
  this[0x11] = 0; // +0x44
  if (*(short *)(data + 0x20) != 0) { // data->componentCount
    do {
      hash = *(uint *)(*(int *)(*(int *)(data + 0x1c) + i * 4) + 0x10); // component type hash
      if (hash < 0x92ba7053) {
        if (hash == 0x92ba7052) { // e.g. "RenderComponent"
          *(byte *)(this + 0x10) = *(byte *)(this + 0x10) | 1; // flag bit 0
        }
        else if (hash == 0x3caa702f) { // e.g. "PhysicsComponent"
          *(byte *)(this + 0x10) = *(byte *)(this + 0x10) | 4; // flag bit 2
        }
        else if (hash == 0x8101d11f) { // e.g. "AudioComponent"
          *(byte *)(this + 0x10) = *(byte *)(this + 0x10) | 2; // flag bit 1
        }
      }
      else if (hash == 0xeb8f328b) { // e.g. "AnimationComponent"
        *(byte *)(this + 0x10) = *(byte *)(this + 0x10) | 8; // flag bit 3
      }
      i = i + 1;
    } while (i < *(ushort *)(data + 0x20));
  }
  return this;
}