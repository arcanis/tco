#pragma once

#include <memory>

namespace my
{
    template <typename Return, typename ... Args>
    struct function_base
    {
        virtual std::unique_ptr<function_base> clone(void) const = 0;

        virtual Return operator()(Args ... args) const = 0;
    };

    template <typename T, typename Return, typename ... Args>
    struct function_impl : public function_base<Return, Args ...>
    {
        function_impl(T const & t)
            : m_internal(t)
        {
        }

        virtual std::unique_ptr<function_base<Return, Args ...>> clone(void) const
        {
            return std::make_unique<function_impl<T, Return, Args ...>>(m_internal);
        }

        virtual Return operator()(Args ... args) const
        {
            return m_internal(args ...);
        }

    private:

        T m_internal;
    };

    template <typename Return, typename ... Args>
    struct function_impl<Return (*)(Args ...), Return, Args ...> : public function_base<Return, Args ...>
    {
        function_impl(Return (*ptr)(Args ...))
            : m_ptr(ptr)
        {
        }

        virtual std::unique_ptr<function_base<Return, Args ...>> clone(void) const
        {
            return std::make_unique<function_impl<Return (*)(Args ...), Return, Args ...>>(m_ptr);
        }

        virtual Return operator()(Args ... args) const
        {
            return m_ptr(args ...);
        }

    private:

        Return (*m_ptr)(Args ...);
    };

    template <typename T>
    struct function;

    template <typename Return, typename ... Args>
    struct function<Return (Args ...)>
    {
        function(void)
            : m_impl()
        {
        }

        function(function const & other)
            : m_impl(other.m_impl ? other.m_impl->clone() : nullptr)
        {
        }

        template <typename T>
        function(T const & t)
            : m_impl(std::make_unique<function_impl<T, Return, Args ...>>(t))
        {
        }

        template <typename T>
        function & operator=(T const & t)
        {
            m_impl = std::make_unique<function_impl<T, Return, Args ...>>(t);

            return *this;
        }

        Return operator()(Args ... args) const
        {
            return m_impl->operator()(args ...);
        }

    private:

        std::unique_ptr<function_base<Return, Args ...>> m_impl;
    };
}
