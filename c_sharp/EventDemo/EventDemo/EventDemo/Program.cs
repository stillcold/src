using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EventDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            Sender sender = new Sender();
            Subscriber subscriber1 = new Subscriber("1",sender);
            Subscriber subscriber2 = new Subscriber("2",sender);
            sender.Debug("demo");
            Console.ReadKey();
        }
    }
}
