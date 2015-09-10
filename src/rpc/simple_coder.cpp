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
       					a simple of rpc coder
*******************************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "simple_coder.hpp"
#include "utils/string_utils.hpp"

namespace rabbit{
	const std::string simple_coder::encode(const char*func_name, va_list para_list){
		std::string msg = "#" + std::string(func_name);
		char num_in_str[10];
		int para = va_arg(para_list, int);
		while (para != -1) {
			itoa(para, num_in_str, 10);
			msg += " " + std::string(num_in_str);
			para = va_arg(para_list, int);
		}
		msg += "#";
		return msg;
	}
	
	std::pair<std::string, std::vector<std::string> > simple_coder::decode(const std::string &msg){
		std::vector<std::string> para_list = string_split(msg, ' ');
		return std::make_pair(para_list[0], std::vector<std::string>(para_list.begin()+1, para_list.end()));
	}
}
