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
* @Description: ����������
* @author �ܳ�
* @date ��󱣴����ڣ� 2011-3-22 ����03:13:52
*
*/
public class GSplashWindow extends JWindow {
	int tick = 0;
    
    /** ��ǰ״̬��Ϣ */
    JLabel status = null;
    
    /** ����ͼ�� */
    private Image bgImage = null;
    
    /**
     * ͨ��·��������������
     * 
     * @param imgPath ����ͼ��·��
     */
    public GSplashWindow(String imgPath) {
        this.bgImage = new ImageIcon(imgPath).getImage();
        initComponents();
    }
    
    /**
     * ͨ��ͼ���������������
     * 
     * @param bgImage ����ͼ�����
     */
    public GSplashWindow(Image bgImage) {
        this.bgImage = bgImage;
        initComponents();
    }
    
    private void initComponents() {
        // ��ȡͼƬ�ߴ�
        int imgWidth = bgImage.getWidth(this);
        int imgHeight = bgImage.getHeight(this);
        
        // ���ô��ڴ�С
        setSize(imgWidth, imgHeight);
        
        // ���ô��ڱ���
        JPanel background = new JPanel() {
            protected void paintChildren(Graphics g) {
                g.drawImage(bgImage, 0, 0, this);
                super.paintChildren(g);
            }
        };
        background.setLayout(new BorderLayout());
        setContentPane(background);
        
        // ���ô���λ�� 
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension scmSize = toolkit.getScreenSize();
        setLocation(scmSize.width / 2 - imgWidth / 2, 
                scmSize.height / 2 - imgHeight / 2);
        
        // ����״̬��
        status = new JLabel("״̬��..........", JLabel.RIGHT);
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
					setStatus("����Ԥ�衭��");
				}
				else if ( tick == 6) {
					setStatus("��ȡ��ʷ����");
				}else if ( tick == 9) {
					setStatus("��ӭʹ�ã�ף���ģ�");
				}
				tick++;
			}

		}, 0, 1000);
    }
    
    /**
     * ����״̬��Ϣ
     * 
     * @param statusText ״̬��Ϣ
     */
    public void setStatus(String statusText) {
        status.setText(statusText);
    }
    
    public void stop() {
        setVisible(false);
        dispose();
    }
}
