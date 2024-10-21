int nand(int a, int b) {
    return ~(a & b) & 1;
    //mask with &1 to get least significant bit
    //should probably just mask at outputs
}