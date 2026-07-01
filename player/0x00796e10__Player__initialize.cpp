// FUNC_NAME: Player::initialize
// Function address: 0x00796e10
// This function initializes various components of a Player object, including physics, model, and state transitions.

class Player {
public:
    // Vtable at offset 0
    // +0x14: virtual void update();
    // +0x44: virtual void sendMessage(uint32_t msg, uint32_t param);
    // +0x54: virtual void setState(int state);
    // +0x58: virtual int getState();
    // +0x5C: virtual void setColor(uint32_t color1, uint32_t color2);

    // Offsets (in bytes) from this pointer
    // +0x130: Component* m_pComponent; // param_1[0x4c]
    // +0x1CC: int m_state; // param_1[0x73] = 6
    // +0x270: Entity* m_pParent; // param_1[0x9c]
    // +0x2BC: uint32_t m_flags; // param_1[0xaf]
    // +0x32C: PhysicsObject* m_pPhysics; // param_1[0xcb]
    // +0x334: uint32_t m_modelHash; // param_1[0xcd]
    // +0x338: uint32_t m_id1; // param_1[0xce]
    // +0x33C: uint32_t m_id2; // param_1[0xcf]
    // +0x340: uint32_t m_id3; // param_1[0xd0]
    // +0x344: uint32_t m_id4; // param_1[0xd1]
    // +0x348: Entity* m_pTarget; // param_1[0xd2]
    // +0x390: Transform* m_pTransform; // param_1[0xe4]
    // +0x394: ModelResource* m_pModelResource; // param_1[0xe5]
    // +0x400: Vector3 m_position; // param_1[0x100] (3 floats)
    // +0x40C: float m_rotation; // param_1[0x102] (actually 0x408? careful: param_1[0x102] is int, but likely float)

    void initialize();
};

// External functions (renamed for clarity)
extern bool isGameMode(uint32_t mode, uint32_t subMode); // FUN_00795a90
extern void setState(Player* pPlayer, int state); // FUN_0043c490
extern void getCameraTransform(Vector3* outPos, Vector3* outRot); // FUN_00471610
extern void* tlsAllocate(uint32_t size, uint32_t tag); // FUN_00aa2150
extern void* tlsAllocate2(uint32_t size, uint32_t tag); // FUN_00aa2680
extern ModelResource* loadModelResource(uint32_t hash); // FUN_00a64b00
extern PhysicsObject* createPhysicsObject(ModelResource* model, Transform* transform, int flags); // FUN_00549b60
extern uint32_t getResourceId(uint32_t type, uint32_t subtype, uint32_t index); // FUN_00540c60
extern Entity* findEntityByHash(uint32_t* hashArray); // FUN_00445ff0
extern bool getEntityProperty(Entity* entity, uint32_t propHash, int* outValue); // FUN_00793fc0
extern void releaseProperty(int value); // FUN_00793f80
extern void updateAudio(bool flag); // FUN_00794600
extern void updateUI(); // FUN_00794500
extern void releaseResource(void* resource); // FUN_00408680
extern Entity* getParentEntity(Entity* child); // FUN_006b07e0
extern Entity* getChildEntity(Entity* parent, int index); // FUN_006b48b0
extern void attachChild(Entity* parent, Entity* child); // FUN_00796b40
extern ModelInstance* getModelInstance(uint32_t modelId); // FUN_008dd580
extern void setModel(Player* player, ModelInstance* model); // FUN_00796210
extern void finalizeInit(); // FUN_007947b0
extern void handleSpecialCase(Player* player, Entity* target); // FUN_00796ba0
extern void doSomething(); // FUN_00794800
extern void cleanup(); // FUN_004086d0

// Global variables
extern uint32_t g_someConstant; // _DAT_00d5780c
extern uint32_t g_tlsIndex; // DAT_01139810
extern Entity* g_someEntity; // DAT_00d5ccf8
extern void* g_resource1; // DAT_0112a600
extern void* g_resource2; // DAT_0112a628
extern void* g_resource3; // DAT_0112a5f0
extern void* g_resource4; // DAT_0112a5e8
extern void* g_resource5; // DAT_0112a5d8
extern void* g_resource6; // DAT_0112a620
extern void* g_resource7; // DAT_0112a618
extern void* g_resource8; // DAT_0112a5cc
extern void* g_someFlag; // DAT_0120e93c

