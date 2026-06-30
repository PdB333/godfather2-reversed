// FUNC_NAME: Entity::Entity (constructor at 0x004ed930)
// Role: Initializes an Entity object from a data source (template/definition)
// Called during entity creation, sets up transform, level indices, and other fields

class Entity {
public:
    // Vtable pointer at +0x00
    void* vtable;

    // Fields (offsets in bytes)
    // +0x04: unknown pointer (param_1[1])
    // +0x08: unknown (param_1[2])
    // +0x0c: unknown (param_1[3])
    // +0x10: unknown (param_1[4])
    // +0x14: unknown (param_1[5])
    // +0x18: unknown (param_1[6])
    // +0x1c: unknown (param_1[7])
    // +0x20: unknown (param_1[8])
    // +0x24: data source pointer (param_1[9])
    // +0x28: some ID or handle (param_1[10])
    // +0x2c: unknown (param_1[11])
    // +0x30: unknown (param_1[12]) - set to 0
    // +0x34: unknown (param_1[13]) - set to 0
    // +0x38: some global value (param_1[14])
    // +0x3c: same global value (param_1[15])
    // +0x40: -1 (param_1[16])
    // +0x44: unknown (param_1[17]) - set to 0
    // +0x48: level index 1 (param_1[18])
    // +0x4c: level type 1 (param_1[19]) - 1,2,3
    // +0x50: unknown (param_1[20]) - set to 0
    // +0x54: level index 2 (param_1[21])
    // +0x58: level type 2 (param_1[22]) - 1,2,3
    // +0x5c: byte flag (param_1[23]) - set to 1
    // +0x60: rotation/position component (param_1[24])
    // +0x64: rotation/position component (param_1[25])
    // +0x68: rotation/position component (param_1[26])
    // +0x6c: unknown (param_1[27]) - set to 0

    // Data source structure (param_2) offsets:
    // +0x00: some ID (first dword)
    // +0x14: float X
    // +0x18: float Y
    // +0x1c: float Z
    // +0x20: float? (used for rotation)
    // +0x24: float?
    // +0x28: float?
    // +0x2c: flags (ushort)
    // +0x3c: value for level index 1 (if type 3)
    // +0x48: value for level index 2 (if type 3)
    // +0x5c: threshold for level type 1 (low)
    // +0x60: threshold for level type 1 (mid)
    // +0x64: threshold for level type 1 (high)
    // +0x70: value for level index 1 (if type 1 or 2)
    // +0x78: threshold for level type 2 (low)
    // +0x7c: threshold for level type 2 (mid)
    // +0x80: threshold for level type 2 (high)
    // +0x8c: value for level index 2 (if type 1 or 2)
};

// External functions called
extern void __cdecl baseConstructor(); // FUN_00533cc0
extern void __cdecl initTransform1(float x, float y, float z, int* matrix); // FUN_0056b8a0
extern void __cdecl initTransform2(float x, float y, float z); // FUN_0056bda0
extern void __cdecl subInit(); // FUN_00533fb0
extern void __cdecl unknownInit(); // FUN_0048ee40
extern void __thiscall subEntityInit(Entity* this, void* dataSource, int param3, int param4, int param5); // FUN_004ed620

// Global constants (from data section)
extern float g_scaleFactor; // DAT_00e445c8
extern float g_offset; // DAT_00e44594
extern int g_globalValue; // DAT_00e2b1a4
extern float g_threshold; // DAT_00e2eff4

// TLS access: get pointer to global manager (e.g., SimManager)
inline int* getGlobalManager() {
    // FS segment offset 0x2c points to a thread-local pointer
    // In Windows, __readfsdword(0x2c) gives the pointer to the thread environment block (TEB)
    // The TEB+0x2c is the thread-local storage array pointer
    // We dereference it to get the actual manager pointer
    return *(int**)(__readfsdword(0x2c));
}

