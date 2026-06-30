// FUNC_NAME: UIElement::UIElement
void __fastcall UIElement::UIElement(UIElement *this)
{
  // +0x00: vtable pointer
  this->vtable = (void **)&PTR_UIElementVTable;
  
  // +0x0C: initially set to 0xFF, later overwritten to 0x100 (count/flag)
  this->field_0C = 0xFF;
  
  // +0x04: flags/state
  this->field_04 = 0;
  
  // +0x08: byte flag (maybe enabled)
  *(uint8 *)&this->field_08 = 0;
  
  // Load global constants
  float defaultX = DAT_00d5e288;  // Maybe 0.0f
  float defaultY = DAT_00d5efd0;  // Maybe 0.0f
  float defaultZ = DAT_00e446dc;  // Maybe 1.0f
  float screenW  = DAT_00d5f5f0;  // Screen width
  float screenH  = DAT_00d5f5f4;  // Screen height
  float alpha    = _DAT_00d5780c; // Global alpha/value
  
  // Region 1 (viewport rectangle) at +0x50
  this->region[0].minX = defaultX;  // +0x50
  this->region[0].minY = defaultY;  // +0x54
  this->region[0].maxX = defaultX;  // +0x58
  this->region[0].maxY = defaultY;  // +0x5C
  this->region[0].color = alpha;    // +0x60

  // Sub-region inside region1 at +0x64
  this->region[0].subMinX = defaultX;  // +0x64
  this->region[0].subMinY = defaultZ;  // +0x68
  this->region[0].subMaxX = alpha;     // +0x6C
  this->region[0].subMaxY = alpha;     // +0x70

  // Primary region UV/texture coordinates at +0x74
  this->region[0].uv[0].u = screenW;  // +0x74
  this->region[0].uv[0].v = screenH;  // +0x78

  // Sub-region UV at +0x7C
  this->region[0].uv[1].u = screenW;  // +0x7C
  this->region[0].uv[1].v = screenH;  // +0x80

  // Region 2 (second viewport) at +0xB4
  this->region[1].minX = defaultX;  // +0xB4
  this->region[1].minY = defaultY;  // +0xB8
  this->region[1].maxX = defaultX;  // +0xBC
  this->region[1].maxY = defaultY;  // +0xC0
  this->region[1].color = alpha;    // +0xC4

  this->region[1].subMinX = defaultX;  // +0xC8
  this->region[1].subMinY = defaultZ;  // +0xCC
  this->region[1].subMaxX = alpha;     // +0xD0
  this->region[1].subMaxY = alpha;     // +0xD4

  this->region[1].uv[0].u = screenW;  // +0xD8
  this->region[1].uv[0].v = screenH;  // +0xDC

  this->region[1].uv[1].u = screenW;  // +0xE0
  this->region[1].uv[1].v = screenH;  // +0xE4

  // Zero out padding and flags for regions 1-4
  // Offset +0xD8 to +0xF0: 0
  this->field_D8 = 0;
  this->field_DC = 0;
  this->field_E0 = 0;
  this->field_E4 = 0;
  this->field_E8 = 0;
  this->field_EC = 0;
  this->field_F0 = 0;
  *(uint8 *)&this->field_F4 = 0; // byte at +0x100

  // Region 3 placeholder (same layout as region1)
  this->region[2].minX = defaultX;
  this->region[2].minY = defaultY;

  // Zero out region 3 padding
  this->region[2].pad_104 = 0;
  this->region[2].pad_108 = 0;
  this->region[2].pad_10C = 0;
  this->region[2].pad_110 = 0;
  this->region[2].pad_114 = 0;
  this->region[2].pad_118 = 0;
  this->region[2].pad_11C = 0;
  this->region[2].pad_120 = 0;

  *(uint8 *)&this->region[2].flag_B4 = 0; // byte at +0x130

  this->region[2].subMinX = defaultX;
  this->region[2].subMinY = defaultY;

  // Zero out region 4 padding
  this->region[3].pad_134 = 0;
  this->region[3].pad_138 = 0;
  this->region[3].pad_13C = 0;
  this->region[3].pad_140 = 0;
  this->region[3].pad_144 = 0;
  this->region[3].pad_148 = 0;
  this->region[3].pad_14C = 0;
  this->region[3].pad_150 = 0;

  *(uint8 *)&this->region[3].flag_B4 = 0; // byte at +0x160

  this->region[3].subMinX = defaultX;
  this->region[3].subMinY = defaultY;

  // Zero out region 5 padding
  this->region[4].pad_164 = 0;
  this->region[4].pad_168 = 0;
  this->region[4].pad_16C = 0;
  this->region[4].pad_170 = 0;
  this->region[4].pad_174 = 0;
  this->region[4].pad_178 = 0;
  this->region[4].pad_17C = 0;
  this->region[4].pad_180 = 0;

  *(uint8 *)&this->region[4].flag_B4 = 1; // byte at +0x1A0 (enabled)
  this->region[4].pad_184 = 0;
  this->region[4].pad_188 = 0;
  this->region[4].pad_18C = 0;
  this->region[4].pad_190 = 0;

  // Final override: set +0x0C to 0x100 (perhaps total region count or size)
  this->field_0C = 0x100;

  return;
}