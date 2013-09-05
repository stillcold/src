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
* @Description: �������������������ĸ�����ť����ʾ��ʽ��������������ԭ������û������
* @author �ܳ�
* @date ���ձ������ڣ� 2011-3-22 ����03:14:58
*
*/
public class GameButton extends JButton {

	/**
	 * ������Ϸ�İ�ť
	 */
	public static final int SINGLE = 1;

	/**
	 * ������Ϸ��ť
	 */
	public static final int MULTI = 2;

	/**
	 * �ط���Ϸ�İ�ť
	 */
	public static final int REPLAY = 3;

	/**
	 * ���а�İ�ť
	 */
	public static final int RECORD = 4;

	/**
	 * �뿪��Ϸ�İ�ť
	 */
	public static final int EXIT = 5;

	/**
	 * ����Ϸ�İ�ť
	 */
	public static final int NEW_GAME = 6;

	/**
	 * ��ͣ��Ϸ�İ�ť
	 */
	public static final int PAUSE_GAME = 7;

	/**
	 * ������Ϸ�İ�ť
	 */
	public static final int CONTINUE_GAME = 8;

	/**
	 * ������Ϸ�İ�ť
	 */
	public static final int SET_GAME = 9;

	/**
	 * ���صİ�ť
	 */
	public static final int BACK = 10;

	/**
	 * ����İ�ť
	 */
	public static final int WORLD = 11;

	/**
	 * ����İ�ť
	 */
	public static final int TALK = 12;

	/**
	 * �����İ�ť
	 */
	public static final int COMPETITION = 13;

	/**
	 * ��½�İ�ť
	 */
	public static final int LOGIN = 14;

	/**
	 * ע��İ�ť
	 */
	public static final int REGISTER = 15;

	/**
	 * ������Ϸ�İ�ť
	 */
	public static final int SAVE_FILE = 16;

	/**
	 * ��Ϸ�طŵİ�ť
	 */
	public static final int GAME_REPLAY = 17;

	/**
	 * ѡ���ļ��İ�ť
	 */
	public static final int CHOOSE_FILE = 18;

	/**
	 * ��ť��ͼƬ
	 */
	private Image[] gameButtonImage;

	/**
	 * ������¼�
	 */
	private Shape shape;

	/**
	 * ��ť�����ͣ�
	 */
	private int type;

	/**
	 * ��ť״̬
	 */
	private int state;

	/**
	 * ���밴ť��Ч
	 */
	private AudioClip mouseEnterMusic;

	/**
	 * ���°�ť����Ч
	 */
	private AudioClip mousePressMusic;

	/**
	 * �������Ĺ��캯��
	 * 
	 * @param type
	 *            ��ť������
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

		// ��Щ�����Ѱ�ť��չΪһ��Բ������һ����Բ��
		Dimension size = getPreferredSize();
		size.width = size.height = 3 * Math.max(size.width, size.height);
		setPreferredSize(size);

		// �������ʹJButton�������������������ǻ�һ��Բ�ı�����
		setContentAreaFilled(false);
	}

	/**
	 * �����ť�ı��С������һ���µ���״����
	 */
	public boolean contains(int x, int y) {
		if (shape == null || !shape.getBounds().equals(getBounds())) {
			shape = new Ellipse2D.Float(0, 0, getWidth(), getHeight());
		}
		return shape.contains(x, y);
	}

	/**
	 * ����JButton�еĻ�����
	 */
	protected void paintComponent(Graphics g) {
		JPanel panel = new JPanel();
		panel.setOpaque(false);
		g.drawImage(gameButtonImage[state], 0, 0, getSize().width - 1,
				getSize().height - 1, panel);
	}

	/**
	 * ���ذ�ť�ı߽磬���ǲ����κζ���
	 */
	protected void paintBorder(Graphics g) {
	}

	/**
	 * ��ʼ����ť
	 */
	public void reInit() {
		this.state = 0;
		repaint();
	}

	public static void main(String args[]) {
		new GameButton(1);
	}
}