Entity* __thiscall Entity::Entity(Entity* this, void* dataSource) {
    baseConstructor(); // Call base class constructor
    this->vtable = &PTR_FUN_00e37310; // Set vtable

    float scale = g_scaleFactor;

    // Guard: check if already initialized (byte at +0x0d)
    if (*(char*)(this + 0x0d) == '\0') {
        int* manager = getGlobalManager(); // Get global manager pointer
        this->dataSource = dataSource; // Store data source at +0x24

        // Check flag at dataSource+0x2c (bit 0x200)
        if ((*(unsigned short*)((char*)dataSource + 0x2c) & 0x200) == 0) {
            // Standard transform initialization
            float x = *(float*)((char*)dataSource + 0x14) * scale;
            float y = *(float*)((char*)dataSource + 0x18) * scale;
            float z = *(float*)((char*)dataSource + 0x1c) * scale;
            int* matrix = (int*)((char*)manager + 8 + 0x10 + this->field_4); // manager+8+0x10+this[4]
            initTransform1(x, y, z, matrix);
            // Read rotation components from dataSource+0x20,0x24,0x28
            this->rotComp1 = *(int*)((char*)dataSource + 0x20);
            this->rotComp2 = *(int*)((char*)dataSource + 0x24);
            this->rotComp3 = *(int*)((char*)dataSource + 0x28);
        } else {
            // Alternative transform initialization (with offset)
            float x = (*(float*)((char*)dataSource + 0x18) + g_offset) * scale;
            float y = *(float*)((char*)dataSource + 0x14) * scale;
            float z = (*(float*)((char*)dataSource + 0x1c) + g_offset) * scale;
            initTransform2(x, y, z);
            // Read rotation components in different order
            this->rotComp1 = *(int*)((char*)dataSource + 0x28);
            this->rotComp2 = *(int*)((char*)dataSource + 0x20);
            this->rotComp3 = *(int*)((char*)dataSource + 0x24);
        }

        // Zero out several fields
        this->field_12 = 0; // +0x30
        this->field_13 = 0; // +0x34
        this->field_17 = 0; // +0x44
        this->field_20 = 0; // +0x50
        this->field_11 = 0; // +0x2c

        subInit(); // Another initialization step
        int globalVal = g_globalValue; // +0x38 and +0x3c will be set to this

        unknownInit(); // Unknown initialization

        // Call sub-entity init with parameters from this
        subEntityInit(this, dataSource, *(int*)((char*)this->field_1 + 0x10), this->field_4, this->field_5);

        float threshold = g_threshold; // Global threshold for level selection
        int* data = (int*)this->dataSource; // Cast data source to int array

        // Determine level type 1 (stored at +0x4c) and index (at +0x48)
        this->levelType1 = 0;
        if (threshold < (float)data[0x19]) { // data[0x19] = offset 0x64
            if ((float)data[0x17] <= threshold) { // data[0x17] = offset 0x5c
                if ((float)data[0x18] <= threshold) { // data[0x18] = offset 0x60
                    this->levelType1 = 3;
                    this->levelIndex1 = data[0xf]; // data[0xf] = offset 0x3c
                } else {
                    this->levelType1 = 2;
                    this->levelIndex1 = data[0x1c]; // data[0x1c] = offset 0x70
                }
            } else {
                this->levelType1 = 1;
                this->levelIndex1 = data[0x1c]; // data[0x1c] = offset 0x70
            }
        }

        // Determine level type 2 (stored at +0x58) and index (at +0x54)
        this->levelType2 = 0;
        if (threshold < (float)data[0x20]) { // data[0x20] = offset 0x80
            if ((float)data[0x1e] <= threshold) { // data[0x1e] = offset 0x78
                if ((float)data[0x1f] <= threshold) { // data[0x1f] = offset 0x7c
                    this->levelType2 = 3;
                    this->levelIndex2 = data[0x12]; // data[0x12] = offset 0x48
                } else {
                    this->levelType2 = 2;
                    this->levelIndex2 = data[0x23]; // data[0x23] = offset 0x8c
                }
            } else {
                this->levelType2 = 1;
                this->levelIndex2 = data[0x23]; // data[0x23] = offset 0x8c
            }
        }

        // Set remaining fields
        this->someId = data[0]; // +0x28 = first dword of data source
        this->rotComp1 = this->rotComp1; // Already set above, but reassigned? Actually the code sets +0x60 and +0x64 from local_60 and local_5c, and +0x68 from uVar5. So we need to store them.
        // Note: The earlier assignments to rotComp1, rotComp2, rotComp3 were from the branch, but then they are overwritten? Actually the code sets param_1[0x18] = local_60, param_1[0x19] = local_5c, param_1[0x1a] = uVar5. So we need to store them after the level selection.
        // But the decompiled code shows that after the level selection, it sets param_1[0x18] = local_60, etc. So we should store them there.
        // However, the local variables local_60, local_5c, uVar5 were set earlier from the data source. So we need to keep them.
        // We'll store them in the appropriate fields.
        this->rotComp1 = this->rotComp1; // Actually we need to use the local variables. Let's restructure.

        // Since the decompiled code sets these after level selection, we'll do the same.
        this->field_24 = this->rotComp1; // +0x60
        this->field_25 = this->rotComp2; // +0x64
        this->field_26 = this->rotComp3; // +0x68

        // Set global values and flag
        this->globalVal1 = globalVal; // +0x38
        this->globalVal2 = globalVal; // +0x3c
        this->negativeOne = -1; // +0x40
        *(char*)(this + 0x5c) = 1; // Set byte at +0x5c to 1 (flag)
    }

    return this;
}