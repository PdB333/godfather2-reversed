// FUNC_NAME: BoneTransformData::loadFromStream
void __thiscall BoneTransformData::loadFromStream(int thisPtr, void* stream) {
    // EARS binary stream read functions
    beginChunk(stream);
    setChunkSignature(stream, 0xED173A59); // bone transform chunk signature
    
    while (!isEndOfChunk(stream)) {
        advanceStream(stream); // skip to next element
        int tagType = getCurrentTag(stream);
        
        switch(tagType) {
            case 0: // bone position X or similar
                advanceStream(stream);
                *(float*)(thisPtr + 0x50) = readFloat(stream); // m_position[0]
                break;
            case 1:
                advanceStream(stream);
                *(float*)(thisPtr + 0x58) = readFloat(stream); // m_position[1]
                break;
            case 2:
                advanceStream(stream);
                *(float*)(thisPtr + 0x60) = readFloat(stream); // m_position[2]
                break;
            case 3:
                advanceStream(stream);
                *(float*)(thisPtr + 0x68) = readFloat(stream); // m_position[3]
                break;
            case 4:
                advanceStream(stream);
                *(float*)(thisPtr + 0x70) = readFloat(stream); // m_position[4]
                break;
            case 5:
                advanceStream(stream);
                *(float*)(thisPtr + 0x78) = readFloat(stream); // m_position[5]
                break;
            case 6: // primary rotation
                if (*(int*)(thisPtr + 0xD4) != 0) {
                    disablePhysicsBody(thisPtr + 0xD4);
                    disablePhysicsConstraint(thisPtr + 0xD4);
                }
                advanceStream(stream);
                float* quat = readQuaternion(stream);
                *(float*)(thisPtr + 0xB4) = quat[0]; // m_rotation.x
                *(float*)(thisPtr + 0xB8) = quat[1]; // m_rotation.y
                *(float*)(thisPtr + 0xBC) = quat[2]; // m_rotation.z
                *(float*)(thisPtr + 0xC0) = quat[3]; // m_rotation.w
                break;
            case 7: // secondary rotation (inverse or additive)
                if (*(int*)(thisPtr + 0xD8) != 0) {
                    disablePhysicsBody(thisPtr + 0xD8);
                    disablePhysicsConstraint(thisPtr + 0xD8);
                }
                advanceStream(stream);
                float* quat2 = readQuaternion(stream);
                *(float*)(thisPtr + 0xC4) = quat2[0]; // m_secondaryRotation.x
                *(float*)(thisPtr + 0xC8) = quat2[1]; // m_secondaryRotation.y
                *(float*)(thisPtr + 0xCC) = quat2[2]; // m_secondaryRotation.z
                *(float*)(thisPtr + 0xD0) = quat2[3]; // m_secondaryRotation.w
                break;
            case 8: // bone index or object reference
                {
                    int obj = readNextObject(stream);
                    *(int*)(thisPtr + 0x84) = *(int*)(obj + 8); // assume handle at +8
                }
                break;
            case 9: // some sub-struct
                {
                    int subStructPtr = thisPtr + 0x88;
                    readRawData(subStructPtr);
                    readSubObject(subStructPtr);
                }
                break;
            case 10: // another reference
                {
                    int obj2 = readNextObject(stream);
                    *(int*)(thisPtr + 0x94) = *(int*)(obj2 + 8);
                }
                break;
            case 11: // scale component X
                {
                    int scaleObj = readNextObject(stream);
                    *(float*)(thisPtr + 0x98) = *(float*)(scaleObj + 8) * g_worldScale;
                }
                break;
            case 12: // scale component Z? (offset 0xA8)
                {
                    int scaleObj = readNextObject(stream);
                    *(float*)(thisPtr + 0xA8) = *(float*)(scaleObj + 8) * g_worldScale;
                }
                break;
            case 13: // scale component Y? (offset 0xA0)
                {
                    int scaleObj = readNextObject(stream);
                    *(float*)(thisPtr + 0xA0) = *(float*)(scaleObj + 8) * g_worldScale;
                }
                break;
            case 14: // scale component? (offset 0xA4)
                {
                    int scaleObj = readNextObject(stream);
                    *(float*)(thisPtr + 0xA4) = *(float*)(scaleObj + 8) * g_worldScale;
                }
                break;
        }
        finalizeElement(stream);
    }
}