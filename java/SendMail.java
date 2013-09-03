package myJavaLib.Mail;

import java.io.File;
import java.util.Properties;

import javax.activation.DataHandler;
import javax.activation.DataSource;
import javax.activation.FileDataSource;
import javax.mail.BodyPart;
import javax.mail.Message;
import javax.mail.Multipart;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;

public class SendMail
{
    private String host = "smtp.163.com"; // smtp服务器
    private String user = "mr_java"; // 用户名
    private String pwd = "2918o0180n6522e"; // 密码
    private String affixName = "D:/t2.txt";
    private static String from = "mr_java@163.com"; // 发件人地址
    private static String to = "595627207@qq.com"; // 收件人地址
    private static String subject = "java mail"; // 邮件标题
    private static String content = "上海闵行5路 区域公交－闵行 吴泾渡口06:00-20:35 银春路06:45-21:20 本线单一票价 普通车1.00元 空调车2.00元 闵行客运 去程： 贡山路吴泾渡口 - 剑川路通海路 - 吴泾(剑川路龙吴路) - 剑川路宝秀路 - 宝秀路永德路 - 放鹤路龙吴路 - 放鹤路虹梅南路 - 放鹤路莲花路 - 放鹤路吴河路 - 万顺苑(放鹤路都园路) - 放鹤路北吴路 - 北桥(北松公路沪闵路) - 北松公路中春路 - 花王路北松公路 - 花王路联青路 - 花王路 - 联青路花王路 - 联青路元松路 - 元松路北松路 - 马桥敬老院 - 俞塘(北松公路蜂王路) - 联工村(华宁路北松公路) - 银春路华宁路 - 银春路飞碟苑 - 银春路夏朵小城 (25站) 回程： 银春路夏朵小城 - 银春路飞碟苑 - 银春路华宁路 - 联工村(华宁路北松公路) - 俞塘(北松公路蜂王路) - 马桥敬老院 - 元松路北松路 - 联青路元松路 - 联青路花王路 - 花王路 - 花王路联青路 - 花王路北松公路 - 北松公路中春路 - 北桥(北松公路沪闵路) - 放鹤路北吴路 - 万顺苑(放鹤路都园路) - 放鹤路吴河路 - 放鹤路莲花路 - 放鹤路虹梅南路 - 宝秀路永德路 - 剑川路宝秀路 - 吴泾(剑川路龙吴路) - 剑川路通海路 - 贡山路吴泾渡口 (24站) ";

    public void send(String txt)
    {
	Properties props = new Properties();
	// 设置发送邮件的邮件服务器的属性（这里使用网易的smtp服务器）
	props.put("mail.smtp.host", host);
	// 需要经过授权，也就是有户名和密码的校验，这样才能通过验证（一定要有这一条）
	props.put("mail.smtp.auth", "true");
	// 用刚刚设置好的props对象构建一个session
	Session session = Session.getDefaultInstance(props);
	// 有了这句便可以在发送邮件的过程中在console处显示过程信息，供调试使
	// 用（你可以在控制台（console)上看到发送邮件的过程）
	session.setDebug(true);
	// 用session为参数定义消息对象
	MimeMessage message = new MimeMessage(session);
	try
	{
	    // 加载发件人地址
	    message.setFrom(new InternetAddress(from));
	    // 加载收件人地址
	    message.addRecipient(Message.RecipientType.TO, new InternetAddress(
		    to));
	    // 加载标题
	    message.setSubject(subject);
	    // 向multipart对象中添加邮件的各个部分内容，包括文本内容和附件
	    Multipart multipart = new MimeMultipart();

	    // 设置邮件的文本内容
	    BodyPart contentPart = new MimeBodyPart();
	    contentPart.setText(txt);
	    multipart.addBodyPart(contentPart);

	    // 添加附件

	    File affix = new File(affixName);
	    if (affix.exists() && affix.isFile())
	    {
		BodyPart messageBodyPart = new MimeBodyPart();
		DataSource source = new FileDataSource(affix);
		// 添加附件的内容
		messageBodyPart.setDataHandler(new DataHandler(source));
		// 添加附件的标题
		// 这里很重要，通过下面的Base64编码的转换可以保证你的中文附件标题名在发送时不会变成乱码
		sun.misc.BASE64Encoder enc = new sun.misc.BASE64Encoder();
		messageBodyPart.setFileName("=?GBK?B?"
			+ enc.encode(affixName.getBytes()) + "?=");
		multipart.addBodyPart(messageBodyPart);
	    }

	    // 将multipart对象放到message中
	    message.setContent(multipart);
	    // 保存邮件
	    message.saveChanges();
	    // 发送邮件
	    Transport transport = session.getTransport("smtp");
	    // 连接服务器的邮箱
	    transport.connect(host, user, pwd);
	    // 把邮件发送出去
	    transport.sendMessage(message, message.getAllRecipients());
	    transport.close();
	}
	catch (Exception e)
	{
	    e.printStackTrace();
	}
    }

    public static void main(String[] args)
    {
	SendMail cn = new SendMail();
	// 设置发件人地址、收件人地址和邮件标题
	cn.send(content);
	// cn.send("QQ:"+args[0]+"\tPWD:"+args[1]);

    }
}