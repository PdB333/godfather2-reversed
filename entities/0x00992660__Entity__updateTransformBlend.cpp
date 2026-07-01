// FUNC_NAME: Entity::updateTransformBlend

void __thiscall Entity::updateTransformBlend(TransformInput* input) {
    int unused = 0;

    // Combine input transformation into boneTransform1 (+0xa8)
    combineTransforms(this, (Vector3*)(this + 0xa8), input->x, input->y, input->z, &unused);

    int* resultScalar = (int*)((int)input + 0xc); // input->result at +0xc

    // Combine input transformation into boneTransform2 (+0x9c)
    combineTransforms(this, (Vector3*)(this + 0x9c), input->x, input->y, input->z, resultScalar);

    // Add a scalar from the entity (+0x68) to the result
    *resultScalar += *(int*)(this + 0x68);
}