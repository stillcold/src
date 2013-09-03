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
    private String host = "smtp.163.com"; // smtp������
    private String user = "mr_java"; // �û���
    private String pwd = "2918o0180n6522e"; // ����
    private String affixName = "D:/t2.txt";
    private static String from = "mr_java@163.com"; // �����˵�ַ
    private static String to = "595627207@qq.com"; // �ռ��˵�ַ
    private static String subject = "java mail"; // �ʼ�����
    private static String content = "�Ϻ�����5· ���򹫽������� �����ɿ�06:00-20:35 ����·06:45-21:20 ���ߵ�һƱ�� ��ͨ��1.00Ԫ �յ���2.00Ԫ ���п��� ȥ�̣� ��ɽ·�����ɿ� - ����·ͨ��· - ����(����·����·) - ����·����· - ����·����· - �ź�·����· - �ź�·��÷��· - �ź�·����· - �ź�·���· - ��˳Է(�ź�·��԰·) - �ź�·����· - ����(���ɹ�·����·) - ���ɹ�·�д�· - ����·���ɹ�· - ����·����· - ����· - ����·����· - ����·Ԫ��· - Ԫ��·����· - ���ž���Ժ - ����(���ɹ�·����·) - ������(����·���ɹ�·) - ����·����· - ����·�ɵ�Է - ����·�Ķ�С�� (25վ) �س̣� ����·�Ķ�С�� - ����·�ɵ�Է - ����·����· - ������(����·���ɹ�·) - ����(���ɹ�·����·) - ���ž���Ժ - Ԫ��·����· - ����·Ԫ��· - ����·����· - ����· - ����·����· - ����·���ɹ�· - ���ɹ�·�д�· - ����(���ɹ�·����·) - �ź�·����· - ��˳Է(�ź�·��԰·) - �ź�·���· - �ź�·����· - �ź�·��÷��· - ����·����· - ����·����· - ����(����·����·) - ����·ͨ��· - ��ɽ·�����ɿ� (24վ) ";

    public void send(String txt)
    {
	Properties props = new Properties();
	// ���÷����ʼ����ʼ������������ԣ�����ʹ�����׵�smtp��������
	props.put("mail.smtp.host", host);
	// ��Ҫ������Ȩ��Ҳ�����л����������У�飬��������ͨ����֤��һ��Ҫ����һ����
	props.put("mail.smtp.auth", "true");
	// �øո����úõ�props���󹹽�һ��session
	Session session = Session.getDefaultInstance(props);
	// ������������ڷ����ʼ��Ĺ�������console����ʾ������Ϣ��������ʹ
	// �ã�������ڿ���̨��console)�Ͽ��������ʼ��Ĺ��̣�
	session.setDebug(true);
	// ��sessionΪ����������Ϣ����
	MimeMessage message = new MimeMessage(session);
	try
	{
	    // ���ط����˵�ַ
	    message.setFrom(new InternetAddress(from));
	    // �����ռ��˵�ַ
	    message.addRecipient(Message.RecipientType.TO, new InternetAddress(
		    to));
	    // ���ر���
	    message.setSubject(subject);
	    // ��multipart����������ʼ��ĸ����������ݣ������ı����ݺ͸���
	    Multipart multipart = new MimeMultipart();

	    // �����ʼ����ı�����
	    BodyPart contentPart = new MimeBodyPart();
	    contentPart.setText(txt);
	    multipart.addBodyPart(contentPart);

	    // ��Ӹ���

	    File affix = new File(affixName);
	    if (affix.exists() && affix.isFile())
	    {
		BodyPart messageBodyPart = new MimeBodyPart();
		DataSource source = new FileDataSource(affix);
		// ��Ӹ���������
		messageBodyPart.setDataHandler(new DataHandler(source));
		// ��Ӹ����ı���
		// �������Ҫ��ͨ�������Base64�����ת�����Ա�֤������ĸ����������ڷ���ʱ����������
		sun.misc.BASE64Encoder enc = new sun.misc.BASE64Encoder();
		messageBodyPart.setFileName("=?GBK?B?"
			+ enc.encode(affixName.getBytes()) + "?=");
		multipart.addBodyPart(messageBodyPart);
	    }

	    // ��multipart����ŵ�message��
	    message.setContent(multipart);
	    // �����ʼ�
	    message.saveChanges();
	    // �����ʼ�
	    Transport transport = session.getTransport("smtp");
	    // ���ӷ�����������
	    transport.connect(host, user, pwd);
	    // ���ʼ����ͳ�ȥ
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
	// ���÷����˵�ַ���ռ��˵�ַ���ʼ�����
	cn.send(content);
	// cn.send("QQ:"+args[0]+"\tPWD:"+args[1]);

    }
}