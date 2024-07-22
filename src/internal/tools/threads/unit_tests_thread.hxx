
#include "catch2/catch_session.hpp"

#include <mutex>
#include <thread>

namespace yg
{
class unit_tests_thread : public std::thread
{
public:
    unit_tests_thread()
        : std::thread(run_catch_session)
    {
    }
    ~unit_tests_thread() { detach(); }

private:
    static int run_catch_session() { return Catch::Session().run(); }
};
} // namespace yg