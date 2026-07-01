// FUNC_NAME: GodfatherGameManager::spawnProjectileEffect
void __thiscall GodfatherGameManager::spawnProjectileEffect(int *this, float duration, uint type, int sourceObject, int targetObject, char isImmediate)
{
    int iVar1;
    float10 currentTime;
    // Local smart pointer-like variables for source and target transforms.
    int local_44; // smart pointer to source transform
    int local_3c; // smart pointer to target transform
    undefined4 local_38;
    undefined8 uStack_34; // source position (x,y,z) and w? (8 bytes = two floats? Actually 8 bytes could be two ints or a float4? In x86, undefined8 is 8 bytes, likely two floats or one double. But given offsets +0x30 and +0x38, it's likely a vector3+? Actually offset +0x30 is 48 bytes, typical size of transform? Might be position (x,y,z) and a quaternion? But here they copy 8 bytes from +0x30 and 4 bytes from +0x38 => total 12 byte? Actually they copy undefined8 from +0x30 (8 bytes) and undefined4 from +0x38 (4 bytes), so 12 bytes. Could be position (float3) and a float.
    undefined4 uStack_20;
    undefined8 uStack_28;
    undefined4 uStack_2c;
    // Flags and other locals
    uint uStack_c;
    float fStack_1c;
    undefined4 uStack_18;
    undefined4 uStack_8;
    uint uStack_4;
    undefined4 uStack_10; // result type (6 or 2)
    undefined1 auStack_48[4];
    
    currentTime = (float10)(**(code **)(*this + 0xc0))(); // virtual function at vtable+0xc0: getCurrentTime()
    if (currentTime > 0.0f) {
        if (duration < 0.0f) {
            duration = 0.0f;
        }
        // Create effect data (likely initializes a structure for the projectile)
        FUN_0084dd20();
        uStack_c = (uint)this[0x1ba] >> 2; // Get some type/ID from a field at offset 0x6E8 (0x1ba*4)
        fStack_1c = duration;
        uStack_18 = type;
        uStack_8 = DAT_01205224;
        if (isImmediate != '\0') {
            uStack_4 = uStack_4 | 8; // Set flag 8
        }
        if (sourceObject == 0) {
            // No source object: use default player object (maybe the calling object's owner?)
            iVar1 = FUN_00471610(); // presumably getCurrentPlayer()
            uStack_28 = *(undefined8 *)(iVar1 + 0x30);
            uStack_20 = *(undefined4 *)(iVar1 + 0x38);
            iVar1 = FUN_00471610(); // again? Maybe a second object (target?)
            uStack_34 = *(undefined8 *)(iVar1 + 0x30);
            uStack_2c = *(undefined4 *)(iVar1 + 0x38);
            // Release any previously held smart pointers
            if (local_44 != 0) {
                FUN_004daf90(&local_44);
                local_44 = 0;
            }
            if (local_3c != 0) {
                FUN_004daf90(&local_3c);
                local_3c = 0;
            }
        }
        else {
            // Use the provided source object's transform (at sourceObject+0x48)
            iVar1 = FUN_00471610();
            uStack_28 = *(undefined8 *)(iVar1 + 0x30);
            uStack_20 = *(undefined4 *)(iVar1 + 0x38);
            iVar1 = FUN_00471610();
            uStack_34 = *(undefined8 *)(iVar1 + 0x30);
            uStack_2c = *(undefined4 *)(iVar1 + 0x38);
            // Set up source transform smart pointer from sourceObject+0x48
            iVar1 = sourceObject + 0x48;
            if (local_3c != iVar1) {
                if (local_3c != 0) {
                    FUN_004daf90(&local_3c);
                }
                local_3c = iVar1;
                if (iVar1 != 0) {
                    local_38 = *(undefined4 *)(sourceObject + 0x4c);
                    *(int **)(sourceObject + 0x4c) = &local_3c;
                }
            }
            // Set up target transform smart pointer (same as source? Actually copies local_3c to local_44)
            iVar1 = local_3c;
            if (local_44 != local_3c) {
                if (local_44 != 0) {
                    FUN_004daf90(&local_44);
                }
                local_44 = iVar1;
                if (iVar1 != 0) {
                    uStack_40 = *(undefined4 *)(iVar1 + 4);
                    *(int **)(iVar1 + 4) = &local_44;
                }
            }
            // Process the target object if provided
            if (targetObject != 0) {
                FUN_0044b210(targetObject);
            }
        }
        // Determine if we should use quick (2) or normal (6) completion type
        currentTime = (float10)(**(code **)(*this + 0xc0))(); // get current time again
        uStack_10 = 6;
        if (duration <= currentTime) {
            uStack_10 = 2;
        }
        // Log the effect creation (log channel at DAT_0112dd94, name from this+0x0f)
        FUN_00408bb0(&DAT_0112dd94, this + 0xf, auStack_48, 0);
        // Release smart pointers
        if (local_3c != 0) {
            FUN_004daf90(&local_3c);
        }
        if (local_44 != 0) {
            FUN_004daf90(&local_44);
        }
    }
    return;
}