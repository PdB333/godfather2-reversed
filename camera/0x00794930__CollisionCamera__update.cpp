// FUNC_NAME: CollisionCamera::update

// 0x00794930: CollisionCamera::update - Main camera update with collision avoidance and state machine
// Handles camera states: 
//   0 = waiting/initialization
//   1 = active (post-update)
//   2 = active (dynamic update with collision)
//   3 = immediate return (reset?)

#include <cstdint>

// Forward declarations of helper functions (see game codebase)
extern float getDeltaTime(int cameraIndex);                    // FUN_00794870
extern void* getCameraFocus();                                  // FUN_00471610 - returns pointer to focus object (position/rotation)
extern int  getCurrentViewId();                                 // (via global interface)
extern void clearReliableMessageQueue(void* queue);            // FUN_00402050
extern void sendOffCameraMessage(void* receiver, int msg);     // FUN_006a8760
extern void broadcastEvent(uint eventType, int data);          // via vtable call at +0x44
extern void applyPosition(CollisionCamera* cam, float* pos);   // virtual call at vtable+0x1c

// Global constants (from decompiled)
const float CAMERA_CONST_A = 0.0f;            // DAT_00e44564
const float CAMERA_CONST_B = 0.0f;            // DAT_00d6a168
const float CAMERA_CONST_C = 0.0f;            // DAT_00d5ef90
const float CAMERA_CONST_D = 0.0f;            // DAT_00d6a0c4
const float CAMERA_CONST_E = 0.0f;            // DAT_00d5780c
const float CAMERA_CONST_F = 0.0f;            // DAT_00d5f00c
const float CAMERA_CONST_G = 0.0f;            // DAT_00d6a160
const float CAMERA_CONST_H = 0.0f;            // DAT_00d5eee4
const float CAMERA_CONST_I = 0.0f;            // DAT_00d6a15c
const float CAMERA_CONST_J = 0.0f;            // DAT_00d6a164

