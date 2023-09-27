//
// Created by CY815 on 2023/9/23.
//
#include <memory>
#include <cstdio>
#include <iostream>

class Foo {
public:
    explicit Foo(std::unique_ptr<int> data) : m_data{std::move(data)} {}

private:
    std::unique_ptr<int> m_data;
};

int *my_alloc(int value) {
    return new int{value};
}

void my_free(const int *p) {
    delete p;
}

void close(FILE *filePtr) {
    if (filePtr == nullptr) {
        return;
    }
    fclose(filePtr);
    std::cout << "File closed." << std::endl;
}

class Simple {
public:
    Simple() { std::cout << "Simple constructor called!" << std::endl; }

    ~Simple() { std::cout << "Simple destructor called!" << std::endl; }
};

namespace shared_ptr_double_delete {
    void doubleDelete() {
        Simple *mySimple{new Simple{}};
        std::shared_ptr<Simple> smartPtr1(mySimple);
        std::shared_ptr<Simple> smartPtr2(mySimple);
    }

    void noDoubleDelete() {
        auto smartPtr1{std::make_shared<Simple>()};
        auto smartPtr2{smartPtr1};
    }

    void test() {
        //doubleDelete();
        noDoubleDelete();
    }
}

namespace shared_ptr_aliasing {
    class Foo {
    public:
        Foo(int value) : m_data{value} {}

        int m_data;
    };


    void test() {
        auto foo{std::make_shared<Foo>(42)};
        auto aliasing{std::shared_ptr<int>{foo, &foo->m_data}};
    }
}

namespace weak_ptr {
    void useResource(std::weak_ptr<Simple> &weakSimple) {
        auto resource{weakSimple.lock()};
        if (resource) {
            std::cout << "Resource still alive." << std::endl;
        } else {
            std::cout << "Resource has been freed!" << std::endl;
        }
    }

    void test() {
        auto sharedSimple{std::make_shared<Simple>()};
        std::weak_ptr<Simple> weakSimple{sharedSimple};

        useResource(weakSimple);

        sharedSimple.reset();

        useResource(weakSimple);
    }
}

namespace unique_ptr_return_from_function {
    std::unique_ptr<Simple> create() {
        auto ptr{std::make_unique<Simple>()};
        return ptr;
    }

    void test() {
        std::unique_ptr<Simple> mySmartPtr1{create()};
        auto mySmartPtr2{create()};
    }
}

namespace enable_shared_from_this {
    class Foo : public std::enable_shared_from_this<Foo> {
    public:
        std::shared_ptr<Foo> getPointer() {
            return shared_from_this();
        }
    };

    void test() {
        auto ptr1{std::make_shared<Foo>()};
        auto ptr2{ptr1->getPointer()};
    }
}

int main() {
    auto myIntSmartPtr{std::make_unique<int>(42)};
    Foo f{std::move(myIntSmartPtr)};

    std::unique_ptr<int, decltype(&my_free)> myIntSmart1{my_alloc(42), my_free};

    std::shared_ptr<int> myIntSmart2{my_alloc(42), my_free};

#if defined(_MSC_VER)
    FILE *f2{nullptr};
    fopen_s(&f2, "data.txt", "w");
#else
    FILE *f2{fopen("data.txt", "w")};
#endif
    std::shared_ptr<FILE> filePtr{f2, close};
    if (filePtr == nullptr) {
        std::cerr << "Error opening file." << std::endl;
    } else {
        std::cout << "File opened." << std::endl;
    }

    shared_ptr_double_delete::test();

    shared_ptr_aliasing::test();

    weak_ptr::test();

    unique_ptr_return_from_function::test();

    enable_shared_from_this::test();

    return 0;
}