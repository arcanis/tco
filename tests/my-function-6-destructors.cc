#include "./my-function.hh"

static my::function<int (int)> wrap;

int fn(int n)
{
    auto copy = wrap;

    return copy(n + 1);
}

int main(void)
{
    wrap = &fn;

    return wrap(0);
}
