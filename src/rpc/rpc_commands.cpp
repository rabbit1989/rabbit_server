/********************************************************************************************
Copyright (C) rabbit1989 2015

https://github.com/rabbit1989/rabbit_server

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*******************************************************************************************
       				each rpc function is wrapped as a commands
*******************************************************************************************/
#include <cstdio>       				
#include "rpc_commands.hpp"

namespace rabbit{

int calculate_add(const int a, const int b) {
	int ret = a + b;
	printf("hello, I am server! I will do calculation (%d + %d)  for you\n", a, b);
	return ret;
}

void on_calculate_add(const int sum, const int a, const int b) {
	printf("hello, I am client! I have received the result from server, the result of %d + %d is %d.\n", a, b, sum);
}

int cal_max(const int a, const int b) {
	int ret = a > b ? a : b;
	printf("server side: max(%d, %d)\n", a, b);
	return ret;
}

void on_cal_max(const int val, const int a, const int b) {
	printf("client side: the max number of (%d , %d) is %d\n", a, b, val);
}

}