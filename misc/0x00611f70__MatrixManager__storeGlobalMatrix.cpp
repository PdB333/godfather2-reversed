// FUNC_NAME: MatrixManager::storeGlobalMatrix

void MatrixManager::storeGlobalMatrix(const float (*source)[4]) // source is a pointer passed in ESI
{
    // Copy a 4x4 matrix (16 floats) from source to global storage
    // Global addresses 0x011f67f0 through 0x011f682c
    _DAT_011f67f0 = *reinterpret_cast<const int*>(source);
    _DAT_011f67f4 = reinterpret_cast<const int*>(source)[1];
    _DAT_011f67f8 = reinterpret_cast<const int*>(source)[2];
    _DAT_011f67fc = reinterpret_cast<const int*>(source)[3];
    _DAT_011f6800 = reinterpret_cast<const int*>(source)[4];
    _DAT_011f6804 = reinterpret_cast<const int*>(source)[5];
    _DAT_011f6808 = reinterpret_cast<const int*>(source)[6];
    _DAT_011f680c = reinterpret_cast<const int*>(source)[7];
    _DAT_011f6810 = reinterpret_cast<const int*>(source)[8];
    _DAT_011f6814 = reinterpret_cast<const int*>(source)[9];
    _DAT_011f6818 = reinterpret_cast<const int*>(source)[10];
    _DAT_011f681c = reinterpret_cast<const int*>(source)[11];
    _DAT_011f6820 = reinterpret_cast<const int*>(source)[12];
    _DAT_011f6824 = reinterpret_cast<const int*>(source)[13];
    _DAT_011f6828 = reinterpret_cast<const int*>(source)[14];
    _DAT_011f682c = reinterpret_cast<const int*>(source)[15];

    // If the global render device pointer exists, update related resources
    if (gRenderDevice != nullptr) // DAT_012058e8
    {
        // +0x28 likely a texture or shader handle
        if (*(int*)(gRenderDevice + 0x28) != 0)
        {
            // FUN_0060b020: likely setTexture(device, handle)
            setTexture(*(int*)(gRenderDevice + 0x10), *(int*)(gRenderDevice + 0x28));
        }
        // +0x2c another resource (e.g., shadow map)
        if (gRenderDevice != nullptr && *(int*)(gRenderDevice + 0x2c) != 0)
        {
            // FUN_0060aea0: likely setShadowMap(device, handle)
            setShadowMap(*(int*)(gRenderDevice + 0x10), *(int*)(gRenderDevice + 0x2c));
        }
    }
}