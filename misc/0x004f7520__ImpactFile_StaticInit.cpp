// FUNC_NAME: ImpactFile_StaticInit
// Initializes a global static descriptor for the "Impact" file format (likely used for game assets)
// Address: 0x004f7520
struct ImpactFileStatic {
    void* vtable;           // +0x00: Pointer to vtable (PTR_LAB_00e378f8)
    const char* name;       // +0x04: "Impact"
    unsigned int extension; // +0x08: ".imp" as little-endian integer (0x2e696d70)
    int unknown1;           // +0x0C: 0
    int fileTypeId;         // +0x10: 0xD (13) – possibly a file type identifier
    int unknown2;           // +0x14: 0
    int maxSize;            // +0x18: 0x800 (2048) – block size or maximum file size
    int unknown3;           // +0x1C: 0
    int unknown4;           // +0x20: 0
    int unknown5;           // +0x24: 0
};

ImpactFileStatic g_ImpactFileStatic; // Global instance at 0x01219000

undefined* ImpactFile_StaticInit(void)
{
    g_ImpactFileStatic.vtable     = &g_vtable_ImpactFile;   // PTR_LAB_00e378f8
    g_ImpactFileStatic.name       = "Impact";
    g_ImpactFileStatic.extension  = 0x2e696d70;             // ".imp"
    g_ImpactFileStatic.unknown1   = 0;
    g_ImpactFileStatic.fileTypeId = 0xD;                    // 13
    g_ImpactFileStatic.unknown2   = 0;
    g_ImpactFileStatic.maxSize    = 0x800;                  // 2048
    g_ImpactFileStatic.unknown3   = 0;
    g_ImpactFileStatic.unknown4   = 0;
    g_ImpactFileStatic.unknown5   = 0;
    return (undefined*)&g_ImpactFileStatic;
}