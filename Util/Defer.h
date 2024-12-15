#ifndef DEFER_H
#define DEFER_H

// reference from: https://github.com/hanjingo/libcpp/blob/dev/libcpp/util/defer.hpp

#include <list>
#include <functional>

namespace libqt
{

class defer final
{
public:
    defer() {}
    ~defer()
    {
        if (cb_) {
            cb_();
        }
    }

    defer(const defer& other) = delete;
    defer& operator=(const defer&) = delete;

    defer(defer&& other) = delete;
    defer& operator=(defer&& other) = delete;

    explicit defer(std::function<void()>&& cb)
    {
        cb_ = std::move(cb);
    }

private:
    std::function<void()> cb_;
};

}

#define __defer_cat(a, b) a##b
#define _defer_cat(a, b) __defer_cat(a, b)

#define DEFER(cmd) ::libqt::defer _defer_cat(__simulate_go_defer__, __LINE__)([&]() { cmd; })
#define DEFER_CLASS(cmd) ::libqt::::defer _defer_cat(__simulate_go_defer_class__, __LINE__)([&, this]() { cmd; })

#endif // DEFER_H
