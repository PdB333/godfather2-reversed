// FUNC_NAME: Entity::processGameEvent
void __thiscall Entity::processGameEvent(Entity* this, EventMessage* message)
{
    int eventId;
    float pos1[3];
    float pos2[3];
    float delta[3];
    float outVector;

    eventId = message->getType(); // vtable call
    if (eventId == 0x27a0f69c) {
        int state = *(int*)(this + 0x58);
        if (state != 0 && state != 0x48) {
            int param = (state == 0) ? 0 : (state - 0x48);
            // compute positions based on current state and some data at +0x54
            getTransformFromState(&pos1, &pos2, *(int*)(this + 0x54), param); // FUN_007c3900
            // apply orientation/offset with global constant _DAT_00e5190c
            applyOrientation(&pos1, &pos2, 1, _DAT_00e5190c, 0); // FUN_00755410
        }
    }
    else if (eventId == 0x485311a7) {
        int state = *(int*)(this + 0x58);
        if (state != 0 && state != 0x48) {
            int param = (state == 0) ? 0 : (state - 0x48);
            setAnimationState(param); // FUN_0075b920
            Entity* localPlayer = getLocalPlayer(); // FUN_00471610
            getPosition(&pos1); // FUN_007490b0
            // compute vector from this entity to local player
            delta[0] = pos1[0] - *(float*)(localPlayer + 0x30);
            delta[1] = pos1[1] - *(float*)(localPlayer + 0x34);
            delta[2] = pos1[2] - *(float*)(localPlayer + 0x38);
            normalizeVector(delta); // FUN_0075b4f0
        }
        playSound(DAT_00d5c454); // FUN_0075b540
    }
}