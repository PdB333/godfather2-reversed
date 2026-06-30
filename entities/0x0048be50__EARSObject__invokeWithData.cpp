// FUNC_NAME: EARSObject::invokeWithData
float __thiscall EARSObject::invokeWithData(float param2, float param3, float param4, float param5,
                                            float param6, float param7, float param8, float param9)
{
    // Calls a helper function (FUN_004883b0) with an extra argument: a pointer to the data at offset +0x1c.
    // The offset likely stores a vector, transform, or other game object state.
    void* extraData = reinterpret_cast<void*>(this + 0x1c);
    return FUN_004883b0(param2, param3, param4, param5, extraData, param6, param7, param8, param9);
}