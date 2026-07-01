// FUNC_NAME: TransformNode::createTransformNode
void __thiscall TransformNode::createTransformNode(void* thisPtr, float posX, float posY, float posZ, float quatW, float quatX, float quatY, float quatZ)
{
    // Check if engine is ready to create transforms
    if (!isEngineReady()) {
        return;
    }

    // Allocate memory for a new TransformNode (size 0x58 = 88 bytes)
    TransformNode* newNode = (TransformNode*)allocateMemory(0x58);
    if (newNode == nullptr) {
        return;
    }

    // Initialize the base object (vtable, etc.)
    initTransform(newNode, thisPtr);

    // Set position (x, y, z) at offsets +0x3c, +0x40, +0x44
    newNode->positionX = posX;   // +0x3c
    newNode->positionY = posY;   // +0x40
    newNode->positionZ = posZ;   // +0x44

    // Set rotation as quaternion (w, x, y, z) at offsets +0x48, +0x4c, +0x50, +0x54
    newNode->quaternionW = quatW; // +0x48
    newNode->quaternionX = quatX; // +0x4c
    newNode->quaternionY = quatY; // +0x50
    newNode->quaternionZ = quatZ; // +0x54

    // Register the new transform node with the engine
    registerTransform(newNode);
}