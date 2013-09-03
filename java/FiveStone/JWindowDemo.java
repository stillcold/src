package five;
import javax.swing.*;
import java.awt.*;
import java.net.*;

/**
* @ClassName: JWindowDemo
* @Description:程序启动界面
* @author 管超
* @date 最后保存日期： 2011-3-22 下午03:13:15
*
*/
public  class JWindowDemo extends JWindow implements Runnable {
  Thread splashThread;  //进度条更新线程
  JProgressBar progress; //进度条
  static boolean flag = false;
  
  public JWindowDemo() {
  	 Container container=getContentPane(); //得到容器
    setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));  //设置光标}
    progress = new JProgressBar(1,100); //实例化进度条
    progress.setStringPainted(true); //描绘文字
    progress.setString("游戏正在启动中,请稍候......");  //设置显示文字
    progress.setBackground(Color.white);  //设置背景色
    container.add(progress,BorderLayout.SOUTH);  //增加进度条到容器上

    Dimension screen = getToolkit().getScreenSize();  //得到屏幕尺寸
    pack(); //窗口适应组件尺寸
    setLocation((screen.width-getSize().width)/2,8*(screen.height-getSize().height)/11); //设置窗口位置
  }

  public void start(){
    this.toFront();  //窗口前端显示
    splashThread=new Thread(this);  //实例化线程
    splashThread.start();  //开始运行线程
  }

  public void run(){
    setVisible(true); //显示窗口
    try {
      for (int i=0;i<100;i++){
        Thread.sleep(100); //线程休眠
        progress.setValue(progress.getValue()+1); //设置进度条值
      }
    }
    catch (Exception ex) {
      ex.printStackTrace();
    }
    dispose(); //释放窗口
    flag = true;
    //showFrame(); //运行主程序
  }
  public static void main(String[] args) {
    JWindowDemo splash = new JWindowDemo();
    splash.start();  //运行启动界面
  }
}

