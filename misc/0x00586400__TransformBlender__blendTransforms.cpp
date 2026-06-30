// FUNC_NAME: TransformBlender::blendTransforms
void TransformBlender::blendTransforms(TransformBlender* other) {
    // this = in_EAX, other = param_1
    // unaff_EDI seems to be a global or another instance? Possibly this->source?
    // Based on code, unaff_EDI is likely a member pointer or global.
    // We'll assume unaff_EDI is a global or another instance stored somewhere.
    // For reconstruction, we'll treat it as a separate pointer.
    TransformBlender* source = unaff_EDI; // unknown origin

    if (source->state != 2) {
        if (other->state == 2) {
            // Copy from other to this
            this->state = 2;
            // Copy 8 floats from other->matrixPart1 to this->matrixPart1
            for (int i = 0; i < 8; i++) {
                this->matrixPart1[i] = other->matrixPart1[i];
            }
            // Copy 4 floats from other->matrixPart2 to this->matrixPart2
            for (int i = 0; i < 4; i++) {
                this->matrixPart2[i] = other->matrixPart2[i];
            }
            return;
        }
        this->state = 0;
        return;
    }

    if (other->state == 2) {
        this->state = 2;
        // Call helper (likely multiply matrices)
        FUN_00582ea0(); // assume multiplies source and other matrices
        // Element-wise multiply source->matrixPart2 with other->matrixPart2
        for (int i = 0; i < 4; i++) {
            this->matrixPart2[i] = source->matrixPart2[i] * other->matrixPart2[i];
        }
        // Override last element with a global constant
        this->matrixPart2[3] = DAT_00e2b1a4;
        return;
    }

    // Default: copy from source to this
    this->state = 2;
    for (int i = 0; i < 8; i++) {
        this->matrixPart1[i] = source->matrixPart1[i];
    }
    for (int i = 0; i < 4; i++) {
        this->matrixPart2[i] = source->matrixPart2[i];
    }
}