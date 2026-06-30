// FUNC_NAME: RigidBody::interpolateState
void RigidBody::interpolateState(void* outputTransform)
{
    // in_EAX = this
    int iVar1 = *(int*)(*(int*)(*(int*)(this + 0x14) + 0x30) + 0x18); // Dereference chain to get some base transform?
    
    // Base position from iVar1 struct at offset 0x30 (pos), 0x34 (pos), 0x38 (pos)
    float baseX = *(float*)(iVar1 + 0x30);
    float baseY = *(float*)(iVar1 + 0x38);
    float baseZ; // Actually local_3c = baseY? Wait offsets: 0x30, 0x34, 0x38. So baseX, baseY, baseZ?
    // The code: local_40 = *(float*)(iVar1+0x30); local_38 = *(float*)(iVar1+0x38); local_3c = *(float*)(iVar1+0x34) + DAT_00e2b334;
    // So baseY from +0x34, baseZ from +0x38. So let's name:
    // basePosX = iVar1 + 0x30, basePosY = iVar1 + 0x34, basePosZ = iVar1 + 0x38.
    // But local_3c has addition of constant, so it's basePosY + upOffset?
    
    float basePosX = *(float*)(iVar1 + 0x30);
    float basePosZ = *(float*)(iVar1 + 0x38); // note: Z is likely third component
    float basePosY = *(float*)(iVar1 + 0x34) + DAT_00e2b334; // local_3c
    
    // Time delta: globalTime - objectTime
    float deltaTime = DAT_00e44564 - *(float*)(this + 0xb4);
    
    // Velocity or direction from this object at offsets 0x90, 0x94, 0x98, 0x9c
    float velX = *(float*)(this + 0x90);
    float velY = *(float*)(this + 0x94);
    float velZ = *(float*)(this + 0x98);
    float velW = *(float*)(this + 0x9c); // Possibly w component of quaternion or angular velocity?
    
    // Interpolated position
    float interpX = velX * deltaTime + basePosX;   // local_30
    float interpY = velY * deltaTime + basePosY;   // local_2c
    float interpZ = velZ * deltaTime + basePosZ;   // local_28
    float interpW = velW * deltaTime + DAT_00e2b1a4; // local_24
    
    // local_34 = DAT_00e2b1a4; (constant)
    float constantW = DAT_00e2b1a4; // local_34
    
    // local_20 = 1 (true) possibly indicating valid
    unsigned char valid = 1;
    
    // Prepare struct on stack: local_40 starts with basePosX, basePosY, basePosZ? Wait local_40 was set to basePosX, but then overwritten by interp values? Actually ordering:
    // local_40 = basePosX
    // local_3c = basePosY + constant
    // local_38 = basePosZ
    // local_34 = constantW
    // local_30 = interpX
    // local_2c = interpY
    // local_28 = interpZ
    // local_24 = interpW
    // local_20 = 1
    // Then call FUN_009e69d0(&local_40, outputTransform) — so it passes address of basePosX? But that's odd. Actually the struct starts at local_40 and contains interp values? The order of assignments: later assignments to local_30,2c,28,24 overwrite earlier ones? They are separate stack locals. So the struct passed is the first elements: local_40, local_3c, local_38, local_34, then local_30,2c,28,24, then local_20. That's a 5-float struct plus 1 byte? Or maybe it's a 3-vector followed by a quaternion? This is messy.
    
    // For clarity, we'll create a local struct and populate it then call the function.
    // Assuming the callee expects a transform struct.
    
    struct Transform {
        float posX;
        float posY;
        float posZ;
        float constant; // possibly w of quaternion or scale
        float interpX;
        float interpY;
        float interpZ;
        float interpW;
        unsigned char valid;
    } t;
    
    t.posX = basePosX;
    t.posY = basePosY; // local_3c already added constant
    t.posZ = basePosZ;
    t.constant = constantW;
    t.interpX = interpX;
    t.interpY = interpY;
    t.interpZ = interpZ;
    t.interpW = interpW;
    t.valid = valid;
    
    FUN_009e69d0(&t, outputTransform);
    return;
}