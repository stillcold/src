using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EventDemo
{
    public delegate void DemoEventHandler(object sender, DemoEventArgs e);
    class Sender
    {
        public event DemoEventHandler DebugEvent;
        public void Debug(string info)
        {
            DemoEventArgs eventArgs = new DemoEventArgs(info);
            if (DebugEvent != null)
            {
                DebugEvent(this, eventArgs);
            }
        }
    }
    public class DemoEventArgs : EventArgs
    {
        private readonly string message;

        public string Message
        {
            get { return message; }
        }

        public DemoEventArgs(string message)
        {
            this.message = message;
        }
    }
}
