
__attribute__ ((aligned (16))) char stack0[4096 * 8];

int main()
{
    int a = 1;
    int b = 1;

    int c;
    while(1)
    {
        c = a + b;
    }
    return 0;
}