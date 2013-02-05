using System;
using System.Collections;
namespace TauNBT
{
	public class NBTTag
	{

		public enum TagType
		{
			End = 0,
			Byte = 1,
			Short = 2,
			Int = 3,
			Long = 4,
			Float = 5,
			Double = 6,
			ByteArray = 7,
			String = 8,
			List = 9,
			Compound = 10,
			IntArray = 11,
			Unknown = 0xFF,
		}

		private TagType type = TagType.End;

		private byte _byte;
		private Int16 _short;
		private Int32 _int;
		private Int64 _long;
		private Single _float;
		private Double _double;
		private byte[] _byte_array;
		private String _string;
		private NBTTag[] _list;
		private Hashtable _compound;
		private Int32[] _int_array;

		protected String name;

		public NBTTag (TagType type = TagType.End)
		{
			this.type = type;
			name = "";
			Compound = new Hashtable();
		}

		public override string ToString ()
		{
			string ret = new string((name + ": " + type + ": ").ToCharArray());
			switch (type) {
			case NBTTag.TagType.Byte:
				ret += Byte;
				break;
			case NBTTag.TagType.Short:
				ret += Short;
				break;
			case NBTTag.TagType.Int:
				ret += Int;
				break;
			case NBTTag.TagType.Long:
				ret += Long;
				break;
			case NBTTag.TagType.Float:
				ret += Float;
				break;
			case NBTTag.TagType.Double:
				ret += Double;
				break;
			case NBTTag.TagType.ByteArray:
				ret += "{ ";
				for(int i = 0; i < ByteArray.Length; i++) {
					ret += ByteArray[i];
				}
				ret += " }";
				break;
			case NBTTag.TagType.String:
				ret += String;
				break;
			case NBTTag.TagType.List:
				ret += "{\n";
				for(int i = 0; i < List.Length; i++) {
					ret += List[i].ToString("     ");
				}
				ret += "}";
				break;
			case NBTTag.TagType.Compound:
				ret += "{\n";
				foreach(NBTTag t in Compound.Values) {
					ret += t.ToString("     ");
				}
				ret += "}";
				break;
			case NBTTag.TagType.IntArray:
				throw new NotImplementedException("IntArray");
				//break;
			}
			return ret + "\n";
		}

		private string ToString(string prefix)
		{
			return prefix + ToString ();
		}

		public TagType Type {
			get {
				return type;
			}
			set {
				type = value;
			}
		}

		public String Name {
			get {
				return name;
			}
			set {
				name = value;
			}
		}

		public byte Byte {
			get {
				return _byte;
			}
			set {
				_byte = value;
			}
		}

		public Int16 Short {
			get {
				return _short;
			}
			set {
				_short = value;
			}
		}

		public Int32 Int {
			get {
				return _int;
			}
			set {
				_int = value;
			}
		}

		public Int64 Long {
			get {
				return _long;
			}
			set {
				_long = value;
			}
		}

		public Single Float {
			get {
				return _float;
			}
			set {
				_float = value;
			}
		}

		public Double Double {
			get {
				return _double;
			}
			set {
				_double = value;
			}
		}

		public byte[] ByteArray {
			get {
				return _byte_array;
			}
			set {
				_byte_array = value;
			}
		}

		public String String {
			get {
				return _string;
			}
			set {
				_string = value;
			}
		}

		public NBTTag[] List {
			get {
				return _list;
			}
			set {
				_list = value;
			}
		}

		public Hashtable Compound {
			get {
				return _compound;
			}
			set {
				_compound = value;
			}
		}

		public Int32[] IntArray {
			get {
				return _int_array;
			}
			set {
				_int_array = value;
			}
		}

	}
}

