using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;

namespace LiongStudio.Script
{
    public class Script
    {
		string script;
		StringReader reader;
		Dictionary<string, byte> roleDict = new Dictionary<string, byte>();
		string focus = "";

        public Script(string path)
        {
			StreamReader sr = new StreamReader(path);
			this.script = sr.ReadToEnd();
			reader = new StringReader(this.script);
        }
        public Script(Stream stream)
		{
			StreamReader sr = new StreamReader(stream);
			this.script = sr.ReadToEnd();
			reader = new StringReader(this.script);
		}
		public Script(string script, StringReader sr)
		{
			this.script = script;
			reader = sr;
		}

		public void NextDialog()
		{
			string line = reader.ReadLine();
			Match match;

			match= new Regex(@"(?<char>\S+)?\s*:", RegexOptions.Compiled).Match(line);
			if (match.Success)
			{
				focus = match.Groups["char"].Value;
				return;
			}

			match = new Regex(@"at\s*(\s*(?<x>[0-9]+)?%\s*,\s*(?<y>[0-9]+)?%\s*)", RegexOptions.Compiled).Match(line);
			if (match.Success)
			{
				InteropController.Position position;
				position.X = Convert.ToDouble(match.Groups["x"].Value);
				position.Y = Convert.ToDouble(match.Groups["y"].Value);
				InteropController.InteropController.SetPosition(position);
				return;
			}

			match = new Regex(@"oF\s*(\s*(?<width>[0-9]+)?%\s*,\s*(?<height>[0-9]+)?%\s*)", RegexOptions.Compiled).Match(line);
			if (match.Success)
			{
				InteropController.Size size;
				size.Width = Convert.ToDouble(match.Groups["x"].Value);
				size.Height = Convert.ToDouble(match.Groups["y"].Value);
				InteropController.InteropController.SetSize(size);
				return;
			}

			match = new Regex(@"[\s*(?<textid>[0-9]+)?\s*]", RegexOptions.Compiled).Match(line);
			if (match.Success)
			{
				InteropController.InteropController.SwitchCharacterImageID(Convert.ToUInt32(match));
				return;
			}

			InteropController.InteropController.ChangeLine(line);
		}
	}
}
