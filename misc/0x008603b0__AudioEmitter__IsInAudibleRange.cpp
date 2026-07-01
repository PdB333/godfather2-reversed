// FUNC_NAME: AudioEmitter::IsInAudibleRange
float* __fastcall AudioEmitter::IsInAudibleRange() {
    // Get listener position from the audio system
    int listenerData = GetListenerPositionData();
    float* listenerPos = (float*)(listenerData + 0x30); // listener position (x,y,z at +0x30,+0x34,+0x38)

    // Check if sound is enabled; field_0xff8 might be a minimum audible range threshold
    if (g_soundEnabled < *(float*)(this + 0xff8)) {
        // Return pointer with low byte cleared (false flag)
        return (float*)((uint)listenerPos & 0xFFFFFF00);
    }

    // Compute maximum audible range: max(innerRange, outerRange) + baseRange
    float innerRange = *(float*)(this + 0xfa0);  // +0xfa0: inner range
    float outerRange = *(float*)(this + 0xfa4);  // +0xfa4: outer range
    float baseRange = *(float*)(this + 0xff8);   // +0xff8: base range (same as above?)
    float maxRange = (innerRange > outerRange ? innerRange : outerRange) + baseRange;

    // Compute squared distance from listener to this sound source
    float dx = listenerPos[0] - *(float*)(this + 0xffc);  // +0xffc: source x
    float dy = listenerPos[1] - *(float*)(this + 0x1000); // +0x1000: source y
    float dz = listenerPos[2] - *(float*)(this + 0x1004); // +0x1004: source z
    float distSq = dx*dx + dy*dy + dz*dz;

    if (distSq < maxRange * maxRange) {
        // Within range: return pointer with low byte set (true flag)
        return (float*)((uint)listenerPos | 1);
    } else {
        // Outside range: return pointer with low byte cleared
        return (float*)((uint)listenerPos & 0xFFFFFF00);
    }
}