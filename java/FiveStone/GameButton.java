package FiveStone;

import java.applet.Applet;
import java.applet.AudioClip;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Shape;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.geom.Ellipse2D;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JPanel;

/**
* @ClassName: GameButton
* @Description: 这个类起初是想用来更改各个按钮的显示方式，后来由于其他原因，最终没有启用
* @author 管超
* @date 最终保存日期： 2011-3-22 下午03:14:58
*
*/
public class GameButton extends JButton {

	/**
	 * 单人游戏的按钮
	 */
	public static final int SINGLE = 1;

	/**
	 * 多人游戏按钮
	 */
	public static final int MULTI = 2;

	/**
	 * 回放游戏的按钮
	 */
	public static final int REPLAY = 3;

	/**
	 * 排行榜的按钮
	 */
	public static final int RECORD = 4;

	/**
	 * 离开游戏的按钮
	 */
	public static final int EXIT = 5;

	/**
	 * 新游戏的按钮
	 */
	public static final int NEW_GAME = 6;

	/**
	 * 暂停游戏的按钮
	 */
	public static final int PAUSE_GAME = 7;

	/**
	 * 继续游戏的按钮
	 */
	public static final int CONTINUE_GAME = 8;

	/**
	 * 设置游戏的按钮
	 */
	public static final int SET_GAME = 9;

	/**
	 * 返回的按钮
	 */
	public static final int BACK = 10;

	/**
	 * 世界的按钮
	 */
	public static final int WORLD = 11;

	/**
	 * 聊天的按钮
	 */
	public static final int TALK = 12;

	/**
	 * 竞赛的按钮
	 */
	public static final int COMPETITION = 13;

	/**
	 * 登陆的按钮
	 */
	public static final int LOGIN = 14;

	/**
	 * 注册的按钮
	 */
	public static final int REGISTER = 15;

	/**
	 * 保存游戏的按钮
	 */
	public static final int SAVE_FILE = 16;

	/**
	 * 游戏回放的按钮
	 */
	public static final int GAME_REPLAY = 17;

	/**
	 * 选择文件的按钮
	 */
	public static final int CHOOSE_FILE = 18;

	/**
	 * 按钮的图片
	 */
	private Image[] gameButtonImage;

	/**
	 * 侦测点击事件
	 */
	private Shape shape;

	/**
	 * 按钮的类型；
	 */
	private int type;

	/**
	 * 按钮状态
	 */
	private int state;

	/**
	 * 进入按钮音效
	 */
	private AudioClip mouseEnterMusic;

	/**
	 * 按下按钮的音效
	 */
	private AudioClip mousePressMusic;

	/**
	 * 带参数的构造函数
	 * 
	 * @param type
	 *            按钮的类型
	 */
	public GameButton(int type) {
		this.type = type;
		this.state = 0;

		mouseEnterMusic =
		 Applet.newAudioClip(getClass().getResource("/resource/s.wav"));

		mousePressMusic =
		Applet.newAudioClip(getClass().getResource("/resource/s.wav"));

		gameButtonImage = new Image[3];

		for (int i = 0; i < gameButtonImage.length; i++) {
			gameButtonImage[i] = new ImageIcon(this.getClass().getResource(
					"/Image/Button/" + type + "-" + (i + 1) + ".png"))
					.getImage();
		}

		this.addMouseListener(new MouseAdapter() {

			@Override
			public void mousePressed(MouseEvent arg0) {
				state = 2;
				repaint();
				mousePressMusic.play();
			}

			@Override
			public void mouseExited(MouseEvent arg0) {
				state = 0;
				repaint();
			}

			@Override
			public void mouseEntered(MouseEvent arg0) {
				state = 1;
				repaint();
				mouseEnterMusic.play();
			}

			public void mouseReleased(MouseEvent arg0) {
				state = 1;
				repaint();
			}

		});

		this.setCursor(new Cursor(Cursor.HAND_CURSOR));

		// 这些声明把按钮扩展为一个圆而不是一个椭圆。
		Dimension size = getPreferredSize();
		size.width = size.height = 3 * Math.max(size.width, size.height);
		setPreferredSize(size);

		// 这个调用使JButton不画背景，而允许我们画一个圆的背景。
		setContentAreaFilled(false);
	}

	/**
	 * 如果按钮改变大小，产生一个新的形状对象。
	 */
	public boolean contains(int x, int y) {
		if (shape == null || !shape.getBounds().equals(getBounds())) {
			shape = new Ellipse2D.Float(0, 0, getWidth(), getHeight());
		}
		return shape.contains(x, y);
	}

	/**
	 * 重载JButton中的画方法
	 */
	protected void paintComponent(Graphics g) {
		JPanel panel = new JPanel();
		panel.setOpaque(false);
		g.drawImage(gameButtonImage[state], 0, 0, getSize().width - 1,
				getSize().height - 1, panel);
	}

	/**
	 * 重载按钮的边界，但是不画任何东西
	 */
	protected void paintBorder(Graphics g) {
	}

	/**
	 * 初始化按钮
	 */
	public void reInit() {
		this.state = 0;
		repaint();
	}

	public static void main(String args[]) {
		new GameButton(1);
	}
}
