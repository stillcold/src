using System;

namespace SendMail
{
    class Program
    {
        static void Main(string[] args)
        {
            string result = SendMail.Send("mr_kernel@163.com",
                          "chao.guan", "773678279@qq.com", "主题",
                          "主体", "mr_kernel", "m@902117jd35zln", "smtp.163.com", "");
            Console.WriteLine(result);
            Console.ReadKey();
        }
    }
}
