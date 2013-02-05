/*
 * TauNBT
 * NBTReader.cs
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


using System;
using System.IO;
using System.Text;

namespace TauNBT
{
	public class NBTReader : BinaryReader
	{
		private EndianMode endianMode;

		public NBTReader (FileStream f, Encoding e, EndianMode mode = EndianMode.Big) : base(f, e)
		{
			EndianMode = mode;

		}

		public NBTTag ReadNBTTag ()
		{
			return ReadNamedTag();
		}

		public NBTTag ReadNamedTag (NBTTag.TagType type = NBTTag.TagType.Unknown)
		{
			NBTTag tag = new NBTTag (type);
			if (type == NBTTag.TagType.Unknown) {
				tag.Type = (NBTTag.TagType)ReadByte ();
			}



			if (tag.Type != NBTTag.TagType.End) {
				Int16 nameLength = ReadInt16();
				tag.Name = new String(ReadChars(nameLength));
#if DEBUG
				Console.WriteLine(tag.Name + ": " + tag.Type);
#endif
				ReadTagValue(tag);
			}


			return tag;
		}


		public NBTTag ReadUnnamedTag(NBTTag.TagType type = NBTTag.TagType.Unknown) {
			NBTTag tag = new NBTTag (type);
			if (type == NBTTag.TagType.Unknown) {
				tag.Type = (NBTTag.TagType)ReadByte ();
			}

			
			if (tag.Type != NBTTag.TagType.End) {
#if DEBUG
				Console.WriteLine(tag.Type);
#endif
				ReadTagValue(tag);
			}

			return tag;
		}

		private void ReadTagValue (NBTTag tag)
		{
			switch(tag.Type) {
			case NBTTag.TagType.Byte:
				tag.Byte = ReadByte();
				break;
			case NBTTag.TagType.Short:
				tag.Short = ReadInt16();
				break;
			case NBTTag.TagType.Int:
				tag.Int = ReadInt32();
				break;
			case NBTTag.TagType.Long:
				tag.Long = ReadInt64();
				break;
			case NBTTag.TagType.Float:
				tag.Float = ReadSingle();
				break;
			case NBTTag.TagType.Double:
				tag.Double = ReadDouble();
				break;
			case NBTTag.TagType.ByteArray:
				tag.ByteArray = ReadBytes(ReadInt32());
				break;
			case NBTTag.TagType.String:
				tag.String = new String(ReadChars(ReadInt16()));
				break;
			case NBTTag.TagType.List:
				NBTTag.TagType tagType = (NBTTag.TagType)ReadByte ();
				Int32 length = ReadInt32();
				tag.List = new NBTTag[length];
				for(int j = 0; j < length; j++) {
					tag.List[j] = ReadUnnamedTag(tagType);
				}
				break;
			case NBTTag.TagType.Compound:
				bool endTagFound = false;
				while(!endTagFound)
				{
					NBTTag _tag = ReadNamedTag();
					if(_tag.Type != NBTTag.TagType.End) {
						tag.Compound[_tag.Name] = _tag;
					}else{
						endTagFound = true;
					}
				}
				break;
			case NBTTag.TagType.IntArray:
				throw new NotImplementedException("IntArray");
				//break;
			}
		}


		public override short ReadInt16 ()
		{
			return endianMode == EndianMode.Big ? BitConverter.ToInt16(ReverseBytes(ReadBytes(2)), 0) : base.ReadInt16();
		}

		public override int ReadInt32 ()
		{
			return endianMode == EndianMode.Big ? BitConverter.ToInt32(ReverseBytes(ReadBytes(4)), 0) : base.ReadInt32();
		}


		public override long ReadInt64 ()
		{
			return endianMode == EndianMode.Big ? BitConverter.ToInt64(ReverseBytes(ReadBytes(8)), 0) : base.ReadInt64();
		}

		public override float ReadSingle ()
		{
			return endianMode == EndianMode.Big ? BitConverter.ToSingle(ReverseBytes(ReadBytes(4)), 0) : base.ReadSingle();
		}

		public override double ReadDouble ()
		{
			return endianMode == EndianMode.Big ? BitConverter.ToDouble(ReverseBytes(ReadBytes(8)), 0) : base.ReadDouble();
		}


		private byte[] ReverseBytes (byte[] b)
		{
			Array.Reverse(b);
			return b;
		}

		public EndianMode EndianMode {
			get {
				return endianMode;
			}
			set {
				endianMode = value;
			}
		}

	}
}

