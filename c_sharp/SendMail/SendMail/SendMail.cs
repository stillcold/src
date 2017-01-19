﻿using System;
using System.Net.Mail;
using System.Text;

namespace SendMail
{
    class SendMail
    {
        /// <summary> 
        /// 发送邮件程序 
        /// </summary> 
        /// <param name="from">发送人邮件地址</param> 
        /// <param name="fromname">发送人显示名称</param> 
        /// <param name="to">发送给谁（邮件地址）</param> 
        /// <param name="subject">标题</param> 
        /// <param name="body">内容</param> 
        /// <param name="username">邮件登录名</param> 
        /// <param name="password">邮件密码</param> 
        /// <param name="server">邮件服务器</param> 
        /// <param name="fujian">附件</param> 
        /// <returns>send ok</returns> 
        /// 调用方法 Send("abc@126.com", "某某人", "cba@126.com", "你好", "我测试下邮件", "邮箱登录名", "邮箱密码", "smtp.126.com", ""); 
        public static string Send(string from, string fromname, string to, string subject, string body, string username, string password, string server, string fujian, SendCompletedEventHandler smtp_SendCompleted)
        {

            try
            {
                //邮件发送类 
                MailMessage mail = new MailMessage();
                //是谁发送的邮件 
                mail.From = new MailAddress(from, fromname);
                //发送给谁 
                mail.To.Add(to);
                //标题 
                mail.Subject = subject;
                //内容编码 
                mail.BodyEncoding = Encoding.Default;
                //发送优先级 
                mail.Priority = MailPriority.High;
                //邮件内容 
                mail.Body = body;
                //是否HTML形式发送 
                mail.IsBodyHtml = true;
                //附件 
                if (fujian.Length > 0)
                {
                    mail.Attachments.Add(new Attachment(fujian));
                }
                //邮件服务器和端口 
                SmtpClient smtp = new SmtpClient();
                smtp.Host = "smtp.163.com";
                smtp.UseDefaultCredentials = true;
                //指定发送方式 
                smtp.DeliveryMethod = SmtpDeliveryMethod.Network;
                //指定登录名和密码 
                smtp.Credentials = new System.Net.NetworkCredential(username, password);
                //超时时间 
                smtp.Timeout = 10000;
                //smtp.Send(mail);
                smtp.SendCompleted += smtp_SendCompleted;
                smtp.SendAsync(mail,null);
                return "send ok";
            }
            catch (Exception exp)
            {
                return exp.Message;
            }
        }
    }
}
