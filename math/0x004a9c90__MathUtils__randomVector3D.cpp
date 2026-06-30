// FUNC_NAME: MathUtils::randomVector3D
void MathUtils::randomVector3D(void* unused, float* outVec)
{
    // Global scale factor for random range (likely from config)
    float scale = DAT_00e445e4;

    for (uint i = 0; i < 3; ++i)
    {
        // FUN_0064be80 returns a random int (probably [0, RAND_MAX])
        int r = Random::getInt();  // 0x0064be80
        outVec[i] = (float)r * scale;
    }
}