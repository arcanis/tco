int fn_b(int n);

int fn_a(int n)
{
    return fn_b(n + 1);
}

int fn_b(int n)
{
    return fn_a(n + 1);
}

int main(void)
{
    return fn_a(0);
}
