// FUNC_NAME: FontManager::initialize
void FontManager::initialize(void)

{
  undefined4 *puVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  short *psVar7;
  short sVar8;
  byte *pbVar9;
  uint uVar10;
  
  // Clear font glyph index tables (0x400 bytes each) to -1
  _memset(g_fontGlyphIndexTable, -1, 0x400);
  g_fontDefaultChar = 0xff;                  // +0x? (global default character)
  g_fontSpaceChar = 0xff;                    // +0x?
  g_fontInitFlag = 0;                        // +0x?
  _memset(g_fontKernTable, -1, 0x400);       // kerning table
  _memset(g_fontData, 0, 0x8000);            // font bitmap data

  // Get font manager instance from singleton factory
  g_fontManagerInstance = (undefined8 *)(**(code **)*g_singletonFactory)();
  puVar1 = g_singletonFactory;
  *g_fontManagerInstance = 0;
  g_fontManagerInstance[1] = 0;
  g_fontManagerInstance[2] = 0;
  g_fontManagerInstance[3] = 0;
  *(undefined4 *)(g_fontManagerInstance + 4) = 0;
  *(undefined4 *)((int)g_fontManagerInstance + 4) = 4;  // sets version to 4

  // Allocate font memory pool
  iVar3 = (**(code **)*puVar1)();
  *(int *)(iVar3 + 8) = iVar3;               // self-pointer
  *(undefined4 *)(iVar3 + 4) = 0x100000;      // pool size 1MB
  *(undefined1 *)(iVar3 + 0xc) = 1;           // pool flags?

  // Attempt to allocate font texture memory
  iVar4 = (**(code **)(*g_memoryManager + 0x68))(g_memoryManager, 0x100000, 0x208);
  if ((iVar4 != 0) && (iVar4 == -0x7789fe84)) {
    (*(code *)g_errorHandler)(2);              // fatal error on allocation failure
  }

  g_fontCurrentBuffer = 0;                    // current glyph buffer index
  g_fontMemoryPool = iVar3;                   // +0x40 global

  // Create font descriptor object
  puVar5 = (undefined4 *)(**(code **)*g_singletonFactory)(0x20, &stack0xffffffbc);
  puVar5[1] = puVar5;                         // self-pointer
  puVar5[3] = 0x600;                          // vertex count
  puVar1 = puVar5 + 5;                        // +0x14: vertex buffer pointer
  *puVar1 = 0;
  *(undefined1 *)(puVar5 + 2) = 0;            // flags byte
  *(undefined2 *)(puVar5 + 4) = 0;            // ?
  *(undefined2 *)((int)puVar5 + 0x12) = 0;    // ?

  // Allocate font vertex buffer (0xC00 bytes = 0x600 vertices * 6? Actually 0xC00->size)
  iVar3 = (**(code **)(*g_memoryManager + 0x6c))(g_memoryManager, 0xc00, 8, 0x65, 1, puVar5, 0);
  if ((iVar3 != 0) && (iVar3 == -0x7789fe84)) {
    (*(code *)g_errorHandler)(2);
  }

  uVar6 = 0;
  if (*(char *)(puVar5 + 2) != '\0') {
    uVar6 = 0x3000;                           // flags for no shredding?
  }
  g_fontDescriptor = puVar5;                  // +0x48 global

  // Initialize vertex buffer (vtable call)
  (**(code **)(*(int *)*puVar5 + 0x2c))((int *)*puVar5, 0, 0, puVar1, uVar6);

  // Fill index buffer with triangle indices for a full screen quad strip
  psVar7 = (short *)*puVar1;                  // vertex buffer data
  psVar2 = psVar7 + 0x600;                    // end pointer (0x600 shorts)
  if (psVar7 < psVar2) {
    sVar8 = 2;
    do {
      *psVar7 = sVar8 + -2;                  // vertex 0
      psVar7[1] = sVar8 + -1;                // vertex 1
      psVar7[2] = sVar8;                     // vertex 2
      psVar7[3] = sVar8 + -2;                // first triangle repeat
      psVar7[4] = sVar8;                     // vertex for second triangle
      psVar7[5] = sVar8 + 1;                 // vertex 3
      psVar7 = psVar7 + 6;                   // advance by 6 shorts (one quad)
      sVar8 = sVar8 + 4;                     // next set of 4 vertices
    } while (psVar7 < psVar2);
  }

  puVar1 = g_fontDescriptor;
  FUN_0060be40();                             // unknown font-related init
  (**(code **)(*(int *)*puVar1 + 0x30))((int *)*puVar1); // commit changes

  // Validate cached glyph bitmaps (each 0xC bytes)
  uVar10 = 0;
  if (g_fontGlyphCount != 0) {
    pbVar9 = &g_fontGlyphArray;               // starts at byte array
    do {
      if (0x80 < *pbVar9) {                   // check if glyph byte > 128 (invalid?)
        FUN_00609bf0();                       // reload or reset font
        return;
      }
      uVar10 = uVar10 + 1;
      pbVar9 = pbVar9 + 0xc;                  // each glyph entry 12 bytes
    } while (uVar10 < g_fontGlyphCount);
  }

  // If there's room, add a new glyph entry (for space character?)
  if (g_fontGlyphCount < 0x20) {
    iVar3 = g_fontGlyphCount * 0xc;
    // Write two function pointers (0x00609e20, 0x00609e40) – likely render callbacks
    *(undefined8 *)(&g_fontGlyphTableBase + g_fontGlyphCount * 3) = 0x609e4000609e20;
    // Set glyph metric byte to 0x80 combined with flags from uVar6
    *(uint *)(&g_fontGlyphArray + iVar3) = CONCAT31((int3)((uint)uVar6 >> 8), 0x80);
    g_fontGlyphCount = g_fontGlyphCount + 1;
  }
  return;
}