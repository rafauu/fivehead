#pragma once

#include <functional>
#include <utility>


namespace Fivehead
{

template <typename T>
class Property
{
private:
    T data;
    std::function<void()> callable;

public:
    template <typename Callable>
    explicit Property(Callable callable) : callable{callable} {}

    const T& get() const
    {
        return data;
    }

    template <typename U>
    void set(U&& newData)
    {
        const bool dataChanged = (newData != data);
        data = std::forward<U>(newData);
        if (dataChanged)
            callable();
    }
};

}

