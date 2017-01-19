using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.Threading;

namespace SendMail
{
    class Program
    {
        private static uint number = 0;

        static Random random = new Random();

        private static string words = "峰鹤立鸡群众所周知每年春节过后全国各地都要同步上映一部大型灾难片，名字叫“开学”。这个学期我给大三的同学上课，为了减少上课的灾难性，提高课程的上座率，我对课程内容进行了调整。第一次上课前，我照例把课程计划发给学生，当天晚上就收到了同学们的短信。师您好！明天要上课了？可是我已经约好一家公司面试，这是家大公司，我从大一就在那边实习，现在终于有了面试机会，我不想放弃这个机会，所以我明天没法上课，要请一次假了，好吗？老师您好！怎么明天要上课？我不知道啊！我以为明天没课了，而且你知道，这两个月是我的旅游季，所以去年七月份我就买了去九寨沟的机票，今天就要出发，明天的课没法参加了，很抱歉向您请个假，祝您新学期愉快！老师您好！我现在九寨沟，和我们班上一位女生一起，我很喜欢她，追她追了两学年，她终于答应跟我一起出来玩，这次旅行对我很重要，比任何事情都重要，我怎么能错过这个机会呢？老师，你懂的！师~~您好呀~~嘻嘻~~我是您的学生啊~~知道我是谁吗~~嘿嘿~~就是每次上课都坐在最前面~~听课非常认真~~的那个~~小女生呀~~赫赫~~想起来了吗~~其实~~我好喜欢听你的课哦~~因为你是我见过的~~下课最准时的老师~~呵呵~~对了，老师~~我明天想请个假~~老师您好，我明天请假，因为我要考六级，我六级已经过了六次了，可是成绩不满意，所以我还要刷分，不停地刷，另外，我下周也请假，因为要考会计证，还有下下周是计算机证，还有律师证、导游证、驾驶证、普遍话证、工程师证、人力资源师证、各种证……老师，请假能团购吗？干脆我这学期都请假吧";

        static void Main(string[] args)
        {
            DoSend();
            Console.ReadKey();
        }

        private static void SmtpSendCompleted(object sender, AsyncCompletedEventArgs asyncCompletedEventArgs)
        {
            Console.WriteLine(number);
            number++;
            if (number < 7)
            {
                Thread.Sleep(5000);
                DoSend();
            }
        }

        private static void DoSend()
        {
            //"itcast0420@163.com","123456"
            string result = SendMail.Send("mr_kernel@163.com",
                                          "朱峰", "hzguanchao@corp.netease.com", GetTitle((uint)random.Next(5,10)),
                                          GetBody((uint)random.Next(30, 50)), "mr_kernel", "m@902117jd35zln", "smtp.163.com", "", SmtpSendCompleted);

            Console.WriteLine(result);
        }

        static string GetTitle(uint length)
        {
            StringBuilder sb = new StringBuilder();
            sb.Append(words[0]);
            for (int i = 0; i < length; i++)
            {
                
                sb.Append(words[random.Next(words.Length-1)]);
            }
            return sb.ToString();
        }

        static string GetBody(uint length)
        {
            StringBuilder sb = new StringBuilder();
            sb.Append(words[10]);
            for (int i = 0; i < length; i++)
            {

                sb.Append(words[random.Next(words.Length - 1)]);
            }
            return sb.ToString();
        }
    }
}
