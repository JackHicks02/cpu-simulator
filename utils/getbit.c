int getBit(int integer, int bit)
{
    return (integer >> bit) & 1;
}