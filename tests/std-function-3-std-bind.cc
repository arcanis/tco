#include <functional>

int fn(std::function<int (int)> const & wrap, int n)
{
    return wrap(n + 1);
}

int main(void)
{
    using namespace std::placeholders;

    std::function<int (int)> wrap;
    wrap = std::bind(&fn, std::ref(wrap), _1);

    return wrap(0);
}
