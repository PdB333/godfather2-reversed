// FUNC_NAME: global_setColorData
void __fastcall setColorData(int* colorData)
{
  _DAT_01219b40 = colorData[0];
  _DAT_01219b44 = colorData[1];
  _DAT_01219b48 = colorData[2];
  _DAT_01219b4c = colorData[3];
  
  // Check if the first color palette is initialized and there's a valid palette entry for the current index
  if ((DAT_012058e8 == &DAT_01219a70) && (*(int*)(&DAT_01219cac + (uint)DAT_01219b20 * 0x30) != 0))
  {
    // Apply the color data to the palette entry
    FUN_0060add0(DAT_01219a80, *(int*)(&DAT_01219cac + (uint)DAT_01219b20 * 0x30), colorData);
  }
}