// FUNC_NAME: 0x00701bc0 PlayerAim::getAimTransform
// Address: 0x00701bc0
// Role: Computes aim position and orientation for player weapons.
// Parameters:
//   this - PlayerAim instance
//   outPosition - output world position (Vector3)
//   outForward - output forward direction vector (Vector3)
//   outRight - output right direction vector (Vector3)
//   outUp - output up direction vector (Vector3)
//   useBoneFlag - if true and conditions met, use target bone; else use camera + offsets

struct Vector3 {
    float x, y, z;
};

// Forward declarations for engine functions (reconstructed)
void* getGameManager();                                    // FUN_007079c0 - returns GameManager*
bool isTargetAlive(void* target);                          // FUN_00481620 - checks if target entity is alive
void getBonePosition(Vector3* outPos, int boneIndex);     // FUN_00424fb0 - gets world position of a bone
struct PlayerTransform* getPlayerTransform();              // FUN_00471610 - returns pointer to player's transform struct
bool isButtonPressed(int buttonId);                        // FUN_00690150 - checks if a controller button/axis is pressed

extern float gAimStickSensitivity;                         // _DAT_00e516e0 - horizontal aim sensitivity
extern float gAimStickVerticalSensitivity;                 // _DAT_00e516dc - vertical aim sensitivity

void __thiscall PlayerAim::getAimTransform(PlayerAim* this,
                                           Vector3* outPosition,
                                           Vector3* outForward,
                                           Vector3* outRight,
                                           Vector3* outUp,
                                           char useBoneFlag)
{
    bool useBone = false;
    bool gotTransformFromBone = false;

    // Check if we should try to use the target bone
    if ((useBoneFlag != 0) && (outPosition != nullptr) &&
        ((*(uint*)((char*)this + 0x2d8) >> 2) & 1) != 0)   // +0x2d8 flags bit 2 (presence of aim target)
    {
        useBone = true;
    }
    else
    {
        // Attempt to fall back to bone if the flag is set but other conditions failed
        useBone = false;
        if (((*(uint*)((char*)this + 0x2d8) >> 2) & 1) != 0)
        {
            void* gameManager = getGameManager();
            if (gameManager != nullptr)
                useBone = *(byte*)((char*)gameManager + 0x249f) & 1;  // +0x249f: some global setting
        }
    }

    // If useBone is active and we have a target, try to get position from target's bone
    if (useBone && (((*(uint*)((char*)this + 0x2d8) >> 2) & 1) != 0))
    {
        void* gameManager = getGameManager();
        if ((gameManager != nullptr) &&
            isTargetAlive(gameManager) &&
            ((*(uint*)((char*)gameManager + 0x8e0) >> 6) & 1) == 0)  // +0x8e0 bit 6: target not in special state
        {
            int boneIndex = *(int*)((char*)gameManager + 0x2494);      // +0x2494: bone ID from target
            Vector3 localVec;
            getBonePosition(&localVec, boneIndex);
            *outPosition = localVec;
            gotTransformFromBone = true;
        }
    }

    // If we didn't get a transform from bone, compute from player's camera + offsets + input
    if ((outPosition != nullptr) && !gotTransformFromBone)
    {
        PlayerTransform* playerTrans = getPlayerTransform();            // Returns player/camera transform struct
        // +0x30: camera world position (Vector3)
        // +0x38: maybe extra float? Actually +0x38 is within 12-byte vector? We'll assume it's the z component of position.
        outPosition->x = *(float*)((char*)playerTrans + 0x30);
        outPosition->y = *(float*)((char*)playerTrans + 0x34);
        outPosition->z = *(float*)((char*)playerTrans + 0x38);

        // Apply primary offset from this instance (weapon offset)
        float primaryScale = *(float*)((char*)this + 0x4fc);        // +0x4fc: primary scale factor
        // +0x10, 0x14, 0x18: forward direction from player transform?
        outPosition->x += (*(float*)((char*)playerTrans + 0x10)) * primaryScale;
        outPosition->y += (*(float*)((char*)playerTrans + 0x14)) * primaryScale;
        outPosition->z += (*(float*)((char*)playerTrans + 0x18)) * primaryScale;

        // Apply secondary offset from input (aim assist adjust)
        float secondaryScale = *(float*)((char*)this + 0x500);      // +0x500: secondary scale factor
        PlayerTransform* playerTrans2 = getPlayerTransform();        // Re-get transform (maybe different offset)
        if (playerTrans2 != nullptr)
        {
            // Check if we can apply input adjustments
            if (((*(uint*)((char*)this + 0x2d8) >> 2) & 1) != 0)
            {
                char stateByte = *(char*)((char*)this + 0x1aa);     // +0x1aa: some state (e.g., aiming down sights)
                void* gameManager = getGameManager();
                if ((stateByte == 1) && (gameManager != nullptr))
                {
                    // Apply input from left stick (button 0x41) and left stick press (button 1)?
                    if (isButtonPressed(0x41) && isButtonPressed(1))
                    {
                        secondaryScale -= gAimStickSensitivity;      // Subtract horizontal sensitivity
                    }
                    // Apply input from right trigger (button 0x19) - maybe zoom/aim?
                    if (isButtonPressed(0x19))
                    {
                        secondaryScale -= gAimStickVerticalSensitivity;
                    }
                }
            }
            // +0x20, 0x24, 0x28: right direction from player transform?
            outPosition->x += (*(float*)((char*)playerTrans2 + 0x20)) * secondaryScale;
            outPosition->y += (*(float*)((char*)playerTrans2 + 0x24)) * secondaryScale;
            outPosition->z += (*(float*)((char*)playerTrans2 + 0x28)) * secondaryScale;
        }
    }

    // Output orientation vectors (always filled from player transform)
    if (outForward != nullptr)
    {
        PlayerTransform* playerTrans = getPlayerTransform();
        // +0x20: forward direction
        outForward->x = *(float*)((char*)playerTrans + 0x20);
        outForward->y = *(float*)((char*)playerTrans + 0x24);
        outForward->z = *(float*)((char*)playerTrans + 0x28);
    }

    if (outRight != nullptr)
    {
        PlayerTransform* playerTrans = getPlayerTransform();
        // +0x00: right direction
        outRight->x = *(float*)((char*)playerTrans + 0x00);
        outRight->y = *(float*)((char*)playerTrans + 0x04);
        outRight->z = *(float*)((char*)playerTrans + 0x08);
    }

    if (outUp != nullptr)
    {
        PlayerTransform* playerTrans = getPlayerTransform();
        // +0x10: up direction
        outUp->x = *(float*)((char*)playerTrans + 0x10);
        outUp->y = *(float*)((char*)playerTrans + 0x14);
        outUp->z = *(float*)((char*)playerTrans + 0x18);
    }

    return;
}