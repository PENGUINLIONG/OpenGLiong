using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;

namespace LiongStudio.Script
{
    class Script
    {
        private string objectID;
        private string version;
        private ArrayList lines;
        private StreamReader stream;
        private ScriptTranslater translater;

        Script(string path)
        {
            if (File.Exists(path))
                stream = new StreamReader(path);
            else
                throw new FileNotFoundException();
            lines = new ArrayList();
            try
            {
                InitHeader();
            }
            catch (BadScriptFormatException e)
            {
                Console.WriteLine("An exception has been occured: " + e.Message);
            }
        }

        private void InitHeader()
        {
            if (stream.ReadLine() != "GaLS")
                throw new BadScriptFormatException("Not GaLiong Script file at all.");
            string temp;
            temp = stream.ReadLine();
            Match match = (new Regex(@"Version\s*=\s*(?<version>\S+)?\s*\|\s*Object\s*=\s*(?<object>\S+)?")).Match(temp);
            version = match.Result("${version}");
            objectID = match.Result("${object}");
            if (version == "" || objectID == "")
                throw new BadScriptFormatException("No Version and(or) ObjectID.");
        }

        void ReadScript()
        {
            foreach(string line in stream.ReadToEnd().Split('\n'))
            {
                foreach (Match match in new Regex(@"\S+").Matches(line))
                {
                    
                }
            }
        }
    }
}
