//
// Created by wuha on 06.08.20.
//
#include "pljit/Pljit.hpp"
#include <thread>
#include <gtest/gtest.h>
using namespace pljit;
using namespace std;
TEST(TestRegisterFunction,testreturn){
    Pljit jit;
    auto func = jit.registerFunction("BEGIN\n"
                                     "RETURN 42\n"
                                     "END.\n");
    auto result = func({});
    ASSERT_EQ(result,42);
}
TEST(TestRegisterFunction,testfunction1){
    Pljit jit;
    auto func = jit.registerFunction("PARAM a;\n"
                                     "VAR b, c, d;\n"
                                     "CONST e = 1;\n"
                                     "BEGIN\n"
                                     "b := e + 1 / (2 - 1) + 1 -( (4 / 2 * 2 * 1) - 1 );\n"
                                     "c := b + e;\n"
                                     "d := b + c + e;\n"
                                     "RETURN d + 1 * 2- 2 / 1;\n"
                                     "a := 233;\n"
                                     "RETURN 1\n"
                                     "END.");
    vector<thread> threads;
    for (int64_t value = 0; value < 10; ++value)
        threads.emplace_back([func,value]() {
          auto result = func({value});
          ASSERT_EQ(result,8);
        });
    for (auto& thread : threads)
        thread.join();

}
TEST(TestRegisterFunction,test1){
    Pljit jit;
    auto func = jit.registerFunction("PARAM w, h, d;\n"
                                     "VAR a;\n"
                                     "CONST b = 1, c = 2;\n"
                                     "BEGIN\n"
                                     "a := c * b;\n"
                                     "a := a+w;\n"
                                     "RETURN w+h+d+a+2\n"
                                     "END.\n");
    auto result = func({1,2,3});
    ASSERT_EQ(result,11);
}
TEST(TestRegisterFunction,testmultithread){
    Pljit jit;
    auto func = jit.registerFunction("PARAM w, h, d;\n"
                                     "VAR a;\n"
                                     "CONST b = 1, c = 2;\n"
                                     "BEGIN\n"
                                     "a := c * b;\n"
                                     "a := a+w;\n"
                                     "RETURN w+h+d+a+2\n"
                                     "END.\n");
    vector<thread> threads;
    for (int64_t value = 0; value < 100; ++value)
        threads.emplace_back([func,value]() {
            auto result = func({value,value,value});
            ASSERT_EQ(4*value+4,result);
        });

    for (auto& thread : threads)
        thread.join();
}
TEST(TestRegisterFunction,testmultiregister) {
    Pljit jit;
    auto func1 = jit.registerFunction("PARAM w, h, d;\n"
                                     "VAR a;\n"
                                     "CONST b = 1, c = 2;\n"
                                     "BEGIN\n"
                                     "a := c * b;\n"
                                     "a := a+w;\n"
                                     "RETURN w+h+d+a+2\n"
                                     "END.");
    auto func2 = jit.registerFunction("PARAM w, h, d;\n"
                                      "VAR a;\n"
                                      "CONST b = 2, c = 2;\n"
                                      "BEGIN\n"
                                      "a := c * b;\n"
                                      "a := a+w;\n"
                                      "RETURN w+h+d+a+2\n"
                                      "END.");
    vector<thread> threads;
    for (int64_t value = 0; value < 10; ++value)
        threads.emplace_back([func1,func2,value]() {
          auto result1 = func1({value,value,value});
          auto result2 = func2({value,value,value});
          ASSERT_EQ(4*value+4,result1);
          ASSERT_EQ(4*value+6,result2);
        });
    for (auto& thread : threads)
        thread.join();
}


