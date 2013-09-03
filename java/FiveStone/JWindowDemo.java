package five;
import javax.swing.*;
import java.awt.*;
import java.net.*;

/**
* @ClassName: JWindowDemo
* @Description:������������
* @author �ܳ�
* @date ��󱣴����ڣ� 2011-3-22 ����03:13:15
*
*/
public  class JWindowDemo extends JWindow implements Runnable {
  Thread splashThread;  //�����������߳�
  JProgressBar progress; //������
  static boolean flag = false;
  
  public JWindowDemo() {
  	 Container container=getContentPane(); //�õ�����
    setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));  //���ù��}
    progress = new JProgressBar(1,100); //ʵ����������
    progress.setStringPainted(true); //�������
    progress.setString("��Ϸ����������,���Ժ�......");  //������ʾ����
    progress.setBackground(Color.white);  //���ñ���ɫ
    container.add(progress,BorderLayout.SOUTH);  //���ӽ�������������

    Dimension screen = getToolkit().getScreenSize();  //�õ���Ļ�ߴ�
    pack(); //������Ӧ����ߴ�
    setLocation((screen.width-getSize().width)/2,8*(screen.height-getSize().height)/11); //���ô���λ��
  }

  public void start(){
    this.toFront();  //����ǰ����ʾ
    splashThread=new Thread(this);  //ʵ�����߳�
    splashThread.start();  //��ʼ�����߳�
  }

  public void run(){
    setVisible(true); //��ʾ����
    try {
      for (int i=0;i<100;i++){
        Thread.sleep(100); //�߳�����
        progress.setValue(progress.getValue()+1); //���ý�����ֵ
      }
    }
    catch (Exception ex) {
      ex.printStackTrace();
    }
    dispose(); //�ͷŴ���
    flag = true;
    //showFrame(); //����������
  }
  public static void main(String[] args) {
    JWindowDemo splash = new JWindowDemo();
    splash.start();  //������������
  }
}

