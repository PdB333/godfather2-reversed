// FUNC_NAME: EntityManager::updateEntities

// Function at 0x004b6330: Main update loop for all entities in the manager.
// Processes entity list, updates AI, audio, and rendering state.
// Uses global audio manager singleton and scene graph for transforms.

// Class layout (assuming EntityManager):
// +0x00: vtable
// +0x04: mSomePointer (some state object, possibly for resource queries)
// +0x08: mSceneGraph (pointer to scene graph interface)
// +0x18: mEntityArray (array of 0x70-byte entity handles)
// +0x1C: mEntityCount (number of entities)
// +0x20: mVelocityRelated (pointer to something with velocity at +0x30)
// +0x24: mAudioSource (audio source object for global sounds)
// +0x28: mFlags (byte flags: bit0 = initialized, bit4 = some condition)

// Entity handle structure (0x70 bytes):
// +0x40: entity object pointer (iVar6)
// Entity object:
// +0xD8: mTypeID (char, compared to 7)
// +0xD0: mComponent (vtable pointer for component)

// Global state:
extern int gAudioManagerInitFlag;          // _DAT_01227890
extern int gAudioManagerStruct;            // _DAT_01227880 (struct with vtable)
extern int gAudioManagerStruct2;           // _DAT_01227884
extern int gAudioManagerStruct3;           // _DAT_01227888
extern int gAudioManagerStruct4;           // _DAT_0122788c
extern int gInvalidValue;                  // DAT_00e2b1a4 (some sentinel)
extern float gSpeedThresholdSq;            // _DAT_00e2e084 (squared speed threshold)

// Forward declarations of helper functions (callees renamed)
void checkEntityCondition(byte* result, int param);
int findSoundBank(int hash);               // 0x4a3790
void initSoundBuffer(void* buffer);        // 0x4a36a0
void copySoundParams(void* dest, void* src); // 0x49da0
void updateAudio();                        // 0x417560
void playSound(void* src, void* params);   // 0x4b59d0
void submitSound(void* params);            // 0xaa3930
void createTransform(void* tform);         // 0xaa5450
void getWorldMatrix(void* mat, void* handle); // 0xaa1cf0
void initSoundPackage(void* pkg);          // 0x9f4cd0
void beginAudioUpdate();                   // 0x9f2000
void endAudioUpdate();                     // 0x9f2000 (same address, used twice)
void updateEntityAI(int entity, int param); // 0x9e6ff0
void updateAudioSource(int src);           // 0x9f1f90
void finalizeAudio();                      // 0x9f0190
void postUpdateCleanup();                  // 0x4b6760
void playAmbientSound(int sceneNode);      // 0x610100

// Scene graph interface assumed:
class SceneGraph {
public:
    virtual void* getRenderData();          // vtable +4
    virtual void* getNodeManager();         // vtable +0x20
};

class NodeManager {
public:
    virtual void* getData();                // vtable +4
    virtual void addEntity(void* entity);   // vtable +0x3c
    virtual void flush();                   // vtable +0x44
};

