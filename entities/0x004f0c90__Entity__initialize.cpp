// FUNC_NAME: Entity::initialize
// Function address: 0x004f0c90
// This function initializes an Entity object, setting up its vtable, linking to a resource object,
// and optionally calling a setup function. It appears to be part of the EARS engine's entity system.

class Entity {
public:
    // Vtable pointer at offset 0x00
    void** vtable;
    // Unknown pointer at offset 0x04
    int* field_0x04;
    // Unknown fields at offsets 0x08, 0x0C, 0x10, 0x14, etc.
    int field_0x08;
    int field_0x0C;
    int field_0x10;
    int field_0x14;
    // Pointer to some object at offset 0x24
    void* someObject; // +0x24
    // Pointer to a resource object at offset 0x28
    void* resourceObject; // +0x28
    // Byte flag at offset 0x2C
    char flag_0x2C; // +0x2C
    // Integer at offset 0x30
    int field_0x30; // +0x30
    // ... other members
};

// External functions (guessed names)
extern void initGlobal(); // FUN_00533cc0
extern void scaleVector(float x, float y, float z, int* dest); // FUN_0056b8a0
extern void initSubsystemA(); // FUN_0048ee40
extern void initSubsystemB(); // FUN_00533fb0
extern void* findResource(int id); // FUN_004f1330
extern void setupEntity(Entity* entity, int param2, long long combined, void* obj, int a, int b); // FUN_004f0ab0

// Global scale factor
extern float g_scaleFactor; // DAT_00e445c8

// Thread-local storage offset (FS segment)
extern int* getThreadLocalData(); // unaff_FS_OFFSET + 0x2c

// Vtable for this class (at 0x00e37440)
extern void* g_entityVtable; // PTR_FUN_00e37440

Entity* __thiscall Entity::initialize(Entity* this, int param2, void* in_EAX) {
    int* threadData;
    int* ptr;
    int resourceId;
    void* resource;
    int* addr;
    int* tempStack;
    int edi;

    initGlobal();
    this->vtable = &g_entityVtable;
    this->field_0x30 = 0;

    float scale = g_scaleFactor;
    if (*(char*)(param2 + 0x0D) == '\0') {
        threadData = *(int**)(getThreadLocalData() + 0x2C);
        this->someObject = in_EAX;

        // Scale and store coordinates
        scaleVector(
            *(float*)(in_EAX + 8) * scale,
            *(float*)(in_EAX + 0x0C) * scale,
            *(float*)(in_EAX + 0x10) * scale,
            (int*)(*(int*)(threadData + 8) + 0x10 + this->field_0x10)
        );

        initSubsystemA();
        initSubsystemB();

        this->flag_0x2C = 0;

        ptr = this->field_0x04;
        resourceId = *(int*)(ptr + 8);
        resource = findResource(resourceId);
        this->resourceObject = resource;

        if (resource == nullptr) {
            resource = findResource(*(int*)this->someObject);
            this->resourceObject = resource;
        }

        if (this->resourceObject == nullptr) {
            *(char*)(param2 + 0x0C) = 1;
            return this;
        }

        addr = &this->field_0x30;
        tempStack = addr;

        // Call virtual function at vtable index 0 on resource object
        (*(void (**)(int*, int, void*, int*))(*((int*)this->resourceObject)))(ptr, ptr + 0x20, this->someObject, addr);

        // Call virtual function at vtable index 3 (offset 0x0C) on resource object
        (*(void (**)(int*, int*))(*((int*)this->resourceObject) + 0x0C))(&tempStack, addr);

        if (edi != 0) {
            setupEntity(this, *(int*)(this->field_0x04 + 0x10), ((long long)edi << 32) | (unsigned int)tempStack, this->someObject, this->field_0x10, this->field_0x14);
            this->flag_0x2C = 1;
        }
    }

    return this;
}