// FUNC_NAME: EARSObject::clearTransform
void __fastcall EARSObject::clearTransform(int this)
{
  // +0x10: position.x, +0x14: position.y, +0x18: position.z
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x14) = 0;
  *(undefined4 *)(this + 0x10) = 0;
  // +0x1c: position.w (or padding)
  *(undefined4 *)(this + 0x1c) = DAT_00e2b1a4; // likely identity quaternion w component (1.0f)
  
  // +0x20: rotation.x, +0x24: rotation.y, +0x28: rotation.z
  *(undefined4 *)(this + 0x28) = 0;
  *(undefined4 *)(this + 0x24) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  // +0x2c: rotation.w
  *(undefined4 *)(this + 0x2c) = DAT_00e2b1a4; // identity quaternion w = 1.0f
  
  // +0x30: scale (4 bytes, likely float)
  *(undefined1 *)(this + 0x30) = 0;
  *(undefined1 *)(this + 0x31) = 0;
  *(undefined1 *)(this + 0x32) = 0;
  *(undefined1 *)(this + 0x33) = 0;
  
  // +0x34-0x44: possibly matrix or additional transform data
  *(undefined4 *)(this + 0x34) = 0;
  *(undefined4 *)(this + 0x38) = 0;
  *(undefined4 *)(this + 0x3c) = 0;
  *(undefined4 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0x44) = 0;
}