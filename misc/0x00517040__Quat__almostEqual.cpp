// FUNC_NAME: Quat::almostEqual
bool __fastcall Quat::almostEqual(float *thisQuat, float *otherQuat)
{
    // DAT_00e44680 appears to be a mask for wrapping (e.g., 0xFFFFFFFF or similar)
    // DAT_00e2e780 is an epsilon value for comparison
    // Compare quaternion components with tolerance for wrapping and floating point error
    // Indices: 0-3 = quaternion (x, y, z, w), 8 = ?, 9 = ?, 10 = ?, 11 = ?, 12-15 = ?, 16-17 = ?
    // The mask applied via bitwise AND suggests dealing with potential sign/overflow issues
    if ((((((float)((uint)(thisQuat[8] - otherQuat[8]) & DAT_00e44680) <= DAT_00e2e780) &&
          ((float)((uint)(thisQuat[9] - otherQuat[9]) & DAT_00e44680) <= DAT_00e2e780)) &&
         ((float)((uint)(thisQuat[10] - otherQuat[10]) & DAT_00e44680) <= DAT_00e2e780)) &&
        (((((float)((uint)(thisQuat[0] - otherQuat[0]) & DAT_00e44680) <= DAT_00e2e780 &&
           ((float)((uint)(thisQuat[1] - otherQuat[1]) & DAT_00e44680) <= DAT_00e2e780)) &&
          (((float)((uint)(thisQuat[2] - otherQuat[2]) & DAT_00e44680) <= DAT_00e2e780 &&
           (((float)((uint)(thisQuat[3] - otherQuat[3]) & DAT_00e44680) <= DAT_00e2e780 &&
            ((float)((uint)(thisQuat[11] - otherQuat[11]) & DAT_00e44680) <= DAT_00e2e780)))))) &&
         (thisQuat[16] == otherQuat[16])))) &&
       ((((thisQuat[17] == otherQuat[17] &&
          ((float)((uint)(thisQuat[12] - otherQuat[12]) & DAT_00e44680) <= DAT_00e2e780)) &&
         ((float)((uint)(thisQuat[13] - otherQuat[13]) & DAT_00e44680) <= DAT_00e2e780)) &&
        (((float)((uint)(thisQuat[14] - otherQuat[14]) & DAT_00e44680) <= DAT_00e2e780 &&
         ((float)((uint)(thisQuat[15] - otherQuat[15]) & DAT_00e44680) <= DAT_00e2e780))))) {
        return true;
    }
    return false;
}