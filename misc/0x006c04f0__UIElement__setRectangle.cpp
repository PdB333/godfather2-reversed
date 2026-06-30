// FUNC_NAME: UIElement::setRectangle
void __thiscall UIElement::setRectangle(const uint32_t* rectValues)
{
  // Copies four 32-bit values from the input array to member fields at offsets 0x10-0x1c.
  // Likely stores rectangle coordinates (e.g., left, top, right, bottom) or a color (RGBA).
  this->rectLeftTopRightBottom[0] = rectValues[0]; // +0x10
  this->rectLeftTopRightBottom[1] = rectValues[1]; // +0x14
  this->rectLeftTopRightBottom[2] = rectValues[2]; // +0x18
  this->rectLeftTopRightBottom[3] = rectValues[3]; // +0x1c
}