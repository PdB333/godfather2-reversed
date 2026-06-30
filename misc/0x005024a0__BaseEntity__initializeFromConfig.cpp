// FUNC_NAME: BaseEntity::initializeFromConfig
void BaseEntity::initializeFromConfig(BaseEntity *this, const EntityConfig *config) {
    // Call base class or engine initialization
    FUN_00533cc0();

    this->vtable = &PTR_FUN_00e37e18;  // +0x00: Initialize vtable pointer

    // Check if the entity should be initialized based on a flag in the config
    if (*(char *)(config + 0xd) == '\0') {  // config->flags & 0x100? Skip if zero
        int *threadLocal = *(int **)(__readfsdword(0x2c));  // Thread-local storage base
        this->transformPoolIndex = this + 0x18;  // +0x28: Pointer to transform data (self-relative?)
        this->field_0x2c = 0;  // Offset 0x2c, set to 0 (maybe short)
        this->field_0x30 = 0;  // +0x30
        this->configRef = config;  // +0x24: Store pointer to creation config
        this->field_0x34 = 0;  // +0x34
        *(short *)((int)this + 0x2e) = -1;  // +0x2e: Set to 0xFFFF
        this->field_0x3c = 0;  // +0x3c
        this->field_0x38 = config->someId;  // +0x38: Copy from config[11] (offset 0x2C in config?)

        // Access a shared memory pool from thread-local and clear a bit at the pool index
        uint *poolEntry = (uint *)(*(int *)(threadLocal + 8) + this->poolIndex);
        *poolEntry &= 0xfffffffe;

        this->field_0x40 = 0;  // +0x40

        // If config has a specific flag, load an additional value (e.g., transform)
        if ((config->flags & 0x10000) != 0) {
            FUN_004e41b0();  // Possibly a matrix/vector function
            this->extraTransform = in_XMM0_Da;  // Store float result
        }

        // Initialize a 4x4 matrix or transform at a memory location derived from poolIndex
        float *matrixBase = (float *)(this->poolIndex + 0x10 + *(int *)(threadLocal + 8));
        float identityValue = DAT_00e2b1a4;  // Likely 1.0f for identity
        matrixBase[0] = identityValue;
        matrixBase[1] = 0.0f;
        matrixBase[2] = 0.0f;
        matrixBase[3] = 0.0f;
        matrixBase[4] = 0.0f;
        matrixBase[5] = identityValue;
        matrixBase[6] = 0.0f;
        matrixBase[7] = 0.0f;
        matrixBase[8] = 0.0f;
        matrixBase[9] = 0.0f;
        matrixBase[10] = identityValue;
        matrixBase[11] = 0.0f;

        // Handle additional transform data based on config flags
        if ((config->flags & 2) != 0) {
            // Additive: convert config positions (integers) to float and add to existing matrix
            float *addPos = (float *)(this->poolIndex + 0x40 + *(int *)(threadLocal + 8));
            *addPos += (float)config->positionX;  // config[21]
            addPos[1] += (float)config->positionY;  // config[22]
            addPos[2] += (float)config->positionZ;  // config[23]
        } else if ((config->flags & 4) != 0) {
            // Absolute: directly set positions from config
            int *absPos = (int *)(this->poolIndex + 0x40 + *(int *)(threadLocal + 8));
            absPos[0] = config->positionX;
            absPos[1] = config->positionY;
            absPos[2] = config->positionZ;
        }

        // Call another initialization function
        FUN_004ebb40();

        // Store global constants
        this->field_0x44 = DAT_00e2eff4;  // +0x44
        this->field_0x48 = 0;  // +0x48

        // Gather resource IDs from config (likely hash strings)
        uint resourceId1 = 0;
        uint resourceId2 = 0;
        if (config->resource1[0] != 0 || config->resource1[1] != 0 ||
            config->resource1[2] != 0 || config->resource1[3] != 0) {
            resourceId1 = FUN_004e9270();  // Convert name to ID
            if (resourceId1 != 0 && resourceId1 != 0xffffffff && resourceId1 < 0x1000) {
                int *refTable = (int *)(&DAT_011a0f38 + resourceId1 * 0x38);
                if (refTable != nullptr) {
                    *refTable += 1;  // Increment reference count
                }
            }
        }
        if (config->resource2[0] != 0 || config->resource2[1] != 0 ||
            config->resource2[2] != 0 || config->resource2[3] != 0) {
            resourceId2 = FUN_004e9270();
            if (resourceId2 != 0 && resourceId2 != 0xffffffff && resourceId2 < 0x1000) {
                int *refTable = (int *)(&DAT_011a0f38 + resourceId2 * 0x38);
                if (refTable != nullptr) {
                    *refTable += 1;
                }
            }
        }

        // Final initialization with combined data
        FUN_005021a0(this, 
                     CONCAT44(config, this->unknownField), 
                     CONCAT44(resourceId2, resourceId1),
                     this->poolIndex, 
                     this->field_0x14);
    }
}