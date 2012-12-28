/*
 * TauNBT
 * NBTOutputStream.cpp
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

#include "NBTOutputStream.h"

NBTOutputStream::NBTOutputStream()
{
	system_endian_mode = getSystemEndianMode();
}


std::ostream& NBTOutputStream::operator<<(NBTTag tag)
{
	if(tag.getType() == NBTTag::TAG_END)
	{
		*this << tag.getType();
	}

	if(tag.getType() != NBTTag::TAG_END)
	{
		if(tag.isNamed())
		{
			*this << tag.getType();
			int16_t nameLength = tag.getName().size();
			*this << nameLength;
			if(nameLength != 0)
			{
				write(tag.getName().c_str(), nameLength);
			}
		}
		switch(tag.getType())
		{
			case NBTTag::TAG_BYTE:
			{
				*this << tag.getByte();
				break;
			}
			case NBTTag::TAG_SHORT:
			{
				*this << tag.getShort();
				break;
			}
			case NBTTag::TAG_INT:
			{
				*this << tag.getInt();
				break;
			}
			case NBTTag::TAG_LONG:
			{
				*this << tag.getLong();
				break;
			}
			case NBTTag::TAG_FLOAT:
			{
				*this << tag.getFloat();
				break;
			}
			case NBTTag::TAG_DOUBLE:
			{
				*this << tag.getDouble();
				break;
			}
			case NBTTag::TAG_BYTE_ARRAY:
			{
				int32_t len = tag.getByteArray().size();
				*this << len;
				char* ba = new char[len];
				for(int32_t i = 0; i < len; i++)
				{
					ba[i] = tag.getByteArray().at(i);
				}
				write(ba, len);
				break;
			}
			case NBTTag::TAG_STRING:
			{
				int16_t str_len = tag.getString().size();
				*this << str_len;
				write(tag.getString().c_str(), str_len);
				break;
			}
			case NBTTag::TAG_LIST:
			{
				int8_t tagId = tag.getList().at(0).getType();
				*this << tagId;
				int32_t l_len = tag.getList().size();
				*this << l_len;
				for(int i = 0; i < l_len; i++)
				{
					*this << tag.getList().at(i);
				}
				break;
			}
			case NBTTag::TAG_COMPOUND:
			{
				for(std::map<std::string, NBTTag>::iterator i = tag.getMap().begin(); i != tag.getMap().end(); i++)
				{
					*this << (*i).second;
				}
				NBTTag endTag;
				endTag.getType() = NBTTag::TAG_END;
				*this << endTag;
				break;
			}
		}
	}


	return *this;
}


std::ostream& NBTOutputStream::operator<<(int8_t val)
{
	char* buf = (char*)&val;
	write(buf, sizeof(int8_t));
	return *this;
}


std::ostream& NBTOutputStream::operator<<(int16_t val)
{
	char* buf = (char*)&val;
	if(getEndianMode() != system_endian_mode)
	{
		reverseBytes(buf,sizeof(int16_t));
	}
	write(buf, sizeof(int16_t));
	return *this;
}


std::ostream& NBTOutputStream::operator<<(int32_t val)
{
	char* buf = (char*)&val;
	if(getEndianMode() != system_endian_mode)
	{
		reverseBytes(buf,sizeof(int32_t));
	}
	write(buf, sizeof(int32_t));
	return *this;
}


std::ostream& NBTOutputStream::operator<<(int64_t val)
{
	char* buf = (char*)&val;
	if(getEndianMode() != system_endian_mode)
	{
		reverseBytes(buf,sizeof(int64_t));
	}
	write(buf, sizeof(int64_t));
	return *this;
}


std::ostream& NBTOutputStream::operator<<(float_t val)
{
	char* buf = (char*)&val;
	if(getEndianMode() != system_endian_mode)
	{
		reverseBytes(buf,sizeof(float_t));
	}
	write(buf, sizeof(float_t));
	return *this;
}


std::ostream& NBTOutputStream::operator<<(double_t val)
{
	char* buf = (char*)&val;
	if(getEndianMode() != system_endian_mode)
	{
		reverseBytes(buf,sizeof(float_t));
	}
	write(buf, sizeof(float_t));
	return *this;
}
