// FUNC_NAME: Vector4::addXyz
void __fastcall Vector4::addXyz(Vector4* this, const Vector4* a, const Vector4* b)
{
    // Save this w before overwriting
    float originalW = this->w;

    // Add all four components as a full add
    this->x = a->x + b->x;
    this->y = a->y + b->y;
    this->z = a->z + b->z;
    this->w = a->w + b->w;

    // Restore original w – effectively only xyz are added
    this->w = originalW;
}