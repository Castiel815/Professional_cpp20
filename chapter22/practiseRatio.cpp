//
// Created by CY815 on 2023/11/29.
//

#include "practiseRatio.h"

void practiseRatio::useRatio() {
    using r1 = std::ratio<1, 60>;

    intmax_t num{r1::num};  // 分子
    intmax_t den{r1::den};  // 分母
    std::cout << std::format("1) r1 = {}/{}", num, den) << std::endl;

    using r2 = std::ratio<1, 30>;
    std::cout << std::format("2) r2 = {}/{}", r2::num, r2::den) << std::endl;
    using result = std::ratio_add<r1, r2>::type;
    std::cout << std::format("3) sum = {}/{}", result::num, result::den) << std::endl;

    using res = std::ratio_less<r2, r1>;
    std::cout << std::format("4) r2 < r1: {}", res::value) << std::endl;
}
