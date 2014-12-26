using System;
using System.Collections.Generic;
using System.Runtime.Serialization;
using System.Text;

namespace LiongStudio.Script
{
    class BadScriptFormatException : SystemException
    {

        public BadScriptFormatException()
            : base()
        {
        }

        public BadScriptFormatException(string message)
            : base(message)
        {
        }

        protected BadScriptFormatException(SerializationInfo info, StreamingContext context)
            : base(info, context)
        {
        }

        public BadScriptFormatException(string message, Exception innerException)
            : base(message, innerException)
        {
        }
    }
}
