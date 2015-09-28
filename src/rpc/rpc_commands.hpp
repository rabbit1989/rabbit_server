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
       				each rpc function is wrapped as a command 
*******************************************************************************************/

#ifndef RPC_COMMANDS_HPP
#define RPC_COMMANDS_HPP

#include <vector>

#include "rpc/rpc_channel.hpp"
#include "utils/type.hpp"

namespace rabbit{

//abstract command class
class rpc_command{
	public:
	virtual	void execute(std::vector<data_struct>&, rpc_channel*) = 0;	
};

//rpc functions
int calculate_add(const int, const int);
void on_calculate_add(const int, const int, const int);
int cal_max(const int, const int);
void on_cal_max(const int, const int, const int);

//rpc commands, each command corresponds to one rpc function
class rc_calculate_add: public rpc_command{
public:
	void execute(std::vector<data_struct>& para, rpc_channel *channel) {
		int a = from_data_struct<int>(para[0]);
		int b = from_data_struct<int>(para[1]);
		int ret = calculate_add(a, b);
		channel->rpc_call("on_calculate_add", ret, a, b);
	}
};

class rc_on_calculate_add: public rpc_command{
public:
	void execute(std::vector<data_struct>& para, rpc_channel *channel) {
		on_calculate_add(from_data_struct<int>(para[0]), from_data_struct<int>(para[1]), from_data_struct<int>(para[2]));
	}
};

class rc_cal_max: public rpc_command{
public:
	void execute(std::vector<data_struct> &para, rpc_channel *channel) {
		int a = from_data_struct<int>(para[0]);
		int b = from_data_struct<int>(para[1]);
		int ret = cal_max(a, b);
		channel->rpc_call("on_cal_max", ret, a, b);
	}

};

class rc_on_cal_max: public rpc_command{
public:
	virtual void execute(std::vector<data_struct> &para, rpc_channel *channel) {
		on_cal_max(from_data_struct<int>(para[0]), from_data_struct<int>(para[1]), from_data_struct<int>(para[2]));
	}
};

}
#endif