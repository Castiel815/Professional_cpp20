//
// Created by CY815 on 2023/9/14.
//

// [[nodiscard]]属性可用于一个有返回值的函数，以使编译器在该函数被调用却没有对返回的值进行任何处理时发出警告，
// 可用于返回错误代码的函数，可用于类、函数和枚举
[[nodiscard("Some explanation")]] int func() {
    return 42;
}

// [[maybe_unused]]属性可用于禁止编译器在未使用某些内容时发出警告
// 可用于类和结构体、非静态数据成员、联合、typedef、类型别名、变量、函数、枚举以及枚举值
int func(int param1, [[maybe_unused]] int param2) {
    return 42;
}

int main() {
    func();
}
