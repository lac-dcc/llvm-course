int32_t strideX = XAI_CNN_CONV_GET_STRIDEX(param);

if (strideX == 1) {
    MAKE_NAME(convolved3D_S_MxNj1, SBIXCa2_MOD_ID16WH)(inTile, inPtrOffsetArr, coeffTile, biasArray, outTile, param);
} else if (strideX == 2) {
    MAKE_NAME(convolved3D_S_MxNj2, SBIXCa2_MOD_ID16WH)(inTile, inPtrOffsetArr, coeffTile, biasArray, outTile, param);
}