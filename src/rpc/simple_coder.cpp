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
#include "utils/type.hpp"       					
#include "utils/string_utils.hpp"

namespace rabbit{
	const std::string simple_coder::encode(std::stack<data_struct> para){
		std::string msg = "#";
		while (!para.empty()) {
			data_struct data = para.top();
			para.pop();
			std::string value = to_string(data);
			msg += value + " ";
		}
		msg += "#";
		return msg;
	}
	
	const std::vector<std::string> simple_coder::decode(const std::string &msg){
		return string_split(msg, ' ');
	}
}