int CollisionCamera::update(int cameraIndex)
{
    // Offsets within this (int* base):
    // +0x2bc (0xaf*4): flags
    // +0x2b8 (0xae*4): state
    // +0x2a4 (0xa9*4): lookAtTarget
    // +0x2ac (0xab*4): lookAtTargetAlt
    // +0x2c0 (0xb0*4): previousState
    // +0x2b4 (0xad*4): desiredDistance (when state=2)
    // +0x130 (0x4c*4): targetObject pointer
    // +0x31c (199*4): desiredOffsetDistance? (float)
    // +0x318 (0xc6*4): distanceOffset? (float)
    // +0x324 (0xc9*4): close distance
    // +0x328 (0xca*4): far distance
    // +0x320 (200*4): currentDistance
    // +0x29c (0xa7*4): messageQueue pointer
    // +0x2bf (byte): useCollision flag

    if ((m_flags >> 19) & 1)  // bit 19: camera just activated
    {
        FUN_00794600(0);  // likely reset something
        m_flags &= 0xFFF7FFFF;  // clear bit 19
        FUN_008b7d60(m_collisionTarget, &m_position);  // set initial collision target
    }

    int state = m_state;
    m_lookAtTarget = m_lookAtTargetAlt;  // always update lookAt

    if (state == 0)
    {
        // No state change needed; keep lookAt as above
    }
    else if (state == 2)
    {
        // Active camera update with dynamic adjustment

        if ((m_flags >> 12) & 1)  // bit 12: some specific flag
        {
            FUN_006a8760(&m_someOffset, 0); // offset 0x107*4 = 0x41c
        }

        if (m_targetObject != nullptr)
        {
            (*(void (__thiscall**)(int, int))m_targetObject[0])(0x6f74af5b, 1); // call virtual at +0x44
        }

        int prevState = m_previousState;
        m_state = 1;  // transition to state 1 (post-update)
        m_desiredDistance = 0;

        // If previous state is not 1,2,3, compute new desired distance from focus
        if (prevState != 1 && prevState != 2 && prevState != 3)
        {
            m_desiredDistance = DAT_00d6a16c;  // default distance

            void* focus = getCameraFocus();
            float focusPosX = *(float*)(focus + 0x20); // low part of vector
            float focusPosY = *(float*)(focus + 0x28); // high part? Actually careful: The original reads as double?
            // The original reads: uVar1 = *(undefined8 *)(focus + 0x20); which is two floats (x,z?) then fStack_f4 = *(float*)(focus+0x28). Assumed layout: vec3 (x,y,z) as 8 bytes (double?) but likely it's 3 floats.
            // We'll simplify: assume focus->position is a Vector3 (3 floats).
            float focusX = *(float*)(focus + 0x20);
            float focusY = *(float*)(focus + 0x24);
            float focusZ = *(float*)(focus + 0x28);

            float elapsed = getDeltaTime(cameraIndex); // from param_2
            float t = elapsed;

            focus = getCameraFocus();
            float lookX = *(float*)(focus + 0x30);
            float lookY = *(float*)(focus + 0x34);
            float lookZ = *(float*)(focus + 0x38);

            void* focus3 = getCameraFocus();
            float velX = *(float*)(focus3 + 0x00);
            float velY = *(float*)(focus3 + 0x04);
            float velZ = *(float*)(focus3 + 0x08);

            if (t >= 0.0f)
            {
                // Positive delta: move toward target
                // Compute new position as weighted blend
                float newX = CAMERA_CONST_A - focusX;
                float newY = CAMERA_CONST_A - focusY;
                float newZ = CAMERA_CONST_A - focusZ;

                float coeff = (float)m_extraDistance + CAMERA_CONST_B;
                float computedX = velX * CAMERA_CONST_B + newX * coeff + lookX;
                float computedY = velY * CAMERA_CONST_B + newY * coeff + lookY;
                float computedZ = velZ * CAMERA_CONST_B + newZ * coeff + lookZ;
            }
            else
            {
                // Negative delta: move away
                m_desiredDistance = (int)(CAMERA_CONST_A - (float)m_desiredDistance);
                float coeff = (float)m_distanceOffset - CAMERA_CONST_B;
                float computedX = newX * coeff + lookX;  // newX from focus
                float computedY = newY * coeff + lookY;
                float computedZ = newZ * coeff + lookZ;
            }

            // Apply position via virtual call
            (*(void (__thiscall**)(CollisionCamera*, float*))m_vtable[7])(this, &computedX); // vtable+0x1c

            if (!m_useCollision)
            {
                // Compute adjusted position with different coefficients
                float adjX = velX * CAMERA_CONST_C + newX * CAMERA_CONST_D + lookX;
                float adjY = velY * CAMERA_CONST_C + newY * CAMERA_CONST_D + lookY;
                float adjZ = velZ * CAMERA_CONST_C + newZ * CAMERA_CONST_D + lookZ;

                // Raycast or shape cast parameters
                // (omit large stack allocations for brevity)
                // Call FUN_005425d0(rayStart, rayEnd, flags, ...)
                // Then FUN_009e69d0(...) for sphere test

                // After collision test, set currentDistance
                if (hitFraction == 0.0f)
                {
                    m_currentDistance = CAMERA_CONST_I;
                }
                else
                {
                    m_currentDistance = (int)((CAMERA_CONST_F - hitFraction) + CAMERA_CONST_G);
                }
            }
            else if (t >= 0.0f)
            {
                m_currentDistance = m_closeDistance;
            }
            else
            {
                m_currentDistance = m_farDistance;
            }
        }

        FUN_00470f80(&m_someTimer);  // update a timer at +0xb4
        FUN_00793840();               // global update function

        // Get current view ID from global interface
        int viewId = 0;
        if (*(int**)*(int*)(DAT_012233a0 + 4) != nullptr)
        {
            viewId = (*(int (__thiscall**)(void))(*(int*)*(int*)(DAT_012233a0 + 4) + 0xc))();
        }

        // Clear message queue if camera index matches view
        if (m_messageQueue != 0 && cameraIndex == viewId)
        {
            FUN_00402050(&m_messageQueue, 0);
        }

        return 1;
    }
    else if (state == 3)
    {
        m_state = 1;  // reset to state 1
        return 0;
    }

    return 0; // default (state 0)
}