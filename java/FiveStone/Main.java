package five;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.util.Timer;

import javax.swing.*;

/**
* @ClassName: Main
* @Description: ���࣬�˻����ĵ������� Դ��
* @author �ܳ�
* @date ���ձ������� ��2011-3-22 ����03:09:37
* @copyright��SIT ��ĿС��
*/
public class Main extends JApplet implements ItemListener, ActionListener,
		MouseListener, MouseMotionListener {
	int chessBoard[][] = new int[15][15];// ���ڴ洢���̱���
	// int color_Qizi;//���ӵ���ɫ
	int score[] = new int[5];// ���ڴ����������
	int intgame_Start = 0;// ��Ϸ��ʼ��־ 0δ��ʼ 1��Ϸ��
	int step = 0;// ��¼���Ӳ���
	int depth;// �������
	int backi = 0, backj = 0;// ����ʱʹ��
	int chessBoardBack[][] = new int[15][15];// 0��1��2�ֱ����AI���˵����ӺͿո�
	int changeTimes = 0;// ��������������¼��������ɫ���Ĺ����ٴΣ��������Ҽ�ͷ���ν�
	int x, y;// ���λ��
	int locationX = 0, locationY = 0;// �������ӵ�λ��
	int startbw = 1;// ���ֱ�ǣ�Ĭ������
	int forbid = 1;// ���ֵı�ǣ�Ĭ���Ǵ򿪵�
	int counter = 0;// �����Ǻ����Ķ��̲߳����õ��ģ���Ϸ����������2��֮�䣬ˢ�½��棬������������������ص��쳣
	// int tick=0;//������ʵ�����һ������˸���������ģ���������޷�������쳣�����Ǵ��벿����ʱ��ɾ������ע�͵����Ա�����
	int c = 0;// ���Ĵ���
	boolean firstTip = true;// �Ƿ��ǵ�һ�����ѣ���Ϊ���ǵ���һ��������Ϸ���������ڶ�������Ϸ�Ѿ�����
	boolean hasWin = false;// ��Ϸ������־
	Dimension currentPos = new Dimension();// ���ں�������x��y��ֵ
	String[] flagTitle = { "1", "2", "3" };// �ȼ�
	private Image img;// ������
	// Button b1 = new Button("�� ʼ �� Ϸ");
	Button b0 = new Button("�� �� ս ��");
	Button b10 = new Button("�� �� ս ��");
	Button b1 = new Button("�� ʼ �� Ϸ");
	Button b2 = new Button("�� �� �� ʼ");
	Button b3 = new Button("�� �� �� Ϸ");
	Button b4 = new Button("�� �� �� ��");
	Button b5 = new Button("�� Ϸ ˵ ��");
	Button b6 = new Button("<=");// �����ı�������ɫ
	Button b7 = new Button("=>");
	Button b8 = new Button("�� �� һ ��");
	Button b9 = new Button("�� �� �� ��");
	Label changeBackground = new Label("����������ɫ");
	Label stepMessage = new Label("����ͳ��");
	Label startSide = new Label("����:");
	Label steplab = new Label("����:");
	Label locationlab = new Label("���:");
	Label locationText = new Label("���ӵ�:");
	Label timeText = new Label("��ʱ:");
	Label timelab = new Label("��ʱ:");
	Label level = new Label("����:");
	Label gameState = new Label("״̬");
	Label gameOver = new Label("��Ϸ״̬");
	Label message = new Label("��ʾ:");
	Checkbox ckbHB[] = new Checkbox[2];// ��ѡ��ʵ�����ֵ�ѡ��
	CheckboxGroup ckgHB = new CheckboxGroup();
	JComboBox levels;// �����˵����е�ʱ�����������أ�����쳣һֱ�޷���� attention here!

	static JFrame frame = new JFrame();
	static MenuBar mb = new MenuBar();
	static Menu menu0 = new Menu("��  Ϸ ");
	static Menu menu1 = new Menu("��  �� ");
	static Menu menu2 = new Menu("��  �� ");
	static Menu mi1_0 = new Menu("���̱���");
	static Menu mi1_1 = new Menu("���ֹ���");
	static MenuItem mi0 = new MenuItem("���¿�ʼ");
	static MenuItem mi2 = new MenuItem("�������Ļ�");
	static MenuItem mi3 = new MenuItem("��  ��");
	static MenuItem mi2_0 = new MenuItem("˵  ��");
	static MenuItem mi2_1 = new MenuItem("��������");
	static MenuItem mi1_0_0 = new MenuItem("��ɫ");
	static MenuItem mi1_0_1 = new MenuItem("�ۻ�");
	static MenuItem mi1_0_2 = new MenuItem("��ɫ");
	static MenuItem mi1_0_3 = new MenuItem("��ɫ");
	static MenuItem mi1_0_4 = new MenuItem("�Զ���");
	static MenuItem mi1_1_0 = new MenuItem("��");
	static MenuItem mi1_1_1 = new MenuItem("�ر�");
	static JTextArea paihangtext = new JTextArea();
	static ImageIcon icon = new ImageIcon("resource/FiveStone.jpg");

	// static JDialog dlg_1=new JDialog(frame);
	// static JDialog dlg_2=new JDialog(frame);
	// static JDialog paihang=new JDialog(frame);
	// static JTextArea paihangtext=new JTextArea();
	// static JTextArea dlg_1_text=new JTextArea();
	// static JTextArea dlg_2_text=new JTextArea();
	static String colorSign = "lightgray"; // ���̱���
	static Color newColor;

	public Main() {
		// ���·��,��������Ĵ������exe�ļ�
		img = Toolkit.getDefaultToolkit().getImage("resource/1.jpg");// װ����Ϸ����
	}

	public static void main(String args[]) // �������з�ʽ applecation �Լ� applet
	{
		Main fs = new Main();
		GSplashWindow gsw = new GSplashWindow("resource/1.gif");
		gsw.start();
		gsw.setStatus("��Ϸ���ڼ���Ԥ�衭��");
		new JWindowDemo().start();
		
		// ���ز˵�
		mb.add(menu0);
		mb.add(menu1);
		mb.add(menu2);
		menu0.add(mi0);
		// menu0.add(mi1);
		menu0.addSeparator();
		menu0.add(mi2);
		menu0.addSeparator();
		menu0.add(mi3);
		menu1.add(mi1_0);
		menu1.addSeparator();
		menu1.add(mi1_1);
		menu2.add(mi2_0);
		menu2.add(mi2_1);
		mi1_0.add(mi1_0_0);
		mi1_0.add(mi1_0_1);
		mi1_0.add(mi1_0_2);
		mi1_0.add(mi1_0_3);
		mi1_0.addSeparator();
		mi1_0.add(mi1_0_4);
		mi1_1.add(mi1_1_0);
		mi1_1.add(mi1_1_1);
		frame.setMenuBar(mb);
		mi0.addActionListener(fs);
		mi2.addActionListener(fs);
		mi3.addActionListener(fs);
		mi2_0.addActionListener(fs);
		mi2_1.addActionListener(fs);
		mi1_0_0.addActionListener(fs);
		mi1_0_1.addActionListener(fs);
		mi1_0_2.addActionListener(fs);
		mi1_0_3.addActionListener(fs);
		mi1_0_4.addActionListener(fs);
		mi1_1_0.addActionListener(fs);
		mi1_1_1.addActionListener(fs);

		fs.init();
		frame.add(fs);
		frame.setSize(1000, 700);
		frame.setResizable(false);
		frame.setIconImage(icon.getImage());
		frame.setTitle("������ V1.1");
		frame.setLocation(150, 50);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        while (!JWindowDemo.flag){
			
		}
        gsw.stop();
		frame.show();
	}

	public void init() {
		setLayout(null);
		addMouseListener(this);
		add(steplab);
		steplab.setBounds(540, 15, 30, 20);
		add(stepMessage);
		stepMessage.setBounds(590, 15, 160, 20);
		stepMessage.setBackground(Color.white);
		add(gameState);
		gameState.setBounds(540, 65, 30, 20);
		add(gameOver);
		gameOver.setBounds(590, 65, 160, 20);
		gameOver.setBackground(Color.white);
		// paihangtext.setBackground(Color.green);
		add(startSide);
		startSide.setBounds(540, 115, 30, 20);

		ckbHB[0] = new Checkbox("��      ��", ckgHB, false);
		ckbHB[0].setBounds(590, 115, 70, 20);
		ckbHB[1] = new Checkbox("�� �� ��", ckgHB, false);
		ckbHB[1].setBounds(590, 145, 70, 20);
		ckbHB[0].addItemListener(this);
		ckbHB[1].addItemListener(this);
		add(ckbHB[0]);
		add(ckbHB[1]);
		add(level);
		level.setBounds(540, 205, 30, 20);
		levels = new JComboBox(flagTitle);
		levels.setBounds(590, 205, 70, 20);
		levels.setBackground(Color.CYAN);
		levels.addItemListener(this);
		add(levels);
		add(changeBackground);
		changeBackground.setBackground(Color.gray);
		changeBackground.setFont(new Font("Serif", Font.PLAIN, 14));
		changeBackground.setBounds(190, 520, 100, 20);
		add(locationlab);
		locationlab.setBounds(540, 175, 30, 20);
		add(locationText);
		locationText.setBounds(590, 175, 50, 20);
		locationText.setBackground(Color.white);
		add(timelab);
		timelab.setBounds(650, 175, 30, 20);
		add(timeText);
		timeText.setBounds(690, 175, 50, 20);
		timeText.setBackground(Color.white);
		add(b1);
		b1.setBounds(590, 280, 160, 25);
		b1.addActionListener(this);
		add(b2);
		b2.setBounds(590, 320, 160, 25);
		b2.addActionListener(this);
		add(b3);
		b3.setBounds(590, 360, 160, 25);
		b3.addActionListener(this);
		add(b8);
		b8.setBounds(590, 400, 160, 25);
		b8.addActionListener(this);
		add(b0);
		b0.setBounds(590, 440, 160, 25);
		b0.addActionListener(this);
		add(b10);
		b10.setBounds(590, 480, 160, 25);
		b10.addActionListener(this);
		add(b5);
		b5.setBounds(400, 520, 160, 20);
		b5.addActionListener(this);
		add(b6);
		b6.setBounds(150, 520, 30, 20);
		b6.addActionListener(this);
		add(b7);
		b7.setBounds(300, 520, 30, 20);
		b7.addActionListener(this);
		add(b9);
		b9.setBounds(590, 520, 160, 20);
		b9.addActionListener(this);
		b9.setBackground(Color.LIGHT_GRAY);
		b8.setEnabled(false);
		autoUpdate();
		game_start_csh();
	}

	public void paint(Graphics g) {
		// �Ȼ�����
		super.paint(g);
		g.drawImage(img, 0, 0, 1000, 700, null);
		int x0 = 30, y0 = 50, dx = 30, dy = 30, N = 14, M = 14;
		int x1, y1, x2, y2;
		if (colorSign == "blue") {
			g.setColor(Color.blue);
		} else if (colorSign == "green") {
			g.setColor(Color.green);
		} else if (colorSign == "orange") {
			g.setColor(Color.orange);
		} else if (colorSign == "new") {
			g.setColor(newColor);
		} else {
			g.setColor(Color.lightGray);
		}
		g.fill3DRect(10, 30, 460, 460, true);
		g.setColor(Color.black);

		// �������е�����
		g.drawString("2", 20, 85);
		g.drawString("3", 20, 115);
		g.drawString("4", 20, 145);
		g.drawString("5", 20, 175);
		g.drawString("6", 20, 205);
		g.drawString("7", 20, 235);
		g.drawString("8", 20, 265);
		g.drawString("9", 20, 295);
		g.drawString("10", 15, 325);
		g.drawString("11", 15, 355);
		g.drawString("12", 15, 385);
		g.drawString("13", 15, 415);
		g.drawString("14", 15, 445);
		g.drawString("15", 15, 475);

		g.drawString("1", 20, 45);
		g.drawString("2", 55, 45);
		g.drawString("3", 85, 45);
		g.drawString("4", 115, 45);
		g.drawString("5", 145, 45);
		g.drawString("6", 175, 45);
		g.drawString("7", 205, 45);
		g.drawString("8", 235, 45);
		g.drawString("9", 265, 45);
		g.drawString("10", 295, 45);
		g.drawString("11", 325, 45);
		g.drawString("12", 355, 45);
		g.drawString("13", 385, 45);
		g.drawString("14", 415, 45);
		g.drawString("15", 445, 45);
		y1 = y0;
		y2 = y0 + M * dy;
		// �����м�������
		g.fillOval(237, 257, 6, 6);
		g.fillOval(147, 167, 6, 6);
		g.fillOval(327, 167, 6, 6);
		g.fillOval(147, 347, 6, 6);
		g.fillOval(327, 347, 6, 6);
		// ��������˵������������ص��쳣�����Լ�����һ�����µļ�ͷ
		g.drawLine(644, 212, 654, 212);
		g.drawLine(644, 212, 649, 217);
		g.drawLine(654, 212, 649, 217);
		g.drawLine(645, 213, 653, 213);
		// Ϊ�����۽��棬�����һЩ��ʾ�Ŀհ״�
		g.draw3DRect(590, 205, 70, 20, true);
		g.draw3DRect(589, 63, 162, 22, true);
		g.draw3DRect(589, 14, 162, 22, true);
		// ���������ϵ��ݺ���
		for (int i = 0; i <= N; i++) {
			x1 = x0 + i * dx;
			g.drawLine(x1, y1, x1, y2);
		}
		g.setColor(Color.black);
		x1 = x0;
		x2 = x0 + N * dx;
		for (int j = 0; j <= M; j++) {
			y1 = y0 + j * dy;
			g.drawLine(x1, y1, x2, y1);
		}
		// ������
		for (int i = 0; i <= 14; i++)
			for (int j = 0; j <= 14; j++) {
				if (chessBoard[i][j] == 1) {
					g.setColor(Color.white);
					g.fillOval(20 + i * 30, 40 + j * 30, 20, 20);
				}
				if (chessBoard[i][j] == 0) {
					g.setColor(Color.black);
					g.fillOval(20 + i * 30, 40 + j * 30, 20, 20);
				}
			}
	}

	// ��Ҫ����Լ��������ѡ��˵���д��itemStateChanged����
	public void itemStateChanged(ItemEvent e) {
		Graphics g = getGraphics();
		if (ckbHB[1].getState()) // ѡ������Ȼ�������
		{
			gameOver.setText("���������");
			forbid = 0;
		} else {
			forbid = 1;
			gameOver.setText("������");
		}
		if (levels.getSelectedIndex() == 0) {
			depth = 1;
			gameOver.setText("��ˮƽ");
		} else if (levels.getSelectedIndex() == 1) {
			depth = 2;
			gameOver.setText("��׼ˮƽ");
		} else if (levels.getSelectedIndex() == 2) {
			depth = 3;
			gameOver.setText("ר��ˮƽ");
		}
	}

	// ������궯��
	public void actionPerformed(ActionEvent e) {
		Graphics g = getGraphics();
		if (e.getSource() == b1)// ��Ϸ��ʼ
		{
			game_start();
		} else if (e.getSource() == b2)// ���¿�ʼ
		{
			game_re();
		} else if (e.getSource() == b3)// �˳���Ϸ
		{
			frame.dispose();
		} else if (e.getSource() == b5)// ��Ϸ���
		{
			CheckResult cr = new CheckResult();
			cr.readMessage();
		} else if (e.getSource() == b6)// ���ٸı�������ɫ
		{
			changeTimes = (changeTimes + 1) % 4;
			switch (changeTimes) {
			case 0:
				colorSign = "gray";
				break;
			case 1:
				colorSign = "orange";
				break;
			// case 2:colorSign="cyan";break;
			// case 4:colorSign="darkgray";break;
			case 2:
				colorSign = "green";
				break;
			// case 5:colorSign="lightgray";break;
			case 3:
				colorSign = "blue";
				break;
			}
			repaint();
		} else if (e.getSource() == b7)// ��ݸı�������ɫ
		{
			changeTimes--;
			if (changeTimes < 0)
				changeTimes += 4;
			switch (changeTimes) {
			case 0:
				colorSign = "gray";
				break;
			case 1:
				colorSign = "orange";
				break;
			// case 2:colorSign="cyan";break;
			// case 4:colorSign="darkgray";break;
			case 2:
				colorSign = "green";
				break;
			// case 5:colorSign="lightgray";break;
			case 3:
				colorSign = "blue";
				break;
			}
			repaint();
		} else if (e.getSource() == b9) {
			new MediaPlayer();
			// b9.setEnabled(false);

		} else if (e.getSource() == b0)// �鿴ս��
		{
			CheckResult cr = new CheckResult();
			cr.displayScore();
		}else if (e.getSource() == b10)// ���ս��
		{
			CheckResult cr = new CheckResult();
			cr.clearScore();
		}else if (e.getSource() == b8)// ����
		{
			if (step < 2)// ֻ����˫���������ӵ�����²��ܻ��壬������ܻᵼ��else�����쳣����
			{
				gameOver.setText("��Ϸδ��ʼ");
				JOptionPane.showMessageDialog(this, "��δ����", "Tips",
						JOptionPane.INFORMATION_MESSAGE);
			} else {
				chessBoard[backi][backj] = 2;
				step--;
				chessBoard[locationX][locationY] = 2;
				step--;
				hasWin = false;// �Է����һ������
				stepMessage.setText("��" + step + "��");
				repaint();
			}
		} else if (e.getSource() == mi0)// ���¿�ʼ
		{
			game_re();
		}/*
		 * else if(e.getSource()==mi1&&intgame_Start==0) {
		 * gameOver.setText("��Ϸ��δ��ʼ"); JOptionPane.showMessageDialog(this,
		 * "��Ϸ��δ��ʼ","Tips",JOptionPane.INFORMATION_MESSAGE); } else
		 * if(e.getSource()==mi1&&intgame_Start==1&&step>=2) {
		 * //backFiveStone++; repaint(); } else
		 * if(e.getSource()==mi1&&intgame_Start==1&&step<2) {
		 * gameOver.setText("��һ�����ܻ��壡"); }
		 */
		else if (e.getSource() == mi2) {
			JOptionPane.showMessageDialog(this, "���������ҹ��Ŵ��ġ���ͳ�ĺڰ�����֮һ��"
					+ "\n��Լ���ϱ���ʱ����Χ��һ���Ⱥ��볯�ʡ��ձ��ȵء�" + "\n���������ձ��С������塱��"
					+ "\nͨ��һϵ�еĹ���仯ʹ������������һ�򵥵���Ϸ���ӻ����淶����"
					+ "\n�����ճ�Ϊ�����ְҵ���������壬ͬʱҲ��Ϊһ�ֹ��ʱ����塣", "�������Ļ�",
					JOptionPane.INFORMATION_MESSAGE);
		} else if (e.getSource() == mi3)// �˳��˵�
		{
			frame.dispose();
		} else if (e.getSource() == mi1_0_0)// �ı���ɫ�˵�
		{
			colorSign = "blue";
			repaint();
		} else if (e.getSource() == mi1_0_1) {
			colorSign = "orange";
			repaint();
		} else if (e.getSource() == mi1_0_2) {
			colorSign = "green";
			repaint();
		} else if (e.getSource() == mi1_1_1)// �رս��ֹ���˵�
		{
			forbid = 0;

		} else if (e.getSource() == mi1_1_0)// �򿪽��ֹ���˵�
		{
			forbid = 1;
			JOptionPane.showMessageDialog(this, "�ý��ֹ���ֻ�ʺ������ֵ������"
					+ "\n�����ѡ�������֣��ù���Ż���Ч", "Tips",
					JOptionPane.INFORMATION_MESSAGE);
		} else if (e.getSource() == mi1_0_3) {
			colorSign = "lightgray";
			repaint();
		} else if (e.getSource() == mi1_0_4)// �Զ�����ɫ
		{
			newColor = JColorChooser.showDialog(null, "�Զ�����ɫ", null);
			if (newColor != null) {
				colorSign = "new";
				repaint();
			}
		} else if (e.getSource() == mi2_1) {
			JOptionPane.showMessageDialog(this, "�������ߣ�eclipse 3.4.2��java"
					+ "\n������ߣ�eclipse 3.2" + "\n���л������κ�������Java ���л���"
					+ "\n         ��jre����ƽ̨" + "\n�ؼ�����������С��֦����"
					+ "\nʵ�ֹ��ܣ��˻����ģ�˫�˶�ս" + "\n�����Ѷȣ��ܹ���Ϊ�������ʺϲ�ͬˮƽ��"
					+ "\n          �ε����ѡ�", "���",
					JOptionPane.INFORMATION_MESSAGE);
		} else if (e.getSource() == mi2_0) {
			JOptionPane.showMessageDialog(this, "��������Ϸ " + "\n����: �ܳ� "
					+ "\n�汾:version 1.0  " + "\n���ʣ�SIT����", "˵��",
					JOptionPane.INFORMATION_MESSAGE);
		} else
			frame.dispose();
	}

	/*
	 * static class WinLis1 extends WindowAdapter { public void
	 * windowClosing(WindowEvent e) { //dlg_1.dispose(); //dlg_2.dispose();
	 * //paihang.dispose(); } }
	 */
	public void mouseMoved(MouseEvent e) {
	}

	public void mouseEntered(MouseEvent e) {
	}

	public void mouseExited(MouseEvent e) {
	}

	public void mouseReleased(MouseEvent e) {
	}

	public void mouseDragged(MouseEvent e) {
	}

	public void mousePressed(MouseEvent e) {
	}

	public void mouseClicked(MouseEvent e) {
		// ���ݷ��صĵ���λ�ã�����Ƿ���������
		currentPos.width = e.getX();
		currentPos.height = e.getY();
		if (currentPos.width > 15 & currentPos.width < 485
				& currentPos.height > 35 & currentPos.height < 485) // 15*15�Ļ�����
		{
			x = y = 20;
			for (int i = 0; i <= 14; i++) {
				for (int j = 0; j <= 14; j++) {
					if (currentPos.width <= (45 + i * 30)
							& currentPos.width >= (15 + i * 30))
						x = i;
					if (currentPos.height <= (65 + j * 30)
							& currentPos.height >= (35 + j * 30))
						y = j;
				}
			}
			// �������в�ִ��
			if (x != 20 && y != 20) {
				if (chessBoard[x][y] == 2) {
					set_Qizi(x, y, 1);
					c = 1;
				} else // �����ظ�����
				{
					JOptionPane.showMessageDialog(this, "�����ظ�����", "��ʾ",
							JOptionPane.INFORMATION_MESSAGE);
					return;
				}
				if (hasWin)// ��Ϸ�Ѿ�����
				{
					JOptionPane.showMessageDialog(this, "��Ϸ�Ѿ�����", "��Ϸ����",
							JOptionPane.INFORMATION_MESSAGE);
					return;
				}
			}
			if (isWin(x, y, 1))// �ж��Ƿ����
			{
				gameOver.setText("��Ϸ����");
				if (firstTip) {
					JOptionPane.showMessageDialog(this, "��Ӯ��", "��Ϸ����",
							JOptionPane.INFORMATION_MESSAGE);
					int i = JOptionPane.showConfirmDialog(null, "�洢��ʾ���Ƿ�洢���ֽ����", "������ʾ",
							JOptionPane.OK_CANCEL_OPTION);
					if (i == JOptionPane.YES_OPTION){
						CheckResult cr = new CheckResult();
						cr.setScore(1);
					}
					firstTip = false;
					hasWin = true;
				} else
					JOptionPane.showMessageDialog(this, "��Ϸ�Ѿ�����", "��Ϸ����",
							JOptionPane.INFORMATION_MESSAGE);
				intgame_Start = 0;
				return;
			}
			if (forbid == 1 & isForbid(x, y))// �ж��Ƿ����
			{
				gameOver.setText("��Ϸ����");
				if (firstTip) {
					JOptionPane.showMessageDialog(this, "�õ���֣�������", "��Ϸ����",
							JOptionPane.INFORMATION_MESSAGE);
					firstTip = false;
				} else
					JOptionPane.showMessageDialog(this, "��Ϸ�Ѿ�����", "��Ϸ����",
							JOptionPane.INFORMATION_MESSAGE);
				intgame_Start = 0;
				return;
			}
			// getNext();
			// set_Qizi(locationX,locationY,0);
			computeSet(0);// //////
		}

	}

	public void set_Qizi(int x, int y, int side) // ����
	{
		Graphics g = getGraphics();
		int a, b;
		if (step == 225)// û�пո�
		{
			gameState.setText("�;�");
		}
		if (intgame_Start == 0) // �ж���Ϸ�Ƿ�ʼ
		{
			return;
		}

		if (chessBoard[x][y] != 2)// ���ǿո�
		{
			return;
		}
		if (intgame_Start == 1 && chessBoard[x][y] == 2)
			step++;
		stepMessage.setText("��" + step + "��");
		if (side == 1)// �жϺ��ӻ��ǰ���
		{
			g.setColor(Color.white);
			g.fillOval(20 + x * 30, 40 + y * 30, 20, 20);
			backi = x;
			backj = y;
			a = backi + 1;
			b = backj + 1;
			locationText.setText("(" + a + "," + b + ")");
		} else {
			g.setColor(Color.black);
			g.fillOval(20 + x * 30, 40 + y * 30, 20, 20);
			a = x + 1;
			b = y + 1;
			locationText.setText("(" + a + "," + b + ")");
		}
		chessBoard[x][y] = side;
	}

	public void game_start_csh() // ��Ϸ��ʼ��ʼ��
	{
		intgame_Start = 0;
		step = 0;

		b2.setEnabled(false);
		// b3.setEnabled(false);
		// color_Qizi=0;
		ckbHB[0].setState(true);

		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				chessBoard[i][j] = 2;
			}
		}
		c = 1;
		gameOver.setText("׼������");
		stepMessage.setText("��δ����");
	}

	public void game_re() // ��Ϸ���¿�ʼ
	{
		b1.setEnabled(true);
		b8.setEnabled(true);
		ckbHB[0].setEnabled(true);
		ckbHB[1].setEnabled(true);
		levels.setEnabled(true);
		game_start_csh();
		c = 1;
		repaint();
	}

	public void game_start() // ��Ϸ��ʼ
	{
		intgame_Start = 1;
		firstTip = true;
		hasWin = false;
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				chessBoard[i][j] = 2;
			}
		}
		b1.setEnabled(false);
		b2.setEnabled(true);
		b3.setEnabled(true);
		b8.setEnabled(true);
		ckbHB[0].setEnabled(false);
		ckbHB[1].setEnabled(false);
		levels.setEnabled(false);
		gameOver.setText("��Ϸ�Ѿ���ʼ");
		if (ckbHB[1].getState()) {
			Graphics g = getGraphics();
			g.setColor(Color.black);
			g.fillOval(230, 250, 20, 20);
			chessBoard[7][7] = 0;
			// color_Qizi=0;
			step++;
			stepMessage.setText("��" + step + "��");
		}
		c = 1;
		repaint();
	}

	public int[] count(int x, int y, int ex, int ey, int k)// �ú������Խ�������������
	{
		int rt = 1;
		// if (chessBoard[x][y]!=2)
		// throw new IllegalArgumentException("illegal!");
		int i;
		for (i = 1; x + i * ex < 15 && y + i * ey < 15 && x + i * ex >= 0
				&& y + i * ey >= 0; i++) {
			if (chessBoard[x + i * ex][y + i * ey] == k)
				rt++;
			else
				break;
		}
		int ok = 0;
		if (x + i * ex < 15 && y + i * ey < 15 && x + i * ex >= 0
				&& y + i * ey >= 0 && chessBoard[x + i * ex][y + i * ey] == 2)
			ok++;
		for (i = 1; x - i * ex < 15 && y - i * ey < 15 && x - i * ex >= 0
				&& y - i * ey >= 0; i++) {
			if (chessBoard[x - i * ex][y - i * ey] == k)
				rt++;
			else
				break;
		}
		if (x - i * ex < 15 && y - i * ey < 15 && x - i * ex >= 0
				&& y - i * ey >= 0 && chessBoard[x - i * ex][y - i * ey] == 2)
			ok++;
		if (rt < 5 && !makesence(x, y, ex, ey, k))
			return new int[] { 0, 1 };
		return new int[] { rt, ok };
	}

	public boolean makesence(int x, int y, int ex, int ey, int bwf)// �ж����µĿռ��ܷ񹹳���������
	{
		int rt = 1;
		for (int i = 1; x + i * ex < 15 && y + i * ey < 15 && x + i * ex >= 0
				&& y + i * ey >= 0 && rt < 5; i++)
			if (chessBoard[x + i * ex][y + i * ey] != 1 - bwf)
				rt++;
			else
				break;
		for (int i = 1; x - i * ex < 15 && y - i * ey < 15 && x - i * ex >= 0
				&& y - i * ey >= 0 && rt < 5; i++)
			if (chessBoard[x - i * ex][y - i * ey] != 1 - bwf)
				rt++;
			else
				break;
		return (rt >= 5);
	}

	protected int findMax(int alpha, int beta, int depth)// �����㷨
	{
		int mx = alpha;
		if (depth == 0)
			return evaluate();
		for (int i = 3; i < 11; i++)
			for (int j = 3; j < 11; j++)
				if (chessBoard[i][j] == 2) {
					if (getType(i, j, 1 - startbw) == 1)
						return 100 * getMark(1);
					chessBoard[i][j] = 1 - startbw;
					int t = findMin(mx, beta, depth - 1);
					chessBoard[i][j] = 2;
					if (t > mx)
						mx = t;
					if (mx >= beta)
						return mx;
				}
		return mx;
	}

	protected int findMin(int alpha, int beta, int depth) {
		int mn = beta;
		if (depth == 0)
			return evaluate();
		int[][] rt = getBests(startbw);
		for (int i = 0; i < rt.length; i++) {
			int ii = rt[i][0];
			int jj = rt[i][1];
			if (getType(ii, jj, startbw) == 1)
				return -100 * getMark(1);
			chessBoard[ii][jj] = startbw;
			int t = findMax(alpha, mn, depth - 1);
			chessBoard[ii][jj] = 2;
			if (t < mn)
				mn = t;
			if (mn <= alpha)
				return mn;
		}
		return mn;
	}

	protected boolean isWin(int x, int y, int bw)// �ж���Ӯ
	{
		if (count(x, y, 1, 0, bw)[0] >= 5)
			return true;
		if (count(x, y, 0, 1, bw)[0] >= 5)
			return true;
		if (count(x, y, 1, -1, bw)[0] >= 5)
			return true;
		if (count(x, y, 1, 1, bw)[0] >= 5)
			return true;
		return false;
	}

	protected boolean isForbid(int x, int y)// �жϽ���
	{
		int[][] types = new int[4][2];
		types[0] = count(x, y, 0, 1, 1);// attention here!
		types[1] = count(x, y, 1, 0, 1);
		types[2] = count(x, y, -1, 1, 1);// ///////
		types[3] = count(x, y, 1, 1, 1);
		int c5, s4, h4, s3, h3, s2, h2;
		c5 = s4 = h4 = s3 = h3 = s2 = h2 = 0;
		for (int k = 0; k < 4; k++) {
			if (types[k][0] == 5)
				c5++;
			else if (types[k][0] == 4 && types[k][1] == 2)
				h4++;
			else if (types[k][0] == 4 && types[k][1] != 2)
				s4++;
			else if (types[k][0] == 3 && types[k][1] == 2)
				h3++;
			else if (types[k][0] == 3 && types[k][1] != 2)
				s3++;
			else if (types[k][0] == 2 && types[k][1] == 2)
				h2++;
			else if (types[k][0] == 2 && types[k][1] != 2)
				s2++;
		}
		if (h3 >= 2)
			return true;
		if (h4 >= 2)
			return true;
		if (s4 >= 2)
			return true;
		if (h4 != 0 & s4 != 0)
			return true;
		if (h4 != 0 & h3 != 0)
			return true;
		if (h3 != 0 & s4 != 0)
			return true;
		return false;
	}

	static void sort2(int[][] a)// �Եõ���ֵ���չ�ֵ�Ĵ�С���ڶ�ά������
	{
		for (int i = a.length; i > 0; i--) {
			for (int j = 0; j < i - 1; j++) {
				if (a[j + 1][2] > a[j][2]) {
					a[j][2] = a[j][2] + a[j + 1][2];
					a[j + 1][2] = a[j][2] - a[j + 1][2];
					a[j][2] = a[j][2] - a[j + 1][2];

					a[j][1] = a[j][1] + a[j + 1][1];
					a[j + 1][1] = a[j][1] - a[j + 1][1];
					a[j][1] = a[j][1] - a[j + 1][1];

					a[j][0] = a[j][0] + a[j + 1][0];
					a[j + 1][0] = a[j][0] - a[j + 1][0];
					a[j][0] = a[j][0] - a[j + 1][0];
				}
			}
		}
	}

	protected int getType(int x, int y, int bwf)// �ж�����
	{
		if (chessBoard[x][y] != 2)
			return -1;
		int[][] types = new int[4][2];
		types[0] = count(x, y, 0, 1, bwf);
		types[1] = count(x, y, 1, 0, bwf);
		types[2] = count(x, y, -1, 1, bwf);
		types[3] = count(x, y, 1, 1, bwf);
		int c5, s4, h4, s3, h3, s2, h2;
		c5 = s4 = h4 = s3 = h3 = s2 = h2 = 0;
		for (int k = 0; k < 4; k++) {
			if (types[k][0] == 5)
				c5++;
			else if (types[k][0] == 4 && types[k][1] == 2)
				h4++;
			else if (types[k][0] == 4 && types[k][1] != 2)
				s4++;
			else if (types[k][0] == 3 && types[k][1] == 2)
				h3++;
			else if (types[k][0] == 3 && types[k][1] != 2)
				s3++;
			else if (types[k][0] == 2 && types[k][1] == 2)
				h2++;
			else if (types[k][0] == 2 && types[k][1] != 2)
				s2++;
		}
		if (c5 != 0)
			return 1;
		if (h4 != 0 || s4 >= 2 || s4 != 0 && h3 != 0)
			return 2;
		if (h3 >= 2)
			return 3;
		if (s3 != 0 && h3 != 0)
			return 4;
		if (s4 != 0)
			return 5;
		if (h3 != 0)
			return 6;
		if (h2 >= 2)
			return 7;
		if (s3 != 0)
			return 8;
		if (h2 != 0 && s2 != 0)
			return 9;
		if (h2 != 0)
			return 10;
		if (s2 != 0)
			return 11;
		return 0;
	}

	protected int getMark(int k)// ��ֵ�������֣����ų��и��õĹ�ֵ
	{
		switch (k) {
		case 1:
			return 100000;
		case 2:
			return 10000;
		case 3:
			return 5000;
		case 4:
			return 1000;
		case 5:
			return 500;
		case 6:
			return 200;
		case 7:
			return 100;
		case 8:
			return 50;
		case 9:
			return 10;
		case 10:
			return 5;
		case 11:
			return 3;
		default:
			return 0;
		}
	}

	protected int evaluate()// �õ���������ķ���
	{
		int rt = 0;
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
				if (chessBoard[i][j] == 2) {
					int type = getType(i, j, 1 - startbw);
					rt += getMark(type);
					type = getType(i, j, startbw);
					rt -= getMark(type);
				}
		return rt;
	}

	protected int[][] getBests(int bwf)// Ϊ�˼�С�����ռ䣬�ȵõ����������ϸߵĵ�
	{
		int[][] rt = new int[255][3];
		int n = 0;
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
				if (chessBoard[i][j] == 2) {
					rt[n][0] = i;
					rt[n][1] = j;
					rt[n][2] = (getMark(getType(i, j, bwf)) + getMark(getType(
							i, j, 1 - bwf)));// ////
					n++;
				}
		// Arrays.sort(rt,new ArrComparator());
		sort2(rt);
		int size = 8 > n ? n : 8;
		int[][] bests = new int[size][3];
		System.arraycopy(rt, 0, bests, 0, size);
		return bests;
	}

	protected void computeSet(int bwf)// AI����
	{
		int it, jt, mx = -100000000;
		it = jt = -1;
		int[][] bests = getBests(bwf);
		for (int k = 0; k < bests.length; k++) {
			int i = bests[k][0];
			int j = bests[k][1];
			if (getType(i, j, bwf) == 1) {
				it = i;
				jt = j;
				break;
			}
			chessBoard[i][j] = bwf;
			int t = findMin(-100000000, 100000000, depth);
			chessBoard[i][j] = 2;
			if (t > mx)// || t==mx &&
						// randomTest(3*(Math.abs(7-i)+Math.abs(7-j))+2)
			{
				it = i;
				jt = j;
				mx = t;
			}
		}
		locationX = it;
		locationY = jt;
		set_Qizi(it, jt, 0);
		c = 1;
		if (isWin(it, jt, 0)) {
			gameOver.setText("��Ϸ����");
			if (firstTip) {
				JOptionPane.showMessageDialog(this, "������", "��Ϸ����",
						JOptionPane.INFORMATION_MESSAGE);
				int i = JOptionPane.showConfirmDialog(null, "�洢��ʾ���Ƿ�洢���ֽ����", "������ʾ",
						JOptionPane.OK_CANCEL_OPTION);
				if (i == JOptionPane.YES_OPTION){
					CheckResult cr = new CheckResult();
					cr.setScore(2);
				}
				firstTip = false;
			} else
				JOptionPane.showMessageDialog(this, "��Ϸ�Ѿ�����", "��Ϸ����",
						JOptionPane.INFORMATION_MESSAGE);
			intgame_Start = 0;
		}
	}

	protected void autoUpdate()// �Զ����£����߳̿�
	{

		Timer time = new Timer(false);
		time.schedule(new TimerTask() {
			public void run() {

				if (intgame_Start != 1 && counter < 15) {
					repaint();
					counter++;
				}
				// tick++;
				timeText.setText(c + "��");
				c++;
			}

		}, 0, 1000);
	}

	protected boolean randomTest(int kt) {
		Random rm = new Random();
		return rm.nextInt() % kt == 0;
	}
}
