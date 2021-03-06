// SPDX-License-Identifier: GPL-3.0-only
/* -*- ConixCore -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 2019-2021 Maksym Prymierov
 *
 * ------------------------------------------------------------------------- */

#pragma once

#include <kernel/tty.h>

#define ADD_TEST() add_test(__FUNCTION__)

namespace conix {
namespace kernel {
namespace tests {

class test {
        size_t tests_failed;
        size_t tests_passed;
        size_t test_count;

protected:
        io::tty& log;
        const char* name;

        auto message()
        {
                return log << "\tTest[" << name << "]:[" << test_count
                        << "] ";
        }

        void fail()
        {
                message() << "is ";
                log.set_foreground(io::tty::foreground_color::red);
                log << "FAIL\n";
                ++tests_failed;
                log.set_foreground(io::tty::foreground_color::light_gray);
        }

        void pass()
        {
                message() << "is ";
                log.set_foreground(io::tty::foreground_color::green);
                log << "PASS\n";
                ++tests_passed;
                log.set_foreground(io::tty::foreground_color::light_gray);
        }

        void add_test()
        {
                ++test_count;
        }

        void add_test(const char* test_case)
        {
                ++test_count;
                message() << test_case << " starting...\n";
        }

public:
        test(const char* _name) :
                tests_failed(0),
                tests_passed(0),
                test_count(0),
                log(io::out()),
                name(_name) 
        {  }

        virtual void start() {  }
        
        template <typename T>
        bool assert_eq(T actual, T expected)
        {
                if (actual != expected) {
                        return false;
                } else {
                        return true;
                }
        }

        template <typename T>
        bool assert_memory_ok(T* memory)
        {
                if (memory != reinterpret_cast<T*>(ENOMEM)) {
                        return true;
                }
                return false;
        }

        void stat()
        {
                log << "\tTest [" << name << "] has been";
                if (tests_passed != test_count) {
                        log << " failures";        
                } else {
                        log << " successful";
                }
                log << " finished.\n";

                log << "\t" << "Total tests: " << test_count << 
                        " Tests passed: " << tests_passed <<
                        " Tests failed: " << tests_failed << ".\n";
        }
};

}; // tests
}; // kernel
}; // conix
