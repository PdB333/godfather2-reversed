// FUNC_NAME: setGlobalColor
void setGlobalColor(uint32_t *color)
{
  DAT_0112dacc = color[0]; // +0x00: red
  DAT_0112dad0 = color[1]; // +0x04: green
  DAT_0112dad4 = color[2]; // +0x08: blue
  DAT_0112dad8 = color[3]; // +0x0C: alpha
  return;
}