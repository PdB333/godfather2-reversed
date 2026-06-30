// FUNC_NAME: DualQuaternion::combine
void DualQuaternion::combine(const DualQuaternion& sourceA, const DualQuaternion& sourceB)
{
    // sourceA is passed in unaff_EDI, sourceB is param_1, this is in_EAX
    // Structure: uint8 type; float* rotPart (8 floats); float* dualPart (4 floats)
    // Offsets: +0x00 type, +0x04 pointer to 8 floats, +0x08 pointer to 4 floats

    if (sourceA.type == 2) // sourceA is a valid dual quaternion (type 2)
    {
        if (sourceB.type == 2) // both are valid dual quaternions
        {
            this->type = 2;
            FUN_00582ea0(); // likely a helper (normalize, multiply, or scale)
            float* srcADual = reinterpret_cast<float*>(sourceA.dualPart); // sourceA.dualPart is pointer to 4 floats
            float a1 = srcADual[1]; // second component
            float a2 = srcADual[2]; // third
            float a3 = srcADual[3]; // fourth
            float* srcBDual = reinterpret_cast<float*>(sourceB.dualPart);
            float b1 = srcBDual[1];
            float b2 = srcBDual[2];
            float b3 = srcBDual[3];
            float* dstDual = reinterpret_cast<float*>(this->dualPart);
            dstDual[0] = srcADual[0] * srcBDual[0];
            dstDual[1] = a1 * b1;
            dstDual[2] = a2 * b2;
            dstDual[3] = a3 * b3;
            dstDual[3] = s_dualWGlobal; // override last component with a global constant (DAT_00e2b1a4)
            return;
        }
        // only sourceA is type 2 -> copy sourceB into this? No, we fall through to copy from sourceA? 
        // Actually the code: if sourceB not 2, it falls to the else branch (since outer if sourceA==2, inner if sourceB==2, else does nothing? Wait: The decomp else for if(*unaff_EDI==2) leads to an else that is executed if *param_1!=2. That else copies from unaff_EDI to in_EAX. So when sourceA==2 and sourceB!=2, we copy sourceA into this.
        // But then after that outer if, there is another if else chain for sourceA!=2.
        // I need to restructure the if-else correctly.

        // Actually re-reading decomp: 
        // if (*unaff_EDI == 2) {
        //     if (*param_1 == 2) {
        //         set this type=2; call helper; multiply dual parts; set last to global; return;
        //     } else {
        //         // fall through to copy from unaff_EDI to in_EAX? No, the code after that else is not in an else block? The control flow is tricky.
        //     }
        // }
        // Actually the decomp shows:
        // if (*(char *)*unaff_EDI != '\x02') { ... } 
        // else { // *unaff_EDI == 2
        //     if (*(char *)*param_1 == '\x02') { 
        //         ... return;
        //     }
        //     // no else? Then fall through to the copy block below?
        // }
        // But the copy block appears after both conditions? Let's examine the decomp again:

        // if (*(char *)*unaff_EDI != '\x02') {
        //     if (*(char *)*param_1 == '\x02') { ... copy from param_1 to in_EAX; return; }
        //     *(undefined1 *)*in_EAX = 0; return;
        // }
        // if (*(char *)*param_1 == '\x02') { ... multiply case; return; }
        // // at this point *unaff_EDI == 2 and *param_1 != 2
        // // fall through to copy from unaff_EDI to in_EAX
        // ... copy code
        // return;

        // So the structure is: first branch for *unaff_EDI != 2; then separate if for *unaff_EDI==2 && *param_1==2; then fallback for *unaff_EDI==2 && *param_1!=2.
        // So I'll implement accordingly.
    }

    // If sourceA.type != 2
    if (sourceA.type != 2)
    {
        if (sourceB.type == 2)
        {
            // Copy sourceB into this
            this->type = 2;
            float* srcBRot = reinterpret_cast<float*>(sourceB.rotPart);
            float* dstRot = reinterpret_cast<float*>(this->rotPart);
            dstRot[0] = srcBRot[0];
            dstRot[1] = srcBRot[1];
            dstRot[2] = srcBRot[2];
            dstRot[3] = srcBRot[3];
            dstRot[4] = srcBRot[4];
            dstRot[5] = srcBRot[5];
            dstRot[6] = srcBRot[6];
            dstRot[7] = srcBRot[7];

            float* srcBDual = reinterpret_cast<float*>(sourceB.dualPart);
            float* dstDual = reinterpret_cast<float*>(this->dualPart);
            dstDual[0] = srcBDual[0];
            dstDual[1] = srcBDual[1];
            dstDual[2] = srcBDual[2];
            dstDual[3] = srcBDual[3];
            return;
        }
        // Both non-type2: set this type to 0 (identity)
        this->type = 0;
        return;
    }

    // *unaff_EDI == 2 and *param_1 != 2 (fallback from earlier)
    // Copy sourceA into this
    this->type = 2;
    float* srcARot = reinterpret_cast<float*>(sourceA.rotPart);
    float* dstRot = reinterpret_cast<float*>(this->rotPart);
    dstRot[0] = srcARot[0];
    dstRot[1] = srcARot[1];
    dstRot[2] = srcARot[2];
    dstRot[3] = srcARot[3];
    dstRot[4] = srcARot[4];
    dstRot[5] = srcARot[5];
    dstRot[6] = srcARot[6];
    dstRot[7] = srcARot[7];

    float* srcADual = reinterpret_cast<float*>(sourceA.dualPart);
    float* dstDual = reinterpret_cast<float*>(this->dualPart);
    dstDual[0] = srcADual[0];
    dstDual[1] = srcADual[1];
    dstDual[2] = srcADual[2];
    dstDual[3] = srcADual[3];
}