void __fastcall EntityManager::updateEntities()
{
    byte conditionResult[8];
    byte tempArray[16];
    byte audioParams[12];
    byte buffer[64];
    byte tempData[12];
    byte worldMatrix[48];
    byte soundPackage[76];
    int entityOffset;
    uint entityIndex;

    // Check if already initialized this frame (bit 0 of mFlags)
    if ((mFlags & 1) == 0)
    {
        bool firstProcessed = false;

        // Initialize global audio manager singleton if needed
        if ((gAudioManagerInitFlag & 1) == 0)
        {
            gAudioManagerInitFlag |= 1;
            // Initialize the four fields of the audio struct
            gAudioManagerStruct = 0;
            gAudioManagerStruct2 = 0;
            gAudioManagerStruct3 = 0;
            gAudioManagerStruct4 = gInvalidValue;
        }

        bool hasEntities = (mEntityCount != 0);
        entityIndex = 0;
        if (hasEntities)
        {
            entityOffset = 0;
            do
            {
                // Get actual entity object pointer from handle array
                int entity = *(int*)(entityOffset + 0x40 + mEntityArray);
                
                // Check if entity meets condition (e.g., visible, in range)
                checkEntityCondition(conditionResult, 0x800);
                
                if ((conditionResult[0] & 1) == 0)
                {
                    if (!firstProcessed)
                    {
                        // First entity that fails condition triggers setup
                        if ((mFlags & 0x10) == 0)
                        {
                            // Normal path: get render data from scene graph
                            SceneGraph* scene = *(SceneGraph**)(mSceneGraph + 8);
                            void* renderData = scene->getRenderData();
                            
                            // If mSomePointer is set, try to play a sound
                            if (mSomePointer != 0)
                            {
                                int soundBank = findSoundBank(0xd550688c); // hash for a sound clip
                                if (soundBank != 0)
                                {
                                    // Initialize sound related data
                                    int zero1 = 0;
                                    int zero2 = 0;
                                    int zero3 = 0;
                                    int sentinel = gInvalidValue;
                                    initSoundBuffer(buffer);
                                    copySoundParams(audioParams, buffer);
                                    updateAudio();
                                    renderData = tempData; // overwrite renderData pointer to tempData
                                }
                            }
                        }
                        else
                        {
                            // Alternate path: use node manager to get data
                            SceneGraph* scene = *(SceneGraph**)(mSceneGraph + 8);
                            NodeManager* nodeMgr = scene->getNodeManager();
                            void* nodeData = nodeMgr->getData();
                            renderData = nodeData; // note: 'renderData' is from previous scope, but in asm it's separate.
                            // Actually in the else branch, puVar4 is set from piVar3->vtable+4 call.
                            // Reconstruct:
                            // piVar3 = nodeMgr; renderData = nodeMgr->getData();
                        }
                    }
                    
                    // Play sound using renderData and audioParams
                    playSound(renderData, audioParams);
                    submitSound(audioParams);
                    
                    // Extract transform from renderData (offsets +0x30,+0x34,+0x38)
                    int x = *(int*)(renderData + 0x30);
                    int y = *(int*)(renderData + 0x34);
                    int z = *(int*)(renderData + 0x38);
                    createTransform(tempArray);
                    
                    // Store transform components and sentinel in stack area
                    // uStack_a0 = x, uStack_9c = y, uStack_98 = z, uStack_94 = sentinel
                    // These are used later? Not explicitly, maybe for something else.
                    // For reconstruction, we just note that the transform was created.
                    
                    firstProcessed = true;
                }
                
                // Get world matrix for this entity handle
                getWorldMatrix(worldMatrix, mEntityArray + entityOffset);
                initSoundPackage(soundPackage);
                
                // Check entity type
                char type = *(char*)(entity + 0xd8);
                if (type != 7)
                {
                    // Update audio for this entity
                    beginAudioUpdate();
                    (* (void (**)(void*)) (*(int*)(entity + 0xd0) + 0x40))(&gAudioManagerStruct);
                    endAudioUpdate();
                    beginAudioUpdate();
                    (* (void (**)(void*)) (*(int*)(entity + 0xd0) + 0x44))(&gAudioManagerStruct);
                    endAudioUpdate();
                }
                
                // Update entity AI
                updateEntityAI(entity, 1);
                
                // Update audio source if present
                if (mAudioSource != 0)
                {
                    updateAudioSource(mAudioSource);
                    finalizeAudio();
                }
                
                // Call virtual method on this to handle entity
                (this->* (void (__thiscall *)(int)) (this->vtable[0x84/4]))(entity);
                
                // Add entity to node manager
                SceneGraph* scene = *(SceneGraph**)(mSceneGraph + 8);
                NodeManager* nodeMgr = scene->getNodeManager();
                nodeMgr->addEntity(entity);
                
                entityOffset += 0x70;
                entityIndex++;
            } while (entityIndex < (uint)mEntityCount);
            hasEntities = (mEntityCount == 0);
        }
        else
        {
            hasEntities = false;
        }
        
        if (!hasEntities)
        {
            // Flush node manager after processing all entities
            SceneGraph* scene = *(SceneGraph**)(mSceneGraph + 8);
            NodeManager* nodeMgr = scene->getNodeManager();
            nodeMgr->flush();
        }
        
        // Mark as initialized this frame
        mFlags |= 1;
        
        // Post-update cleanup
        postUpdateCleanup();
        
        // Check velocity magnitude threshold
        if (mVelocityRelated != 0)
        {
            float velx = *(float*)(mVelocityRelated + 0x30);
            float vely = *(float*)(mVelocityRelated + 0x34);
            float velz = *(float*)(mVelocityRelated + 0x38);
            float speedSq = velx*velx + vely*vely + velz*velz;
            if (speedSq > gSpeedThresholdSq)
            {
                mFlags |= 4;
            }
        }
        
        // Play ambient sound if scene graph has an audio source at +0x80
        SceneGraph* scene = *(SceneGraph**)(mSceneGraph + 8);
        int sceneAudio = (int)scene->getRenderData();
        if (*(int*)(sceneAudio + 0x80) != 0)
        {
            playAmbientSound(sceneAudio);
        }
    }
    return;
}