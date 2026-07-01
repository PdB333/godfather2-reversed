// FUNC_NAME: Math::distanceSquaredFromPointToTriangle
float Math::distanceSquaredFromPointToTriangle(float *point, float *triangleV0, float *triangleV1, float *triangleV2)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float result;

  // Extract point coordinates
  fVar4 = *point;          // point.x
  fVar10 = point[1];       // point.y
  fVar12 = point[2];       // point.z

  // Vector from triangleV2 to point
  fVar1 = fVar4 - *triangleV2;          // point.x - V2.x
  fVar5 = fVar10 - triangleV2[1];       // point.y - V2.y
  fVar7 = fVar12 - triangleV2[2];       // point.z - V2.z

  // Vector from triangleV0 to point
  fVar2 = fVar4 - *triangleV0;          // point.x - V0.x
  fVar6 = fVar10 - triangleV0[1];       // point.y - V0.y
  fVar8 = fVar12 - triangleV0[2];       // point.z - V0.z

  // Compute dot products for barycentric coordinate calculation
  fVar15 = fVar5 * fVar5 + fVar7 * fVar7 + fVar1 * fVar1;  // |V2->point|^2
  fVar9 = fVar6 * fVar5 + fVar8 * fVar7 + fVar2 * fVar1;   // (V0->point) dot (V2->point)

  // Vector from triangleV1 to point
  fVar11 = (fVar10 - triangleV1[1]) * fVar5 + (fVar12 - triangleV1[2]) * fVar7 +
           (fVar4 - *triangleV1) * fVar1;  // (V1->point) dot (V2->point)

  fVar3 = fVar6 * fVar6 + fVar8 * fVar8 + fVar2 * fVar2;  // |V0->point|^2
  fVar13 = (fVar10 - triangleV1[1]) * fVar6 + (fVar12 - triangleV1[2]) * fVar8 +
           (fVar4 - *triangleV1) * fVar2;  // (V1->point) dot (V0->point)

  // Compute denominator for barycentric coordinates
  fVar14 = fVar3 * fVar15 - fVar9 * fVar9;  // determinant

  // Compute barycentric coordinates (u, v)
  fVar15 = fVar13 * fVar15 - fVar11 * fVar9;  // u * determinant
  fVar3 = fVar3 * fVar11 - fVar13 * fVar9;    // v * determinant

  result = DAT_00d5f6f0;  // default large value (e.g., infinity or max float)

  // Check if point projects inside triangle (barycentric coordinates >= 0 and u+v <= 1)
  if (((0.0 <= fVar3 * fVar14) && (0.0 <= fVar15 * fVar14)) &&
     ((float)((uint)fVar15 & DAT_00e44680) + (float)((uint)fVar3 & DAT_00e44680) <=
      (float)((uint)fVar14 & DAT_00e44680))) {
    // Compute closest point on triangle
    fVar9 = DAT_00d5ccf8 / (fVar14 + (float)PTR_FUN_00e4462c);  // 1/determinant (with epsilon)
    fVar3 = fVar9 * fVar3;  // v
    fVar9 = fVar9 * fVar15; // u

    // Compute distance from point to closest point on triangle
    fVar12 = triangleV1[2] - (fVar3 * fVar8 + fVar12 + fVar9 * fVar7);
    fVar10 = triangleV1[1] - (fVar3 * fVar6 + fVar10 + fVar9 * fVar5);
    fVar4 = *triangleV1 - (fVar3 * fVar2 + fVar4 + fVar9 * fVar1);
    result = fVar12 * fVar12 + fVar10 * fVar10 + fVar4 * fVar4;  // squared distance
  }

  return (float10)result;  // return as extended precision float
}