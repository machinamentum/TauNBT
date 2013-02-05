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

