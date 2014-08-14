using System;

namespace SendMail
{
    class Program
    {
        static void Main(string[] args)
        {
            string result = SendMail.Send();
            Console.WriteLine(result);
            Console.ReadKey();
        }
    }
}
