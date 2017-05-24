struct Destruct
{
    Destruct(void)
        : m_ptr(nullptr)
    {
    }

    ~Destruct(void)
    {
        delete m_ptr;
    }

    char * m_ptr;
};

struct Test
{
    int operator()(int n) const
    {
        Destruct destruct;

        return (*this)(n + 1);
    }
};

int main(void)
{
    Test test;

    return test(0);
}
