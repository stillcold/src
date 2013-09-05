package FiveStone;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Toolkit;
import java.util.Timer;
import java.util.TimerTask;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JWindow;

/**
* @ClassName: GSplashWindow
* @Description: 启动画面类
* @author 管超
* @date 最后保存日期： 2011-3-22 下午03:13:52
*
*/
public class GSplashWindow extends JWindow {
	int tick = 0;
    
    /** 当前状态信息 */
    JLabel status = null;
    
    /** 背景图像 */
    private Image bgImage = null;
    
    /**
     * 通过路径构造启动画面
     * 
     * @param imgPath 背景图像路径
     */
    public GSplashWindow(String imgPath) {
        this.bgImage = new ImageIcon(imgPath).getImage();
        initComponents();
    }
    
    /**
     * 通过图像对象构造启动画面
     * 
     * @param bgImage 背景图像对象
     */
    public GSplashWindow(Image bgImage) {
        this.bgImage = bgImage;
        initComponents();
    }
    
    private void initComponents() {
        // 获取图片尺寸
        int imgWidth = bgImage.getWidth(this);
        int imgHeight = bgImage.getHeight(this);
        
        // 设置窗口大小
        setSize(imgWidth, imgHeight);
        
        // 设置窗口背景
        JPanel background = new JPanel() {
            protected void paintChildren(Graphics g) {
                g.drawImage(bgImage, 0, 0, this);
                super.paintChildren(g);
            }
        };
        background.setLayout(new BorderLayout());
        setContentPane(background);
        
        // 设置窗口位置 
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension scmSize = toolkit.getScreenSize();
        setLocation(scmSize.width / 2 - imgWidth / 2, 
                scmSize.height / 2 - imgHeight / 2);
        
        // 加入状态条
        status = new JLabel("状态条..........", JLabel.RIGHT);
        status.setForeground(Color.WHITE);
        status.setBorder(BorderFactory.createEmptyBorder(4, 4, 4, 4));
        getContentPane().add(status, "South");
    }
    
    public void start() {
        setVisible(true);
        toFront();
        Timer time = new Timer(false);
		time.schedule(new TimerTask() {
			public void run() {

				if ( tick == 3) {
					setStatus("配置预设……");
				}
				else if ( tick == 6) {
					setStatus("读取历史……");
				}else if ( tick == 9) {
					setStatus("欢迎使用，祝开心！");
				}
				tick++;
			}

		}, 0, 1000);
    }
    
    /**
     * 设置状态信息
     * 
     * @param statusText 状态信息
     */
    public void setStatus(String statusText) {
        status.setText(statusText);
    }
    
    public void stop() {
        setVisible(false);
        dispose();
    }
}
