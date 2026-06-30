// FUNC_NAME: EARS::Math::Vector3::Vector3
// Address: 0x00636c00 - Default constructor for Vector3 (initializes to zero via helper at 0x00636910)
void __thiscall EARS::Math::Vector3::Vector3(void)
{
    // Delegate to internal zero-initialization routine
    // The helper (0x00636910) sets all components (x, y, z) to 0.0f
    EARS::Math::Vector3::init(this);
}