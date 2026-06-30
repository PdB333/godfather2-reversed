// FUNC_NAME: PersistObject::readProperties
void __thiscall PersistObject::readProperties(Stream *stream) {
    Property *prop;
    int fieldPtr;
    float val;
    int result;
    uint32_t uintVal;
    undefined4 *vec3;
    undefined4 x, y, z;
    float minVal, maxVal;

    stream->beginRead();
    stream->readHeader(0x57b9741); // magic/version

    while (!stream->isEnd()) {
        stream->advanceProperty();
        prop = stream->readProperty(); // returns pointer to property struct

        switch (prop->type) {
        case 0: // String property
            fieldPtr = this + 0x58;
            stream->readString(fieldPtr);
            stream->readStringHash(0x38523fc3, stream);
            stream->endString();
            break;
        case 1: // bool at offset 0x98
            fieldPtr = stream->readProperty();
            *(bool *)(this + 0x98) = *(int *)(fieldPtr + 8) != 0;
            break;
        case 2:  // uint32 at 0x9c
        case 0x3f: // ... many uint32 fields
        // Cases 2 through 0x3f (except where noted) store a single uint32 from prop->data
        #define STORE_UINT32(offset) case __COUNTER__: \
            fieldPtr = stream->readProperty(); \
            *(uint32_t *)(this + (offset)) = *(uint32_t *)(fieldPtr + 8); \
            break;
        // But to avoid giant macro, list individually:
        case 2: *(uint32_t*)(this+0x9c) = *(uint32_t*)(stream->readProperty()+8); break;
        case 3: *(uint32_t*)(this+0xa0) = *(uint32_t*)(stream->readProperty()+8); break;
        case 4: *(uint32_t*)(this+0xa4) = *(uint32_t*)(stream->readProperty()+8); break;
        case 5: *(uint32_t*)(this+0xa8) = *(uint32_t*)(stream->readProperty()+8); break;
        case 6: *(uint32_t*)(this+0xac) = *(uint32_t*)(stream->readProperty()+8); break;
        case 7: *(uint32_t*)(this+0xb0) = *(uint32_t*)(stream->readProperty()+8); break;
        case 8: *(uint32_t*)(this+0xb4) = *(uint32_t*)(stream->readProperty()+8); break;
        case 9: *(uint32_t*)(this+0xb8) = *(uint32_t*)(stream->readProperty()+8); break;
        case 10: *(uint32_t*)(this+0xbc) = *(uint32_t*)(stream->readProperty()+8); break;
        case 11: *(uint32_t*)(this+0xc0) = *(uint32_t*)(stream->readProperty()+8); break;
        case 12: *(uint32_t*)(this+0xc4) = *(uint32_t*)(stream->readProperty()+8); break;
        case 13: *(uint32_t*)(this+200) = *(uint32_t*)(stream->readProperty()+8); break; // offset 200 = 0xc8
        case 14: *(uint32_t*)(this+0xcc) = *(uint32_t*)(stream->readProperty()+8); break;
        case 15: *(uint32_t*)(this+0xd0) = *(uint32_t*)(stream->readProperty()+8); break;
        case 16: *(uint32_t*)(this+0xd4) = *(uint32_t*)(stream->readProperty()+8); break;
        case 17: *(uint32_t*)(this+0xd8) = *(uint32_t*)(stream->readProperty()+8); break;
        case 18: *(uint32_t*)(this+0xdc) = *(uint32_t*)(stream->readProperty()+8); break;
        case 19: *(uint32_t*)(this+0xe0) = *(uint32_t*)(stream->readProperty()+8); break;
        case 20: *(uint32_t*)(this+0xe4) = *(uint32_t*)(stream->readProperty()+8); break;
        case 21: *(uint32_t*)(this+0xe8) = *(uint32_t*)(stream->readProperty()+8); break;
        case 22: *(uint32_t*)(this+0xec) = *(uint32_t*)(stream->readProperty()+8); break;
        case 23: *(uint32_t*)(this+0xf0) = *(uint32_t*)(stream->readProperty()+8); break;
        case 24: *(uint32_t*)(this+0xf4) = *(uint32_t*)(stream->readProperty()+8); break;
        case 25: *(uint32_t*)(this+0xf8) = *(uint32_t*)(stream->readProperty()+8); break;
        case 26: *(uint32_t*)(this+0xfc) = *(uint32_t*)(stream->readProperty()+8); break;
        case 27: *(uint32_t*)(this+0x100) = *(uint32_t*)(stream->readProperty()+8); break;
        case 28: *(uint32_t*)(this+0x104) = *(uint32_t*)(stream->readProperty()+8); break;
        case 29: *(uint32_t*)(this+0x108) = *(uint32_t*)(stream->readProperty()+8); break;
        case 30: *(uint32_t*)(this+0x10c) = *(uint32_t*)(stream->readProperty()+8); break;
        case 31: *(uint32_t*)(this+0x110) = *(uint32_t*)(stream->readProperty()+8); break;
        case 32: *(uint32_t*)(this+0x114) = *(uint32_t*)(stream->readProperty()+8); break;
        case 33: *(uint32_t*)(this+0x118) = *(uint32_t*)(stream->readProperty()+8); break;
        case 34: *(uint32_t*)(this+0x11c) = *(uint32_t*)(stream->readProperty()+8); break;
        case 35: *(uint32_t*)(this+0x120) = *(uint32_t*)(stream->readProperty()+8); break;
        case 36: *(uint32_t*)(this+0x124) = *(uint32_t*)(stream->readProperty()+8); break;
        case 37: *(uint32_t*)(this+0x128) = *(uint32_t*)(stream->readProperty()+8); break;
        case 38: *(uint32_t*)(this+300) = *(uint32_t*)(stream->readProperty()+8); break; // offset 300 = 0x12c
        case 39: *(uint32_t*)(this+0x130) = *(uint32_t*)(stream->readProperty()+8); break;
        case 41: *(uint32_t*)(this+0x134) = *(uint32_t*)(stream->readProperty()+8); break;
        case 42: *(uint32_t*)(this+0x138) = *(uint32_t*)(stream->readProperty()+8); break;
        case 43: *(uint32_t*)(this+0x13c) = *(uint32_t*)(stream->readProperty()+8); break;
        case 44: *(uint32_t*)(this+0x140) = *(uint32_t*)(stream->readProperty()+8); break;
        case 45: // bool at 0x144
            fieldPtr = stream->readProperty();
            *(uint32_t*)(this+0x144) = (*(int*)(fieldPtr+8) != 0) ? 1 : 0;
            break;
        case 46: *(uint32_t*)(this+0x148) = *(uint32_t*)(stream->readProperty()+8); break;
        case 47: *(uint32_t*)(this+0x14c) = *(uint32_t*)(stream->readProperty()+8); break;
        case 48: // global flag
            fieldPtr = stream->readProperty();
            g_debugMode = *(int*)(fieldPtr+8) != 0;
            break;
        case 49: // global flag
            fieldPtr = stream->readProperty();
            g_someFlag = *(int*)(fieldPtr+8) != 0;
            break;
        case 50: *(uint32_t*)(this+0x150) = *(uint32_t*)(stream->readProperty()+8); break;
        case 51: *(uint32_t*)(this+0x154) = *(uint32_t*)(stream->readProperty()+8); break;
        case 52: *(uint32_t*)(this+0x158) = *(uint32_t*)(stream->readProperty()+8); break;
        case 53: *(uint32_t*)(this+0x15c) = *(uint32_t*)(stream->readProperty()+8); break;
        case 54: *(uint32_t*)(this+0x184) = *(uint32_t*)(stream->readProperty()+8); break;
        case 55: *(uint32_t*)(this+0x160) = *(uint32_t*)(stream->readProperty()+8); break;
        case 56: *(uint32_t*)(this+0x164) = *(uint32_t*)(stream->readProperty()+8); break;
        case 57: *(uint32_t*)(this+0x168) = *(uint32_t*)(stream->readProperty()+8); break;
        case 58: *(uint32_t*)(this+0x16c) = *(uint32_t*)(stream->readProperty()+8); break;
        case 59: *(uint32_t*)(this+0x170) = *(uint32_t*)(stream->readProperty()+8); break;
        case 60: *(uint32_t*)(this+0x174) = *(uint32_t*)(stream->readProperty()+8); break;
        case 61: *(uint32_t*)(this+0x178) = *(uint32_t*)(stream->readProperty()+8); break;
        case 62: *(uint32_t*)(this+0x17c) = *(uint32_t*)(stream->readProperty()+8); break;
        case 63: *(uint32_t*)(this+0x180) = *(uint32_t*)(stream->readProperty()+8); break;
        case 64: // vec3
            stream->readProperty(); // discard
            vec3 = (undefined4*)stream->readPropertyArray();
            *(undefined4*)(this+0x1a0) = vec3[0];
            *(undefined4*)(this+0x1a4) = vec3[1];
            *(undefined4*)(this+0x1a8) = vec3[2];
            break;
        case 65: *(uint32_t*)(this+0x68) = *(uint32_t*)(stream->readProperty()+8); break;
        case 66: *(uint32_t*)(this+0x70) = *(uint32_t*)(stream->readProperty()+8); break;
        case 67: *(uint32_t*)(this+0x6c) = *(uint32_t*)(stream->readProperty()+8); break;
        case 68: *(uint32_t*)(this+0x74) = *(uint32_t*)(stream->readProperty()+8); break;
        case 69: *(uint32_t*)(this+0x78) = *(uint32_t*)(stream->readProperty()+8); break;
        case 70: // clamped float at 0x7c (min 0, max from global)
            fieldPtr = stream->readProperty();
            val = *(float*)(fieldPtr+8);
            if (val > 0.0f) {
                fieldPtr = stream->readProperty();
                minVal = g_floatConstant; // _DAT_00d5780c
                if (*(float*)(fieldPtr+8) < minVal) {
                    fieldPtr = stream->readProperty();
                    minVal = *(float*)(fieldPtr+8);
                }
            } else {
                minVal = 0.0f;
            }
            *(float*)(this+0x7c) = minVal;
            break;
        case 71: // clamped float at 0x80 (max from global)
            fieldPtr = stream->readProperty();
            val = g_floatConstant;
            if (val < *(float*)(fieldPtr+8)) {
                fieldPtr = stream->readProperty();
                val = *(float*)(fieldPtr+8);
            }
            *(float*)(this+0x80) = val;
            break;
        case 72: // clamped float at 0x84 (min 0, max from global)
            fieldPtr = stream->readProperty();
            if (*(float*)(fieldPtr+8) > 0.0f) {
                fieldPtr = stream->readProperty();
                minVal = g_floatConstant;
                if (*(float*)(fieldPtr+8) < minVal) {
                    fieldPtr = stream->readProperty();
                    minVal = *(float*)(fieldPtr+8);
                }
            } else {
                minVal = 0.0f;
            }
            *(float*)(this+0x84) = minVal;
            break;
        case 73: // uint32 at 0x88 (conditional: if positive float)
            fieldPtr = stream->readProperty();
            uintVal = 0;
            if (*(float*)(fieldPtr+8) > 0.0f) {
                fieldPtr = stream->readProperty();
                uintVal = *(uint32_t*)(fieldPtr+8);
            }
            *(uint32_t*)(this+0x88) = uintVal;
            break;
        case 74: // uint32 at 0x8c (conditional: if positive float)
            fieldPtr = stream->readProperty();
            uintVal = 0;
            if (*(float*)(fieldPtr+8) > 0.0f) {
                fieldPtr = stream->readProperty();
                uintVal = *(uint32_t*)(fieldPtr+8);
            }
            *(uint32_t*)(this+0x8c) = uintVal;
            break;
        case 75: *(uint32_t*)(this+0x1ac) = *(uint32_t*)(stream->readProperty()+8); break;
        case 76: // uint32 at 0x190 (conditional)
            fieldPtr = stream->readProperty();
            uintVal = 0;
            if (*(float*)(fieldPtr+8) > 0.0f) {
                fieldPtr = stream->readProperty();
                uintVal = *(uint32_t*)(fieldPtr+8);
            }
            *(uint32_t*)(this+0x190) = uintVal;
            break;
        case 77: // uint32 at 0x194 (conditional)
            fieldPtr = stream->readProperty();
            uintVal = 0;
            if (*(float*)(fieldPtr+8) > 0.0f) {
                fieldPtr = stream->readProperty();
                uintVal = *(uint32_t*)(fieldPtr+8);
            }
            *(uint32_t*)(this+0x194) = uintVal;
            break;
        case 78: // uint32 at 0x198 (conditional)
            fieldPtr = stream->readProperty();
            uintVal = 0;
            if (*(float*)(fieldPtr+8) > 0.0f) {
                fieldPtr = stream->readProperty();
                uintVal = *(uint32_t*)(fieldPtr+8);
            }
            *(uint32_t*)(this+0x198) = uintVal;
            break;
        case 79: // uint32 at 0x19c (conditional)
            fieldPtr = stream->readProperty();
            uintVal = 0;
            if (*(float*)(fieldPtr+8) > 0.0f) {
                fieldPtr = stream->readProperty();
                uintVal = *(uint32_t*)(fieldPtr+8);
            }
            *(uint32_t*)(this+0x19c) = uintVal;
            break;
        }
        stream->endProperty();
    }
}