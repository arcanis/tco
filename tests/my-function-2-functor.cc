#include "./my-function.hh"

static my::function<int (int)> wrap;

struct Test
{
    int operator()(int n) const
    {
        return wrap(n + 1);
    }
};

int main(void)
{
    wrap = Test();

    return wrap(0);
}
