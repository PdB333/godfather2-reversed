// FUNC_NAME: Sentient::checkLineOfSight
// Address: 0x007e1950
// Role: Checks if this sentient has line-of-sight to another object, using visibility check, object vtable, and geometric dot product.

bool __thiscall Sentient::checkLineOfSight(int thisPtr, int* targetObject)
{
    int bodyPtr = *(int*)(thisPtr + 0x58);        // +0x58: pointer to Body component
    char visible = isTargetVisible(targetObject, *(int*)(bodyPtr + 0x1f68)); // 0x1f68: some ID/token for visibility query
    if (visible) {
        visible = (*(code**)(*targetObject + 0x150))(bodyPtr); // vtable call: targetObject->canBeSeen(bodyPtr)
        if (visible) {
            int tr1 = getWorldTransform();        // returns pointer to transform containing position at +0x30
            int tr2 = getWorldTransform();        // another entity transform
            float dx = *(float*)(tr2 + 0x30) - *(float*)(tr1 + 0x30);
            float dy = *(float*)(tr2 + 0x34) - *(float*)(tr1 + 0x34);
            float dz = *(float*)(tr2 + 0x38) - *(float*)(tr1 + 0x38);
            int tr3 = getWorldTransform();        // own transform, direction stored at +0x20
            float dirX = *(float*)(tr3 + 0x20);
            float dirY = *(float*)(tr3 + 0x24);
            float dirZ = *(float*)(tr3 + 0x28);
            float dot = dirX*dx + dirY*dy + dirZ*dz;
            if (g_visibilityDotThreshold < dot) { // global threshold, dot must be > this value
                int result = performSkillCheck(9); // 9 = skill type (e.g., stealth, perception?)
                return result == 0;
            }
        }
    }
    return false;
}