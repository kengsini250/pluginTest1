#ifndef ADD_H
#define ADD_H

//没用
#include "pluginTest_1_global.h"

//   *******必须加 extern "C" ，否则QLibrary不能调用！！！！******
extern "C" Q_DECL_EXPORT int func(int a, int b);

#endif // ADD_H
