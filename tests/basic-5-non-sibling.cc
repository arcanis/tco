double fn_b(int a, int b);

int fn_a(int n)
{
    return fn_b(n + 1, n + 1);
}

double fn_b(int a, int b)
{
    return fn_a(a * b);
}

int main(void)
{
    return fn_a(0);
}
