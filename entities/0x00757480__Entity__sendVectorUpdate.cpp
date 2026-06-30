// FUNC_NAME: Entity::sendVectorUpdate
void __thiscall Entity::sendVectorUpdate(float* source, float* target) {
    float srcX = source[0];  // local_c
    float srcY = source[1];  // local_8
    float srcZ = source[2];  // local_4
    float dstX = target[0];  // local_18
    float dstY = target[1];  // local_14
    float dstZ = target[2];  // local_10

    int networkObj = *(int*)(this + 0xAC); // member pointer to network-related object
    unsigned int param7 = 0; // from networkObj+0x838
    unsigned int param6 = 0; // from networkObj+0x834
    if (networkObj != -0x828) { // sentinel for invalid/null pointer
        param7 = *(unsigned int*)(networkObj + 0x838);
        param6 = *(unsigned int*)(networkObj + 0x834);
    }

    // send a network message with source/destination vectors and control flags
    // constants: 0x40102 (flags?), 0x10001 (message type?), 1,0,0
    sendNetworkMessage(networkObj, &srcX, &dstX, 0x40102, 0x10001, param6, param7, 1, 0, 0);
}