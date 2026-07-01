// FUNC_NAME: Entity::initTransformFromData

class Entity {
public:
    // vtable at offset 0
    virtual bool isDataValid(void* data) = 0; // vtable+0x14
    // +0x08: Transform* parentTransform; // pointer to parent transform data
};

class Transform {
public:
    // vtable at offset 0
    virtual void setExtraParam(int param) = 0; // vtable+0x04
    // +0x1C (28): int localTransform[4]; // copied from data[0..3]
    // +0x3C (60): int worldTransform[4]; // copied from parentTransform+0x24..0x30
};

// External functions (likely from engine)
Transform* findOrCreateTransform(void* data); // FUN_0082a540
void* getAllocator(); // FUN_009c8f80
Transform* createTransform(); // FUN_008297a0
void registerTransform(Transform* t); // FUN_00832240

int __thiscall Entity::initTransformFromData(int* thisPtr, int* data, int extraParam) {
    bool isNewObject = true;
    Transform* transform;

    // Validate input data via virtual call
    if (!thisPtr->isDataValid(data)) {
        return 0;
    }

    // Try to find existing transform for this data
    transform = findOrCreateTransform(data);
    if (transform == nullptr) {
        isNewObject = false;
        // Allocate memory for new transform (size 0xB0 = 176 bytes)
        void* mem = getAllocator()->allocate(0xB0);
        if (mem != nullptr) {
            transform = createTransform();
            if (transform != nullptr) {
                goto LAB_008329f0;
            }
        }
        return 0;
    }

LAB_008329f0:
    // Copy local transform data from input (4 ints at offsets 28-40)
    transform->localTransform[0] = data[0];
    transform->localTransform[1] = data[1];
    transform->localTransform[2] = data[2];
    transform->localTransform[3] = data[3];

    // Copy world transform from parent (if available)
    // parentTransform is at this+0x08
    int* parentTransform = (int*)thisPtr[2]; // +0x08
    if (parentTransform != nullptr) {
        // Parent transform data at offsets 0x24,0x28,0x2C,0x30
        transform->worldTransform[0] = *(int*)(parentTransform + 0x24 / 4);
        transform->worldTransform[1] = *(int*)(parentTransform + 0x28 / 4);
        transform->worldTransform[2] = *(int*)(parentTransform + 0x2C / 4);
        transform->worldTransform[3] = *(int*)(parentTransform + 0x30 / 4);
    }

    // Apply extra parameter if provided
    if (extraParam != 0) {
        transform->setExtraParam(extraParam);
    }

    // If newly created, register the transform
    if (!isNewObject) {
        registerTransform(transform);
    }

    return 1;
}