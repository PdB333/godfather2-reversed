// FUNC_NAME: Entity::applyImpulseTransformed
void __thiscall Entity::applyImpulseTransformed(int this, int sourceEntity)
{
  float scaleFactor;
  
  scaleFactor = DAT_00e53694;
  if (*(float *)(this + 0xf8) < DAT_00e5369c) {
    scaleFactor = (DAT_00e53694 - DAT_00e53698) * (*(float *)(this + 0xf8) / DAT_00e5369c) +
            DAT_00e53698;
  }
  scaleFactor = scaleFactor / _DAT_00e536a0;
  
  // +0x380 = linear impulse X, +0x1d0 = source impulse X
  *(float *)(this + 0x380) = *(float *)(sourceEntity + 0x1d0) * scaleFactor;
  // +0x384 = linear impulse Y? (offset 900 = 0x384)
  *(float *)(this + 900) = *(float *)(sourceEntity + 0x1d4) * scaleFactor;
  // +0x388 = linear impulse Z
  *(float *)(this + 0x388) = *(float *)(sourceEntity + 0x1d8) * scaleFactor;
  
  // +0x3b0 = angular impulse X, +0x1dc = source angular impulse X
  *(float *)(this + 0x3b0) = *(float *)(sourceEntity + 0x1dc) * scaleFactor;
  // +0x3b4 = angular impulse Y, +0x1e0 = source angular impulse Y
  *(float *)(this + 0x3b4) = *(float *)(sourceEntity + 0x1e0) * scaleFactor;
  // +0x3b8 = angular impulse Z, +0x1e4 = source angular impulse Z
  *(float *)(this + 0x3b8) = *(float *)(sourceEntity + 0x1e4) * scaleFactor;
  
  // +0x3e0 = extra impulse 1? (0x3e0), source +0x1e8
  *(float *)(this + 0x3e0) = *(float *)(sourceEntity + 0x1e8) * scaleFactor;
  // +0x3e4 = extra impulse 2? (0x3e4), source +0x1ec
  *(float *)(this + 0x3e4) = *(float *)(sourceEntity + 0x1ec) * scaleFactor;
  // +0x3e8 = extra impulse 3? (0x3e8 = 1000), source +0x1f0
  *(float *)(this + 1000) = *(float *)(sourceEntity + 0x1f0) * scaleFactor;
  
  // +0x410 = offset 0x410, source +0x1f4 (500)
  *(float *)(this + 0x410) = *(float *)(sourceEntity + 500) * scaleFactor;
  // +0x414 = offset 0x414, source +0x1f8
  *(float *)(this + 0x414) = *(float *)(sourceEntity + 0x1f8) * scaleFactor;
  // +0x418 = offset 0x418, source +0x1fc
  *(float *)(this + 0x418) = *(float *)(sourceEntity + 0x1fc) * scaleFactor;
  
  return;
}