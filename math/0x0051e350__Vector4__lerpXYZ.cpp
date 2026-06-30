// FUNC_NAME: Vector4::lerpXYZ
void __fastcall Vector4::lerpXYZ(const Vector4* a, const Vector4* b, float t)
{
    float originalW = this->w;
	
    // Linear interpolation of xyz components: result = t * a + b
    this->x = t * a->x + b->x;
    this->y = t * a->y + b->y;
    this->z = t * a->z + b->z;
	
    // Preserve the original w component (not interpolated)
    this->w = originalW;
}