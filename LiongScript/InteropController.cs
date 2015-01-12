using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace LiongStudio.Script.InteropController
{
	enum CharacterDisplayMode
	{
		Normal = 1,
		UpsideDown = 2,
		Hidden = 0
	}
	enum CharacterFX
	{
		Inherit = 0,
		Normal = 1,
		Shaky = 2,
		Flowing = 3,
		Abnormal = 4,
		ExAbnormal = 5,
		ExExAbnormal = 6
	}
	[StructLayout(LayoutKind.Sequential)]
	public struct Position
	{
		public double X;
		public double Y;
	}
	[StructLayout(LayoutKind.Sequential)]
	public struct Size
	{
		public double Width;
		public double Height;
	}

	class InteropController
	{
		#region LiongUI
		[DllImport(@"LiongUI.dll")]
		public static extern void SwitchCharacterFX([MarshalAs(UnmanagedType.LPWStr)]string name, [MarshalAs(UnmanagedType.SysInt)]CharacterDisplayMode displaymode);
		[DllImport(@"LiongUI.dll")]
		public static extern void SetPosition([MarshalAs(UnmanagedType.Struct)]Position position);
		[DllImport(@"LiongUI.dll")]
		public static extern void SetSize([MarshalAs(UnmanagedType.Struct)]Size size);
		[DllImport(@"LiongUI.dll")]
		public static extern void SwitchCharacterImageID([MarshalAs(UnmanagedType.SysUInt)]uint textID);
		[DllImport(@"LiongUI.dll")]
		public static extern void ChangeLine([MarshalAs(UnmanagedType.LPWStr)]string line);
		#endregion

		#region LiongGL
		[DllImport(@"LiongGL.dll")]
		public static extern void SwitchBackGroundImage();
		#endregion
	}
}
