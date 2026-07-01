// FUNC_NAME: Entity::updatePositionFromAnimation
void __fastcall Entity::updatePositionFromAnimation(int this)
{
  int animData;
  float *pfVar2;
  
  animData = FUN_0043d0d0(this + 0x20, 0x8a259734, 0xffffffff); // Get animation data from +0x20
  if (animData != 0) {
    pfVar2 = (float *)FUN_0043d590(); // Get current animation frame position
    if (pfVar2 != (float *)0x0) {
      *(float *)(this + 0x7c) = *pfVar2 + DAT_01205228; // +0x7c: position X
      *(float *)(this + 0x80) = pfVar2[1]; // +0x80: position Y
    }
  }
  return;
}