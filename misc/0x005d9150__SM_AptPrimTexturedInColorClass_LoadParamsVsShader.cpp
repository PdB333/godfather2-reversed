// Xbox PDB: SM_AptPrimTexturedInColorClass::LoadParamsVsShader
// FUNC_NAME: ShaderMaterial::initShaderParams
// Address: 0x005d9150
// Role: Retrieves shader parameter handles from a shader manager and stores them in member variables.

class ShaderMaterial {
public:
    // Member variable offsets (relative to 'this'):
    // +0x100 : m_inColorMul (handle for "inColorMul")
    // +0x60  : m_inColorAdd (handle for "inColorAdd")
    // -0x78  : m_transU (handle for "transU")
    // -0x74  : m_transV (handle for "transV")
    // -0xD0  : m_modelViewProj (handle for "ModelViewProj")
    // Note: Negative offsets indicate fields stored before 'this' pointer, possibly in a base class or vtable region.

    void __thiscall initShaderParams()
    {
        int handle;

        // Retrieve shader parameter handle for "inColorMul"
        handle = getShaderParameterHandle(*(int*)((char*)this - 0x110), "inColorMul");
        *(int*)((char*)this + 0x64) = handle;   // +0x100? Actually offset is 0x64? Wait: original +100 decimal = 0x64 hex. So correct.

        // Retrieve shader parameter handle for "inColorAdd"
        handle = getShaderParameterHandle(*(int*)((char*)this - 0x110), "inColorAdd");
        *(int*)((char*)this + 0x60) = handle;   // offset +0x60

        // Retrieve shader parameter handle for "transU"
        handle = getShaderParameterHandle(*(int*)((char*)this - 0x110), "transU");
        *(int*)((char*)this - 0x78) = handle;   // offset -0x78

        // Retrieve shader parameter handle for "transV"
        handle = getShaderParameterHandle(*(int*)((char*)this - 0x110), "transV");
        *(int*)((char*)this - 0x74) = handle;   // offset -0x74

        // Retrieve shader parameter handle for "ModelViewProj"
        handle = getShaderParameterHandle(*(int*)((char*)this - 0x110), "ModelViewProj");
        *(int*)((char*)this - 0xD0) = handle;   // offset -0xD0
    }

private:
    // External function: likely retrieves a shader parameter handle from a manager.
    // First argument is a pointer to the shader or material data (offset -0x110 from this).
    // Returns an integer handle or index.
    static int __fastcall getShaderParameterHandle(int shaderPtr, const char* name);
};