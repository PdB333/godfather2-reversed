// FUNC_NAME: FontManager::processGlyphQuads
undefined4 __thiscall FontManager::processGlyphQuads(int *this, int destBuffer, int quadCount, float *scale /* [4]: rgba multiplier */)
{
  float fVar1;
  float srcX, srcY, srcZ, srcW;
  float scaleX, scaleY, scaleZ, scaleW;
  int pGlyphData;
  int extraout_EDX;
  float *pDst;
  
  // Virtual call: fetch glyph atlas data pointer (offset 0xc in vtable)
  // If null, return 0 (failure)
  pGlyphData = (*(code **)(*this + 0xc))();
  if (pGlyphData == 0) {
    return 0;
  }
  
  if (0 < quadCount) {
    // destination buffer starts at destBuffer + 0xc (likely to skip a header)
    pDst = (float *)(destBuffer + 0xc);
    // source data starts at glyphData + 0x10 (skip some header)
    pGlyphData = pGlyphData + 0x10;
    
    do {
      // Read 4 floats from source (position/texcoord/color component)
      srcX = *(float *)(pGlyphData - 0x10);  // offset -0x10
      srcY = *(float *)(pGlyphData - 0xc);   // offset -0xc
      srcZ = *(float *)(pGlyphData - 8);     // offset -8
      srcW = *(float *)(pGlyphData - 4);     // offset -4
      
      scaleX = scale[0];
      scaleY = scale[1];
      scaleZ = scale[2];
      scaleW = scale[3];
      
      // Multiply by scale and store to destination (offset -12, -8, -4, 0 relative to pDst)
      pDst[-3] = *(float *)(pGlyphData - 0x10) * scaleX;
      pDst[-2] = srcY * scaleY;
      pDst[-1] = srcZ * scaleZ;
      pDst[0]  = srcW * scaleW;  // overwritten below with packed color
      
      // Call helper to pack color (returns packed 32-bit color in EDX? see note)
      FUN_00414aa0();  // likely a color packing function
      
      // Write packed color (4 bytes) from extraout_EDX -4 to pDst (overwrites last float)
      *(undefined1 *)((int)pDst + 3) = *(undefined1 *)(extraout_EDX + -1);
      *(undefined2 *)pDst = *(undefined2 *)(extraout_EDX + -4);
      *(undefined1 *)((int)pDst + 2) = *(undefined1 *)(extraout_EDX + -2);
      
      // Advance source pointer (unusual: uses EDX as base)
      pGlyphData = extraout_EDX + 0x20;
      
      // Advance destination pointer by 8 floats (32 bytes per quad vertex)
      pDst = pDst + 8;
      
      quadCount = quadCount + -1;
    } while (quadCount != 0);
  }
  return 1;
}