void Player::initialize() {
    bool flag = isGameMode(0, 1);
    Component* pComponent = m_pComponent; // +0x130

    if (flag) {
        if (pComponent != nullptr) {
            pComponent->sendMessage(0x6f74af5b, 1); // +0x44 virtual
        }
    } else {
        if (pComponent != nullptr) {
            pComponent->sendMessage(0x6f74af5b, 0);
        }
    }

    m_state = 6; // +0x1CC
    setState(this, 10); // FUN_0043c490

    // Call virtual update
    this->update(); // +0x14

    // Get camera transform
    Vector3 camPos, camRot;
    getCameraTransform(&camPos, &camRot); // FUN_00471610

    // Allocate transform block from TLS
    void* tlsData = TlsGetValue(g_tlsIndex);
    Transform* pTransform = *(Transform**)((uint8_t*)tlsData + 0x80);
    if (pTransform == nullptr) {
        pTransform = (Transform*)tlsAllocate(9, 9); // size 9? likely 9*4=36 bytes
    } else {
        *(int*)((uint8_t*)tlsData + 0x84) -= 1;
        *(Transform**)((uint8_t*)tlsData + 0x80) = (Transform*)pTransform->next;
    }

    m_pTransform = pTransform; // +0x390

    // Initialize transform
    pTransform->field0 = 0;
    pTransform->field1 = 0;
    pTransform->field2 = 0;
    pTransform->field3 = 0;
    pTransform->field4 = 0;
    pTransform->field6 = 0;
    pTransform->field7 = 0;
    pTransform->field8 = 0;
    pTransform->field9 = 0;
    pTransform->fieldB = 0;
    pTransform->someConstant = g_someConstant;
    pTransform->field5 = g_someConstant;
    pTransform->field10 = g_someConstant;

    // Copy camera transform into transform block at offsets 0x30,0x34,0x38,0x3c
    pTransform->posX = camPos.x;
    pTransform->posY = camPos.y;
    pTransform->posZ = camPos.z;
    pTransform->rot = camRot.x; // simplified

    // Load model resource
    uint32_t modelHash = m_modelHash; // +0x334
    TlsGetValue(g_tlsIndex); // unused return
    void* modelMem = tlsAllocate2(0x20, 0x27); // allocate 32 bytes
    *(uint16_t*)((uint8_t*)modelMem + 4) = 0x20; // size field
    m_pModelResource = loadModelResource(modelHash); // +0x394

    // Allocate physics object
    tlsData = TlsGetValue(g_tlsIndex);
    PhysicsObject* pPhysics = *(PhysicsObject**)((uint8_t*)tlsData + 0x68);
    if (pPhysics == nullptr) {
        pPhysics = (PhysicsObject*)tlsAllocate(6, 0x27);
    } else {
        *(int*)((uint8_t*)tlsData + 0x6C) -= 1;
        *(PhysicsObject**)((uint8_t*)tlsData + 0x68) = (PhysicsObject*)pPhysics->next;
    }

    if (pPhysics != nullptr) {
        m_pPhysics = createPhysicsObject(m_pModelResource, m_pTransform, 0); // +0x32C
    } else {
        m_pPhysics = 0;
    }

    // Set physics resource ID
    uint32_t resId = getResourceId(0x12, 0x1f, 0);
    m_pPhysics->resourceId = resId; // +0x1C

    // Check if we need to load a specific model based on hash
    int* pTarget = &m_pTarget; // +0x348
    if ((*pTarget == 0 || *pTarget == 0x48) &&
        (m_id1 != 0xBBADB9BA || // -0x45245246
         (m_id2 != 0xBEEFBEEF || // -0x41104111
          m_id3 != 0xEAC15A55 || // -0x153ea5ab
          m_id4 != 0x91100911))) { // -0x6eeff6ef
        Entity* entity = findEntityByHash(&m_id1); // +0xCE
        if (entity != nullptr) {
            int value = 0;
            if (getEntityProperty(entity, 0x63c15f4e, &value)) {
                releaseProperty(value);
            }
        }
    }

    // Store camera transform again
    getCameraTransform(&camPos, &camRot);
    m_position = camPos; // +0x100 (3 floats)
    m_rotation = camRot.x; // +0x102 (float)

    bool flag2 = isGameMode(0, 1);
    updateAudio(flag2);
    updateUI();

    if (m_pParent != nullptr) { // +0x9C
        releaseResource(&g_resource1);
        releaseResource(&g_resource2);
        releaseResource(&g_resource3);
        releaseResource(&g_resource4);
        releaseResource(&g_resource5);
        releaseResource(&g_resource6);

        Entity* parent = getParentEntity(m_pParent);
        if (parent != nullptr) {
            Entity* child = getChildEntity(parent, 0);
            attachChild(child, nullptr);
            ModelInstance* model = getModelInstance(*(uint32_t*)((uint8_t*)parent + 0x180));
            setModel(this, model);
        }
        finalizeInit();
    }

    // Check flag bit 10 (0x400)
    if ((m_flags >> 10) & 1) {
        if (*pTarget != 0 && *pTarget != 0x48) {
            int offset = (*pTarget == 0) ? 0 : (*pTarget - 0x48);
            if (*(int*)((uint8_t*)offset + 0x348) == 0) {
                pTarget = nullptr;
            } else {
                pTarget = (int*)(*(int*)((uint8_t*)offset + 0x348) - 0x48);
            }
            if (pTarget != (int*)this) {
                goto skipSpecial;
            }
        }
        handleSpecialCase(this, g_someEntity);
    }
skipSpecial:

    int state = this->getState(); // +0x58 virtual
    if (state == 0x1ff) {
        if (!((m_flags >> 5) & 1) && m_pParent != nullptr) {
            releaseResource(&g_resource7);
            releaseResource(&g_resource8);
            m_flags |= 0x2000;
            doSomething();
            cleanup();
            return;
        }
        this->setState(2); // +0x54 virtual
        this->setColor(0x40, 0xC0); // +0x5C virtual
    }
    cleanup();
}