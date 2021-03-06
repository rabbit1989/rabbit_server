/***********************************************************************
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
*************************************************************************
                some string processing functions
*************************************************************************/
#include <cstdio>

#include "string_utils.hpp"

namespace rabbit{
	std::vector<std::string> string_split(const std::string &str, const char sep) {
		std::vector<std::string> ret;
		size_t i = 0, j = 0;
		size_t length = str.length();
		while (i < length) {
			while (i < length && str[i] == sep)i++;
			j = i+1;
			while (j < length && str[j] != sep)j++;
			ret.push_back(str.substr(i, j-i));
			i = j+1;
		}
		return ret;
	}

	std::string to_string(const data_struct& value){
		switch(value.type) {
			case INT:  
				char num_in_str[10];
				sprintf(num_in_str, "%d", value.i_val);				
				return std::string(num_in_str);
				break;
			case STRING: return value.s_val; break;
			case FLOAT: break;
			default: fprintf(stderr, "string_utils.cpp: to_string(): unknown data type!\n");
		}
		return "unknown_data";
	}

	int str2int(const std::string &str) {
		int ret = 0;
		for (int i = 0; i < str.size(); i++)
			ret = ret*10 + str[i] - 48;
		return ret;
	}

}
