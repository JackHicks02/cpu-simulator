int get_bit(int integer, int bit)
{
    return (integer >> bit) & 1;
}