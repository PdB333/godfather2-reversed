// FUNC_NAME: Vector4::scale
void Vector4::scale(float scalar)
{
  // +0x00: x, +0x04: y, +0x08: z, +0x0C: w
  this->x = scalar * this->x;
  this->y = scalar * this->y;
  this->z = scalar * this->z;
  this->w = scalar * this->w;
}