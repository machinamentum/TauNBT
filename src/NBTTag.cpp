/*
 * TauNBT
 * NBTTag.cpp
 *
 * Copyright (c) Joshua Huelsman, 12/28/2012.
 * All rights reserved.
 * 
 * BSD License
 *
 * Redistribution and use in source and binary forms, with or without modification, are 
 * permitted provided that the following conditions are met:
 * - Redistributions of source code must retain the above copyright notice, this list of
 *  conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice, this list
 *  of conditions and the following disclaimer in the documentation and/or other materia
 * ls provided with the distribution.
 * - Neither the name of the "Joshua Huelsman" nor the names of its contributors may be u
 * sed to endorse or promote products derived from this software without specific prior 
 * written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY E
 * XPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES O
 * F MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SH
 * ALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENT
 * AL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROC
 * UREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS I
 * NTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRI
 * CT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF T
 * HE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "NBTTag.h"

int8_t& NBTTag::getType() { return type; };
int8_t& NBTTag::getByte() { return _byte; };
int16_t& NBTTag::getShort() { return _short; };
int32_t& NBTTag::getInt() { return _int; };
int64_t& NBTTag::getLong() { return _long; };
float_t& NBTTag::getFloat() { return _float; };
double_t& NBTTag::getDouble() { return _double; };
std::vector<char>& NBTTag::getByteArray() { return _byte_array; };
std::string& NBTTag::getString() { return _string; };
std::vector<NBTTag>& NBTTag::getList() { return list; };
std::map<std::string, NBTTag>& NBTTag::getMap() { return map; };
std::vector<int32_t>& NBTTag::getIntArray() { return _int_array; }
std::string& NBTTag::getName() { return name; };
bool& NBTTag::isNamed() { return is_named; };

