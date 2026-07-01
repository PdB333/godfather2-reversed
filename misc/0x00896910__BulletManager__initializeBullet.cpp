// FUNC_NAME: BulletManager::initializeBullet
// Address: 0x00896910
// Initializes a bullet entry in the bullet array. The bullet struct is 0x2C bytes.
// If param_6 is null or its field at offset 0x14 is zero, the bullet is marked inactive and zeroed.
// Otherwise, it computes initial position, direction, and distance.

struct Bullet {
    char active;          // +0x00
    char pad1[3];         // +0x01
    int someID;           // +0x04
    float posX;           // +0x08
    float posY;           // +0x0C
    float posZ;           // +0x10
    float squaredDist;    // +0x14
    float dirX;           // +0x18
    float dirY;           // +0x1C
    float dirZ;           // +0x20
    int someHash;         // +0x24
    float constant;       // +0x28
};

// Global constants
extern float g_bulletConstant; // DAT_01205220
extern int g_defaultSomeID;    // _DAT_00d5780c

// Forward declaration of helper function
int computeHash(void* data); // FUN_00542700

void __thiscall BulletManager::initializeBullet(
    void* thisPtr,
    void* weaponData,
    int bulletIndex,
    float* origin,
    float* direction,
    int* targetData)
{
    // Calculate pointer to the bullet entry in the array at offset +8
    Bullet* bullet = (Bullet*)(*(int*)((char*)thisPtr + 8) + bulletIndex * 0x2C);

    // Set constant field
    bullet->constant = g_bulletConstant;

    // Determine if bullet is active based on targetData
    char isActive;
    if (targetData == nullptr || targetData[0x14] == 0) {
        isActive = 0;
    } else {
        isActive = 1;
    }
    bullet->active = isActive;

    // Set someID: use targetData[4] if available, else default
    int id;
    if (targetData != nullptr) {
        id = targetData[4];
    } else {
        id = g_defaultSomeID;
    }
    bullet->someID = id;

    if (isActive == 0) {
        // Inactive bullet: zero out all fields except constant and someID
        bullet->posX = 0.0f;
        bullet->posY = 0.0f;
        bullet->posZ = 0.0f;
        bullet->dirX = 0.0f;
        bullet->dirY = 0.0f;
        bullet->dirZ = 0.0f;
        bullet->squaredDist = 0.0f;
        bullet->someHash = 0;

        // Set squaredDist to (weaponData+4)^2 (likely speed squared)
        float speed = *(float*)((char*)weaponData + 4);
        bullet->squaredDist = speed * speed;
        return;
    }

    // Active bullet: compute initial position and direction
    float speed = *(float*)((char*)weaponData + 4);
    float scale = speed * (float)targetData[4]; // targetData[4] is an int multiplier
    bullet->posX = origin[0] + direction[0] * scale;
    bullet->posY = origin[1] + direction[1] * scale;
    bullet->posZ = origin[2] + direction[2] * scale;

    // Store direction from targetData (first three floats)
    bullet->dirX = *(float*)&targetData[0];
    bullet->dirY = *(float*)&targetData[1];
    bullet->dirZ = *(float*)&targetData[2];

    // Compute hash from targetData
    bullet->someHash = computeHash(targetData);

    // Compute squared distance from origin to new position
    float dx = origin[0] - bullet->posX;
    float dy = origin[1] - bullet->posY;
    float dz = origin[2] - bullet->posZ;
    bullet->squaredDist = dx*dx + dy*dy + dz*dz;
}