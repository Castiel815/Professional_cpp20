//
// Created by CY815 on 2023/11/29.
//

#ifndef PROFESSIONAL_CPP20_PRACTISERATIO_H
#define PROFESSIONAL_CPP20_PRACTISERATIO_H

#include "../commonBase/common.h"

#ifdef USE_CPP20
import <iostream>;
import <ratio>;
import <format>;
#else

#include <iostream>
#include <ratio>
#include <format>

#endif

/**
 * 编译期有理数
 */
class practiseRatio {
public:
    static void useRatio();
};


#endif //PROFESSIONAL_CPP20_PRACTISERATIO_H
