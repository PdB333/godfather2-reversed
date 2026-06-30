// Xbox PDB: SM_AptPrimTexturedInColorClass::LoadParamsVsShader
// FUNC_NAME: ShaderEffect::cacheUniformHandles

void __thiscall ShaderEffect::cacheUniformHandles(void *this) {
    // Get the shader program object handle from a field located 0x110 bytes before 'this'.
    // This suggests that 'this' may be a sub-object or a pointer into a larger structure.
    int shaderProgram = *(int *)((char *)this - 0x110);

    // Retrieve uniform location handles by name and cache them at various offsets.
    // The offsets are relative to 'this' and represent fields in the shader parameter block.

    // +100 (decimal) -> inColorMul uniform
    *(int *)((char *)this + 100) = getUniformByName(shaderProgram, "inColorMul");

    // +0x60 -> inColorAdd uniform
    *(int *)((char *)this + 0x60) = getUniformByName(shaderProgram, "inColorAdd");

    // -0x78 -> transU uniform
    *(int *)((char *)this - 0x78) = getUniformByName(shaderProgram, "transU");

    // -0x74 -> transV uniform
    *(int *)((char *)this - 0x74) = getUniformByName(shaderProgram, "transV");

    // -0xd0 -> ModelViewProj uniform (matrix)
    *(int *)((char *)this - 0xd0) = getUniformByName(shaderProgram, "ModelViewProj");
}