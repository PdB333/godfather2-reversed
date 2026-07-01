// Xbox PDB: EARS_Apt_UIPauseMap_SetUpCameraOnHide
// FUNC_NAME: Presentation::updateZoomBlurEffect
// Address: 0x009795b0
// Role: Updates the zoom blur post-processing effect. Copies camera transform data, checks activation bit, loads shader, and creates effect node.

uint Presentation::updateZoomBlurEffect(void) {
    int* effectNodePtr;
    int newEffectNode;
    char shaderName[16]; // buffer for shader name (unused in this path?)
    float viewMatrix[16]; // 4x4 matrix from renderer

    // Get camera object or source
    int* sourceObj = *(int**)(this + 0x68);
    if (sourceObj != nullptr) {
        // Copy transform data (position? / rotation?) from source to this object
        this->field_d0 = *(int*)(sourceObj + 0x90);
        this->field_d4 = *(int*)(sourceObj + 0x94);
        this->field_d8 = *(int*)(sourceObj + 0x98);
        this->field_dc = *(int*)(sourceObj + 0x9c);
        
        // Copy additional data (e.g., FOV, zoom factor)
        this->field_e0 = *(int*)(sourceObj + 0xb4);
        
        // Check zoom blur activation bit (bit 4 of field_60)
        if (((this->field_60 >> 4) & 1) == 0) {
            // Activate effect: call with source, effect ID 9, enable flag 1
            FUN_00424df0(0, sourceObj, *(int*)(sourceObj + 0x108), 9, 1, 0);
            this->field_70 = DAT_01205214; // set some global
            this->field_60 |= 8; // set bit 3 (rendering flag?)
            
            // Get renderer and copy view matrix
            int* renderer = FUN_004262f0(0);
            for (int i = 0; i < 16; i++) {
                viewMatrix[i] = *(float*)(renderer + 0x40 + i*4);
            }
            
            // Load shader "zoomblur_out"
            FUN_004eacb0("zoomblur_out");
            
            // Create effect node
            FUN_004df420(&newEffectNode, shaderName, viewMatrix, 0xffffffff, 4, 0, 0xffffffff, 0);
            
            // Manage linked list at this->field_fc (effect node list)
            effectNodePtr = (int*)(this + 0xfc);
            if (*effectNodePtr != 0) {
                FUN_004df600(); // release previous node?
            }
            
            // Store new node in linked list
            *effectNodePtr = newEffectNode;
            if (newEffectNode != 0) {
                *(int**)(newEffectNode + 8) = effectNodePtr; // doubly linked list
            }
        } else {
            // Deactivate effect
            FUN_00424df0(0, sourceObj, 0, 9, 1, 1);
        }
    }
    
    // Clean up additional effect object?
    if (*(int*)(this + 0x6c) != 0) {
        FUN_00424ee0(0, *(int*)(this + 0x6c));
    }
    
    return 1; // success
}