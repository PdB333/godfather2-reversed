// FUNC_NAME: PhysicsObject::sweepAndCheck
// Address: 0x00559780
// Role: Performs a collision sweep with an optional filter callback. If the filter returns nonzero, applies the sweep and outputs a status byte.

typedef unsigned int (__thiscall *CollisionFilter)(void *unk, float *startPos, unsigned int extra, int param);
typedef unsigned int (__thiscall *PostSweepFunc)(char *outByte, float *data, int info);

extern void __cdecl sweepHelper(void); // FUN_00557e20

undefined1 * __thiscall PhysicsObject::sweepAndCheck(PhysicsObject *this, undefined1 *outResult, float *sweepData, int collisionInfo)
{
    CollisionFilter filter;
    unsigned int filterResult;
    char tempByte;
    float startPos[4];
    float endPos[4];
    float extra1, extra2;

    filter = (CollisionFilter)this->field_0x10; // +0x10: filter callback function pointer
    *outResult = 0;
    this->field_0x0E = 0; // +0x0E: flag/reset

    if (filter != (CollisionFilter)0) {
        // Construct start and end positions by adding sweep offsets to this object's position
        startPos[0] = (float)this->posX + sweepData[0];
        startPos[1] = (float)this->posY + sweepData[1];
        startPos[2] = (float)this->posZ + sweepData[2];
        startPos[3] = (float)this->posW + sweepData[3];

        endPos[0] = (float)this->posX + sweepData[4];
        endPos[1] = (float)this->posY + sweepData[5];
        endPos[2] = (float)this->posZ + sweepData[6];
        endPos[3] = (float)this->posW + sweepData[7];

        extra1 = sweepData[8];
        extra2 = sweepData[9];

        filterResult = filter(this->field_0x0D, startPos, *(unsigned int *)(collisionInfo + 0x10), this->field_0x11);
        this->field_0x0E = ~filterResult;
        if (filterResult == 0) {
            goto LAB_005598a0; // filter rejected, skip sweep
        }
    }

    sweepHelper(); // Global sweep processing

    // Virtual method at vtable+0x20 (index 8); returns an unsigned int
    PostSweepFunc vfunc = (PostSweepFunc)((void ***)this)[0][8];
    unsigned int virtualResult = vfunc(&tempByte, sweepData, collisionInfo);
    *outResult = (char)(virtualResult >> 0x18);

LAB_005598a0:
    this->field_0x0E = 0;
    return outResult;
}