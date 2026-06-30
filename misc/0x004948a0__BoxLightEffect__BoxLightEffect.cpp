// FUNC_NAME: BoxLightEffect::BoxLightEffect
void __thiscall BoxLightEffect::BoxLightEffect(void *this)
{
  // Store pointer to self at offset +0x2d0 (possibly for later use or vtable)
  *(int *)((char *)this + 0x2d0) = (int)this;

  // Acquire a shader/effect object from a global manager (PTR_DAT_0110a18c)
  *(int *)((char *)this + 0x14) = FUN_0060a2e0(&PTR_DAT_0110a18c);

  // Perform global initialization (likely loading default shader state)
  FUN_004907a0();

  // Retrieve handle for shader constant "g_boxLightInvMtx" (inverse view matrix for box light)
  *(int *)((char *)this + 0x2d4) = FUN_0060a580(
      *(int *)((char *)this + 0x14),  // shader object
      "g_boxLightInvMtx");

  // Retrieve handle for "g_boxLightFBScale" (framebuffer scale factor for box light)
  *(int *)((char *)this + 0x320) = FUN_0060a580(
      *(int *)((char *)this + 0x14),
      "g_boxLightFBScale");

  // Retrieve handle for "g_boxLightFBOffset" (framebuffer offset for box light)
  *(int *)((char *)this + 0x340) = FUN_0060a580(
      *(int *)((char *)this + 0x14),
      "g_boxLightFBOffset");

  // Additional initialization (possibly setting remaining defaults)
  FUN_004923e0();
}