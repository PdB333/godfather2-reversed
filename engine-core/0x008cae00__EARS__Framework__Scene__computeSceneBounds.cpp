// FUNC_NAME: EARS::Framework::Scene::computeSceneBounds
// Function address: 0x008cae00
// Combines bounding boxes from all objects in a scene manager, computes overall AABB,
// and sets it on an output object (likely a BoundingBoxComponent).

// Forward declarations of called functions (incomplete signatures)
void debugPushMarker();  // 0x004a37d0
class EntityManager* getEntityManager();  // 0x0054a4d0
void mergeBoundingBoxes(float* aabbMin, float* aabbMax);  // 0x004bd0e0
void setBoundingBox(char* buffer, int something);  // 0x0042a1a0

void Scene::computeSceneBounds(int unusedThis, Scene* scene)
{
    debugPushMarker();

    EntityManager* pManager = getEntityManager();
    if (pManager != nullptr)
    {
        int entityCount = *(int*)((int)pManager + 0xC);   // +0xC: number of entities
        int index = 0;

        // Arrays for axis-aligned bounding box: min (x,y,z,w) and max (x,y,z,w)
        float minX, minY, minZ, minW;
        float maxX, maxY, maxZ, maxW;

        // Temporary storage for each entity's AABB
        float entityMin[4];
        float entityMax[4];

        // Global transform matrix (likely world origin)
        // DAT_011397d0 is a global matrix; 0 indicates identity?
        // In the binary, this is a hardcoded global pointer.
        void* globalTransform = (void*)0x011397d0;

        if (entityCount > 0)
        {
            do
            {
                // Get entity pointer from manager's array at +0x8
                int* entityArray = *(int**)((int)pManager + 0x8); // +0x8: pointer to array of entity pointers
                int entityPtr = entityArray[index];

                // Entity structure: +0x10 points to a sub-object (e.g., Renderable) that has a vtable
                // Vtable offset +0x1C is a method to get world AABB
                // The method takes (const Matrix* transform, int flags, float* output8Floats)
                auto getAABB = *(void (__thiscall**)(void*, int, float*))(*(int*)(*(int*)(entityPtr + 0x10) + 0x1C));

                if (index == 0)
                {
                    // First entity: read AABB directly into min/max arrays
                    getAABB(globalTransform, 0, &minX); // writes 8 floats: minX,minY,minZ,minW,maxX,maxY,maxZ,maxW
                    // After call, stack variables: minX,minY,minZ,minW are set
                    // maxX,maxY,maxZ,maxW are also set (consecutive in memory)
                    maxW = *(float*)(&minX + 7); // maxW is the last float written (after minX..minW, maxX..maxW)
                }
                else
                {
                    // For subsequent entities
                    float tempMin[4];
                    float tempMax[4];
                    getAABB(globalTransform, 0, &tempMin); // writes 8 floats into tempMin..tempMax

                    // Compare new AABB with current min/max
                    // Update min
                    if (tempMin[0] <= minX) minX = tempMin[0];
                    if (tempMin[1] <= minY) minY = tempMin[1];
                    if (tempMin[2] <= minZ) minZ = tempMin[2];
                    if (tempMin[3] <= minW) minW = tempMin[3];

                    // Update max (take larger values)
                    if (tempMax[0] > maxX) maxX = tempMax[0];
                    if (tempMax[1] > maxY) maxY = tempMax[1];
                    if (tempMax[2] > maxZ) maxZ = tempMax[2];
                    if (tempMax[3] > maxW) maxW = tempMax[3];
                }
                index++;
            } while (index < entityCount);
        }

        // Combine min and max into a single AABB structure (e.g., maybe clip or transform)
        mergeBoundingBoxes(&minX, &maxX);

        // Get an object from scene parameter at +0x8
        // scene+0x8 likely points to a component that accepts a bounding box
        int* sceneComponent = *(int**)((int)scene + 0x8);
        // Virtual table of that component: offset 0x20 returns some class identifier
        auto getComponentId = *(int (__thiscall**)(void*))(*(int*)sceneComponent + 0x20);
        int componentId = getComponentId(sceneComponent);
        // Virtual table offset 0x04: get some value (maybe version or type)
        auto getSubId = *(int (__thiscall**)(void*))(*(int*)sceneComponent + 0x04);
        int subId = getSubId(sceneComponent);
        // Set the computed bounding box on the component
        char buffer[16]; // placeholder for AABB data structure
        setBoundingBox(buffer, componentId, subId);
    }
}