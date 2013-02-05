/*
 * TauNBT
 * NBTInputStream.cpp
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

#include "NBTInputStream.h"


NBTInputStream::NBTInputStream()
{
	system_endian_mode = getSystemEndianMode();
}

std::istream& NBTInputStream::operator>>(NBTTag& tag)
{
	//if we dont know the next Tag's type, find it.
	if(tag.getType() == NBTTag::TAG_END)
	{
		int8_t type;
		*this >> type;
		tag.getType() = type;
	}
	if(tag.getType() != NBTTag::TAG_END)
	{
		if(tag.isNamed())
		{
			int16_t nameLength = 0;
			*this >> nameLength;
			if(nameLength != 0)
			{
				char* name = new char[nameLength];
				read(name, nameLength);
				tag.getName().assign(name, nameLength);
			}
		}
		switch(tag.getType())
		{
			case NBTTag::TAG_BYTE:
			{
				*this >> tag.getByte();
				break;
			}
			case NBTTag::TAG_SHORT:
			{
				*this >> tag.getShort();
				break;
			}
			case NBTTag::TAG_INT:
			{
				*this >> tag.getInt();
				break;
			}
			case NBTTag::TAG_LONG:
			{
				*this >> tag.getLong();
				break;
			}
			case NBTTag::TAG_FLOAT:
			{
				*this >> tag.getFloat();
				break;
			}
			case NBTTag::TAG_DOUBLE:
			{
				*this >> tag.getDouble();
				break;
			}
			case NBTTag::TAG_BYTE_ARRAY:
			{
				int32_t len;
				*this >> len;
				char* ba = new char[len];
				read(ba, len);
				for(int i = 0; i < len; i++)
				{
					tag.getByteArray().push_back(ba[i]);
				}
				break;
			}
			case NBTTag::TAG_STRING:
			{
				int16_t str_len;
				*this >> str_len;
				char* str = new char[str_len];
				read(str, str_len);
				tag.getString().assign(str, str_len);
				break;
			}
			case NBTTag::TAG_LIST:
			{
				int8_t tagId;
				*this >> tagId;
				//int t = tagId;
				int32_t l_len;
				*this >> l_len;
				for(int i = 0; i < l_len; i++)
				{
					NBTTag t;
					t.isNamed() = false;
					t.getType() = tagId;
					*this >> t;
					tag.getList().push_back(t);
				}
				break;
			}
			case NBTTag::TAG_COMPOUND:
			{
				bool endTagFound = false;
				while(!endTagFound && !eof())
				{
					NBTTag t;
					t.isNamed() = true;
					t.getType() = 0;
					*this >> t;
					if(t.getType() != NBTTag::TAG_END)
					{
						tag.getMap()[t.getName()] = t;
					}else{
						endTagFound = true;
					}
				}
				break;
			}
			case NBTTag::TAG_INT_ARRAY:
			{
				int32_t len;
				*this >> len;
				for(int i = 0; i < len; i++)
				{
					*this >> tag.getIntArray().at(i);
				}
				break;
			}
		}
	}
	return *this;
}

std::istream& NBTInputStream::operator>>(int8_t& val)
{
	char* buf = new char[sizeof(int8_t)];
	read(buf, sizeof(int8_t));
	val = *( (char*)(buf) );
	return *this;
}

std::istream& NBTInputStream::operator>>(int16_t& val)
{
	char* buf = new char[sizeof(int16_t)];
	read(buf, sizeof(int16_t));
	if(getEndianMode() != system_endian_mode)
	{
		reverseBytes(buf,sizeof(int16_t));
	}
	val = *( (short*)(buf) );
	return *this;
}

std::istream& NBTInputStream::operator>>(int32_t& val)
{
	char* buf = new char[sizeof(int32_t)];
	read(buf, sizeof(int32_t));
	if(getEndianMode() != system_endian_mode)
	{
		reverseBytes(buf,sizeof(int32_t));
	}
	val = *( (int*)(buf) );
	return *this;
}

std::istream& NBTInputStream::operator>>(int64_t& val)
{
	char* buf = new char[sizeof(int64_t)];
	read(buf, sizeof(int64_t));
	if(getEndianMode() != system_endian_mode)
	{
		reverseBytes(buf,sizeof(int64_t));
	}
	val = *( (long*)(buf) );
	return *this;
}

std::istream& NBTInputStream::operator>>(float_t& val)
{
	char* buf = new char[sizeof(float_t)];
	read(buf, sizeof(float_t));
	if(getEndianMode() != system_endian_mode)
	{
		reverseBytes(buf,sizeof(float_t));
	}
	val = *( (float*)(buf) );
	return *this;
}

std::istream& NBTInputStream::operator>>(double_t& val)
{
	char* buf = new char[sizeof(double_t)];
	read(buf, sizeof(double_t));
	if(getEndianMode() != system_endian_mode)
	{
		reverseBytes(buf,sizeof(double_t));
	}
	val = *( (double*)(buf) );
	return *this;
}
