int fn(int n)
{
    return fn(n + 1);
}

int main(void)
{
    return fn(0);
}
