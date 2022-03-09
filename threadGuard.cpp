#include "threadGuard.hpp"

thread_guard::thread_guard(std::thread &t): t_(t) {}

thread_guard::~thread_guard() {
    if (t_.joinable()) {
        t_.join();
    }
}