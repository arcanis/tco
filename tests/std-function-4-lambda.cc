#include <functional>

int main(void)
{
    std::function<int (int)> fn;

    fn = [&fn](int n) { return fn(n + 1); };

    return fn(0);
}
