#include "CSendMail.h"
#include "stdio.h"
int main()
{
    char pwd[100];
    char username[100];
    char mailto[100];
    char mailfrom[100];
    char subject[100];
    char body[1000];
    CSendMail C163sendMail;


    printf ("Please input username\n");
    scanf ("%s",username);
    printf ("Please input password\n");
    scanf ("%s",pwd);
    printf ("Please input the email you want to send mail\n");
    scanf ("%s",mailto);
    printf ("Please input the email you want to use\n");
    scanf ("%s",mailfrom);
    printf ("Please input the subject\n");
    scanf ("%s",subject);
    printf ("Please input the body\n");
    scanf ("%s",body);
    
	C163sendMail.SendMail(
			username,
			pwd,
			"smtp.163.com",//	const std::string & strSmtpServer, 
			25,//	int iPort, 
			mailto, //MailTo
			mailfrom, //MailFrom
			subject,	//Subject, 
			body	//MailBody
			);
	return 0;
}
