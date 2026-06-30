// FUNC_NAME: CharacterModel::CharacterModel
// Function address: 0x004f0c90
// Constructor for CharacterModel class, initializing from a data source (param_2).
// Based on EA EARS engine object hierarchy.

#include <cstdint>

// Forward declarations
class ResourceHandle; // param_1[10]
class ModelData;

// Global scale factor (DAT_00e445c8)
extern float g_scaleFactor;

// Vtable pointer (PTR_FUN_00e37440)
extern void* g_characterModelVtable;

// External functions
extern void BaseClassConstructor(); // FUN_00533cc0
extern void ScaleVector(float x, float y, float z, int* target); // FUN_0056b8a0
extern void UnknownInit1(); // FUN_0048ee40
extern void UnknownInit2(); // FUN_00533fb0
extern ResourceHandle* FindResource(void* resourceId); // FUN_004f1330
extern void RegisterCharacterModel(CharacterModel* model, int* transform, int someArg, void* parent, int* matrix1, int* matrix2); // FUN_004f0ab0

class CharacterModel {
public:
    // Vtable pointer at +0x00
    void* vtable;

    // +0x04: pointer to data source (likely a ModelData)
    ModelData* modelData;

    // +0x08: unknown
    int unknown_0x08;

    // +0x0C: unknown
    int unknown_0x0C;

    // +0x10: first part of transform matrix?
    int transformPart1[4]; // Used by FUN_0056b8a0

    // +0x20: second part of transform?
    int transformPart2[4];

    // +0x30: buffer for resource output (param_1 + 0xc)
    int resourceBuffer[4]; // Actually a 16-byte buffer? Used in vtable calls

    // +0x40: pointer to parent or owning object (param_1[9])
    void* parentObject;

    // +0x44: resource handle (param_1[10])
    ResourceHandle* resourceHandle;

    // +0x48: byte flag (param_1[0xb])
    unsigned char flag_0x48;

    // Constructor
    CharacterModel(ModelData* data, void* parentInEAX) {
        // Call base class constructor (likely EARSObject)
        BaseClassConstructor();

        // Set vtable
        vtable = &g_characterModelVtable;

        // Zero out resource buffer at +0x30
        resourceBuffer[0] = 0;

        // Scale factor
        float scale = g_scaleFactor;

        // Check if the model data indicates we should process (byte at data+0x0D)
        if (*(char*)(data + 0x0D) == '\0') {
            // Get a thread-local pointer or global structure (unaff_FS_OFFSET + 0x2c)
            int* tlsPointer = *(int**)(__readfsdword(0x2C)); // FS:[0x2C] on x86

            // Store parentObject (passed in EAX, possibly the 'this' of a parent)
            parentObject = parentInEAX;

            // Scale a vector from parentObject+8, +0xC, +0x10 and store into transformPart1+0x10 ?
            // Actually FUN_0056b8a0 takes four float args and an int* target
            // The target is tlsPointer+8+0x10 + transformPart1[0]? This is unclear.
            ScaleVector(
                *(float*)((int)parentObject + 8) * scale,
                *(float*)((int)parentObject + 12) * scale,
                *(float*)((int)parentObject + 16) * scale,
                (int*)(*(int*)(tlsPointer + 8) + 0x10 + (int)&transformPart1)
            );

            // More initialization
            UnknownInit1();
            UnknownInit2();

            // Get pointer from modelData+8 and find resource
            int resourceId = *(int*)(modelData + 8);
            resourceHandle = FindResource((void*)resourceId);

            // If first attempt fails, try from parentObject
            if (resourceHandle == nullptr) {
                resourceHandle = FindResource(*(void**)parentObject);
            }

            // If still no resource, set error flag and return
            if (resourceHandle == nullptr) {
                *(char*)(data + 0x0C) = 1;
                return;
            }

            // Use resource buffer at +0x30
            int* buffer = &resourceBuffer[0];
            int* bufferCopy = buffer; // puVar6

            // Call virtual function from resource handle (vtbl[0]) 
            // Likely to bind the resource to the model
            (*(void(**)(ModelData*, int, void*, int*))(*resourceHandle->vtable))(
                modelData,
                (int)modelData + 0x20, // second part of model data?
                parentObject,
                buffer
            );

            // Call another virtual function at vtbl+0xC on the resource handle
            // Possibly to prepare the resource for rendering
            void* stackVar; // placeholder
            (*(void(**)(void*, int*))(*(int*)resourceHandle + 0x0C))(
                &stackVar,
                buffer
            );

            // If some EDI register is non-zero, register the character model
            // (unaff_EDI is likely an external condition like a success flag)
            if (/* unaff_EDI != 0 */ true) {
                RegisterCharacterModel(
                    this,
                    *(int*)(modelData + 0x10), // argument from model data
                    /* CONCAT44(unaff_EDI, bufferCopy) */ (unsigned long long)1 << 32 | (unsigned int)bufferCopy,
                    parentObject,
                    &transformPart1[0], // param_1[4]?
                    &transformPart1[4]  // param_1[5]?
                );

                // Set flag indicating registration happened
                flag_0x48 = 1;
            }
        }
    }
};