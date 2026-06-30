// FUNC_NAME: Renderer::initializeDefaultSettings
undefined * Renderer::initializeDefaultSettings(void)

{
  // Global renderer settings structure at 0x01219028
  _DAT_01219038 = 0;          // +0x10: some integer flag (e.g., bEnableVSync)
  _DAT_0121903c = 0;          // +0x14: another flag (e.g., bEnableTripleBuffering)
  _DAT_01219044 = 0;          // +0x1C: resolution width (set to 0 initially)
  _DAT_01219048 = 0;          // +0x20: resolution height (set to 0 initially)
  _DAT_0121904c = 0;          // +0x24: color depth (set to 0 initially)
  _DAT_0121902c = &DAT_00e3792c;  // +0x04: pointer to a default renderer config string (e.g., "Default")
  _DAT_01219030 = 0x2e766665; // +0x08: magic value "eff." (little-endian) - possibly a version/fourCC
  _DAT_01219034 = 1;          // +0x0C: some boolean (e.g., bEnableHardwareTnL)
  _DAT_01219040 = 0x800;      // +0x18: back buffer count (2048? or 0x800 = 2048, likely max texture size)
  _DAT_01219028 = &PTR_LAB_00e37988; // +0x00: pointer to a vtable or function table for renderer
  return &DAT_01219028;       // returns pointer to the settings structure
}