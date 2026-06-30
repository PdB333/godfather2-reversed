// FUNC_NAME: ParameterReader::readFromStream
void __thiscall ParameterReader::readFromStream(int this, int streamHandle) {
    char hasMore;
    int stream;
    int paramPtr;
    int tokenType;
    int subObjBase;
    int subObjPtr;
    float clampedValue;
    int tmp;
    int *vecPtr;
    int vecX, vecY, vecZ;

    // Initialize the parameter stream with the given handle
    stream = streamHandle;
    paramStreamInit(stream);
    paramStreamBegin(stream, 0x57b9741); // Begin reading with class identifier

    hasMore = paramStreamHasMore();
    while (hasMore == '\0') { // while there are more parameters
        paramStreamAdvance();
        tokenType = paramStreamGetTokenType();
        switch(tokenType) {
        case 0: // Sub-object
            subObjBase = this + 0x58; // +0x58: pointer to sub-object (e.g., child component)
            subObjPtr = subObjBase;
            paramStreamAdvance(subObjBase); // Push this pointer for sub-object parsing
            paramStreamReadSubObject(subObjPtr); // Parse sub-object
            // Get a specific parameter from sub-object by index 0
            tmp = paramStreamGetParameterByIndex(subObjBase, 0);
            // Set a parameter in the main object using a hash (0x38523fc3)
            paramStreamSetParameter(0x38523fc3, &stream);
            stream = paramStreamCommitSubObject(); // Commit and get result?
            break;
        case 1: // Bool
            paramPtr = paramStreamAdvance();
            *(bool *)(this + 0x98) = *(int *)(paramPtr + 8) != 0; // +0x98: someBool
            break;
        case 2: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x9c) = *(int *)(paramPtr + 8); // +0x9c: field9c
            break;
        case 3: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xa0) = *(int *)(paramPtr + 8); // +0xa0: fieldA0
            break;
        case 4: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xa4) = *(int *)(paramPtr + 8); // +0xa4: fieldA4
            break;
        case 5: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xa8) = *(int *)(paramPtr + 8); // +0xa8: fieldA8
            break;
        case 6: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xac) = *(int *)(paramPtr + 8); // +0xac: fieldAC
            break;
        case 7: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xb0) = *(int *)(paramPtr + 8); // +0xb0: fieldB0
            break;
        case 8: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xb4) = *(int *)(paramPtr + 8); // +0xb4: fieldB4
            break;
        case 9: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xb8) = *(int *)(paramPtr + 8); // +0xb8: fieldB8
            break;
        case 0xa: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xbc) = *(int *)(paramPtr + 8); // +0xbc: fieldBC
            break;
        case 0xb: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xc0) = *(int *)(paramPtr + 8); // +0xc0: fieldC0
            break;
        case 0xc: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xc4) = *(int *)(paramPtr + 8); // +0xc4: fieldC4
            break;
        case 0xd: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 200) = *(int *)(paramPtr + 8); // +0xc8: fieldC8
            break;
        case 0xe: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xcc) = *(int *)(paramPtr + 8); // +0xcc: fieldCC
            break;
        case 0xf: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xd0) = *(int *)(paramPtr + 8); // +0xd0: fieldD0
            break;
        case 0x10: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xd4) = *(int *)(paramPtr + 8); // +0xd4: fieldD4
            break;
        case 0x11: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xd8) = *(int *)(paramPtr + 8); // +0xd8: fieldD8
            break;
        case 0x12: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xdc) = *(int *)(paramPtr + 8); // +0xdc: fieldDC
            break;
        case 0x13: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xe0) = *(int *)(paramPtr + 8); // +0xe0: fieldE0
            break;
        case 0x14: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xe4) = *(int *)(paramPtr + 8); // +0xe4: fieldE4
            break;
        case 0x15: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xe8) = *(int *)(paramPtr + 8); // +0xe8: fieldE8
            break;
        case 0x16: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xec) = *(int *)(paramPtr + 8); // +0xec: fieldEC
            break;
        case 0x17: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xf0) = *(int *)(paramPtr + 8); // +0xf0: fieldF0
            break;
        case 0x18: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xf4) = *(int *)(paramPtr + 8); // +0xf4: fieldF4
            break;
        case 0x19: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xf8) = *(int *)(paramPtr + 8); // +0xf8: fieldF8
            break;
        case 0x1a: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0xfc) = *(int *)(paramPtr + 8); // +0xfc: fieldFC
            break;
        case 0x1b: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x100) = *(int *)(paramPtr + 8); // +0x100: field100
            break;
        case 0x1c: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x104) = *(int *)(paramPtr + 8); // +0x104: field104
            break;
        case 0x1d: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x108) = *(int *)(paramPtr + 8); // +0x108: field108
            break;
        case 0x1e: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x10c) = *(int *)(paramPtr + 8); // +0x10c: field10C
            break;
        case 0x1f: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x110) = *(int *)(paramPtr + 8); // +0x110: field110
            break;
        case 0x20: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x114) = *(int *)(paramPtr + 8); // +0x114: field114
            break;
        case 0x21: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x118) = *(int *)(paramPtr + 8); // +0x118: field118
            break;
        case 0x22: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x11c) = *(int *)(paramPtr + 8); // +0x11c: field11C
            break;
        case 0x23: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x120) = *(int *)(paramPtr + 8); // +0x120: field120
            break;
        case 0x24: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x124) = *(int *)(paramPtr + 8); // +0x124: field124
            break;
        case 0x25: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x128) = *(int *)(paramPtr + 8); // +0x128: field128
            break;
        case 0x26: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 300) = *(int *)(paramPtr + 8); // +0x12c: field12C
            break;
        case 0x27: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x130) = *(int *)(paramPtr + 8); // +0x130: field130
            break;
        case 0x29: // Int32 (note: skipping 0x28)
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x134) = *(int *)(paramPtr + 8); // +0x134: field134
            break;
        case 0x2a: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x138) = *(int *)(paramPtr + 8); // +0x138: field138
            break;
        case 0x2b: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x13c) = *(int *)(paramPtr + 8); // +0x13c: field13C
            break;
        case 0x2c: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x140) = *(int *)(paramPtr + 8); // +0x140: field140
            break;
        case 0x2d: // Bool
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x144) = (uint)(*(int *)(paramPtr + 8) != 0); // +0x144: field144 (bool)
            break;
        case 0x2e: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x148) = *(int *)(paramPtr + 8); // +0x148: field148
            break;
        case 0x2f: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x14c) = *(int *)(paramPtr + 8); // +0x14c: field14C
            break;
        case 0x30: // Bool + global
            paramPtr = paramStreamAdvance();
            g_globalBool1 = *(int *)(paramPtr + 8) != 0; // global bool at 0x00e50fb4
            break;
        case 0x31: // Bool + global
            paramPtr = paramStreamAdvance();
            g_globalBool2 = *(int *)(paramPtr + 8) != 0; // global bool at 0x0112a7a6
            break;
        case 0x32: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x150) = *(int *)(paramPtr + 8); // +0x150: field150
            break;
        case 0x33: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x154) = *(int *)(paramPtr + 8); // +0x154: field154
            break;
        case 0x34: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x158) = *(int *)(paramPtr + 8); // +0x158: field158
            break;
        case 0x35: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x15c) = *(int *)(paramPtr + 8); // +0x15c: field15C
            break;
        case 0x36: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x184) = *(int *)(paramPtr + 8); // +0x184: field184 (non-contiguous)
            break;
        case 0x37: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x160) = *(int *)(paramPtr + 8); // +0x160: field160
            break;
        case 0x38: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x164) = *(int *)(paramPtr + 8); // +0x164: field164
            break;
        case 0x39: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x168) = *(int *)(paramPtr + 8); // +0x168: field168
            break;
        case 0x3a: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x16c) = *(int *)(paramPtr + 8); // +0x16c: field16C
            break;
        case 0x3b: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x170) = *(int *)(paramPtr + 8); // +0x170: field170
            break;
        case 0x3c: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x174) = *(int *)(paramPtr + 8); // +0x174: field174
            break;
        case 0x3d: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x178) = *(int *)(paramPtr + 8); // +0x178: field178
            break;
        case 0x3e: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x17c) = *(int *)(paramPtr + 8); // +0x17c: field17C
            break;
        case 0x3f: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x180) = *(int *)(paramPtr + 8); // +0x180: field180
            break;
        case 0x40: // Vector3
            paramStreamAdvance();
            vecPtr = paramStreamReadVector3();
            vecX = *vecPtr;
            vecY = *(vecPtr + 1);
            vecZ = *(vecPtr + 2);
            *(int *)(this + 0x1a0) = vecX; // +0x1a0: vector3.x
            *(int *)(this + 0x1a4) = vecY; // +0x1a4: vector3.y
            *(int *)(this + 0x1a8) = vecZ; // +0x1a8: vector3.z
            break;
        case 0x41: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x68) = *(int *)(paramPtr + 8); // +0x68: field68
            break;
        case 0x42: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x70) = *(int *)(paramPtr + 8); // +0x70: field70
            break;
        case 0x43: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x6c) = *(int *)(paramPtr + 8); // +0x6c: field6C
            break;
        case 0x44: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x74) = *(int *)(paramPtr + 8); // +0x74: field74
            break;
        case 0x45: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x78) = *(int *)(paramPtr + 8); // +0x78: field78
            break;
        case 0x46: // Float with clamp to max
            paramPtr = paramStreamAdvance();
            clampedValue = 0.0f;
            if (0.0f < *(float *)(paramPtr + 8)) { // first value is positive
                paramPtr = paramStreamAdvance();
                clampedValue = g_maxFloat; // global float constant (0x00d5780c)
                if (*(float *)(paramPtr + 8) < g_maxFloat) { // second value is less than max
                    paramPtr = paramStreamAdvance();
                    clampedValue = *(float *)(paramPtr + 8); // third value becomes result
                }
            }
            *(float *)(this + 0x7c) = clampedValue; // +0x7c: field7C (float)
            break;
        case 0x47: // Float with clamp to min
            paramPtr = paramStreamAdvance();
            clampedValue = g_maxFloat;
            if (g_maxFloat < *(float *)(paramPtr + 8)) { // first value greater than max
                paramPtr = paramStreamAdvance();
                clampedValue = *(float *)(paramPtr + 8); // second value becomes result
            }
            *(float *)(this + 0x80) = clampedValue; // +0x80: field80 (float)
            break;
        case 0x48: // Float with clamp to max (similar to 0x46)
            paramPtr = paramStreamAdvance();
            clampedValue = 0.0f;
            if (0.0f < *(float *)(paramPtr + 8)) {
                paramPtr = paramStreamAdvance();
                clampedValue = g_maxFloat;
                if (*(float *)(paramPtr + 8) < g_maxFloat) {
                    paramPtr = paramStreamAdvance();
                    clampedValue = *(float *)(paramPtr + 8);
                }
            }
            *(float *)(this + 0x84) = clampedValue; // +0x84: field84 (float)
            break;
        case 0x49: // Float/Int with conditional (clamp positive)
            paramPtr = paramStreamAdvance();
            tmp = 0;
            if (0.0f < *(float *)(paramPtr + 8)) { // first positive
                paramPtr = paramStreamAdvance();
                tmp = *(int *)(paramPtr + 8);
            }
            *(int *)(this + 0x88) = tmp; // +0x88: field88 (int)
            break;
        case 0x4a: // Same as 0x49
            paramPtr = paramStreamAdvance();
            tmp = 0;
            if (0.0f < *(float *)(paramPtr + 8)) {
                paramPtr = paramStreamAdvance();
                tmp = *(int *)(paramPtr + 8);
            }
            *(int *)(this + 0x8c) = tmp; // +0x8c: field8C (int)
            break;
        case 0x4b: // Int32
            paramPtr = paramStreamAdvance();
            *(int *)(this + 0x1ac) = *(int *)(paramPtr + 8); // +0x1ac: field1AC
            break;
        case 0x4c: // Float/Int with conditional
            paramPtr = paramStreamAdvance();
            tmp = 0;
            if (0.0f < *(float *)(paramPtr + 8)) {
                paramPtr = paramStreamAdvance();
                tmp = *(int *)(paramPtr + 8);
            }
            *(int *)(this + 400) = tmp; // +0x190: field190 (int)
            break;
        case 0x4d: // Float/Int with conditional
            paramPtr = paramStreamAdvance();
            tmp = 0;
            if (0.0f < *(float *)(paramPtr + 8)) {
                paramPtr = paramStreamAdvance();
                tmp = *(int *)(paramPtr + 8);
            }
            *(int *)(this + 0x194) = tmp; // +0x194: field194
            break;
        case 0x4e: // Float/Int with conditional
            paramPtr = paramStreamAdvance();
            tmp = 0;
            if (0.0f < *(float *)(paramPtr + 8)) {
                paramPtr = paramStreamAdvance();
                tmp = *(int *)(paramPtr + 8);
            }
            *(int *)(this + 0x198) = tmp; // +0x198: field198
            break;
        case 0x4f: // Float/Int with conditional
            paramPtr = paramStreamAdvance();
            tmp = 0;
            if (0.0f < *(float *)(paramPtr + 8)) {
                paramPtr = paramStreamAdvance();
                tmp = *(int *)(paramPtr + 8);
            }
            *(int *)(this + 0x19c) = tmp; // +0x19c: field19C
            break;
        }
        paramStreamNext();
        hasMore = paramStreamHasMore();
    }
    return;
}