#include "./my-function.hh"

static my::function<int (int)> wrap;

int fn(int n)
{
    return wrap(n + 1);
}

int main(void)
{
    wrap = &fn;

    return wrap(0);
}
