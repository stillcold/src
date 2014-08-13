using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EventDemo
{
    class Subscriber
    {
        private string id;
        public Subscriber(string id, Sender sender)
        {
            this.id = id;

            //步骤6．用+=操作符添加事件到事件队列中（-=操作符能够将事件从队列中删除）。
            sender.DebugEvent += new DemoEventHandler(MyEvent);
        }

        //步骤5，定义事件处理方法
        void MyEvent(object sender, DemoEventArgs e)
        {
            Console.WriteLine(id + " received this message: {0}", e.Message);
        }
    }
}
