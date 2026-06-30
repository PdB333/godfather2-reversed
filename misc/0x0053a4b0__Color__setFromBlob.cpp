// FUNC_NAME: Color::setFromBlob
void __thiscall Color::setFromBlob(undefined1 (*blob)[16])
{
  // +0x00: 16-byte color value (RGBA?)
  // _DAT_0121b930 and _DAT_0121b940 are two 16-byte globals representing color data
  // _DAT_0121b740 and related globals seem to be a rendering state manager

  if (blob == (undefined1 (*)[16])0x0) {
    // Clear color to black/zero if null blob
    _DAT_0121b930 = (undefined1 [16])0x0;
    _DAT_0121b940 = (undefined1 [16])0x0;
  }
  else {
    // Copy the 32-byte blob (two 16-byte chunks)
    _DAT_0121b930 = *blob;
    _DAT_0121b940 = blob[1];
  }

  // Check if we need to update the rendering state
  // DAT_012058e8 seems to be a current rendering state pointer
  // DAT_0121b740 appears to be a default/no-color state
  // DAT_0121b754 and DAT_0121bbcc are state IDs/indices
  if ((DAT_012058e8 == &DAT_0121b740) && (DAT_0121b754 == DAT_0121bbcc)) {
    // Update the rendering state with the new color data
    FUN_0060ab00(DAT_0121bbcc, DAT_0121bb8c, &DAT_0121b930, 8);
  }
}