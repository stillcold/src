package five;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.util.Timer;

import javax.swing.*;

/**
* @ClassName: Main
* @Description: 主类，人机对弈的五子棋 源码
* @author 管超
* @date 最终保存日期 ：2011-3-22 下午03:09:37
* @copyright：SIT 项目小组
*/
public class Main extends JApplet implements ItemListener, ActionListener,
		MouseListener, MouseMotionListener {
	int chessBoard[][] = new int[15][15];// 用于存储棋盘变量
	// int color_Qizi;//棋子的颜色
	int score[] = new int[5];// 用于储存最佳排行
	int intgame_Start = 0;// 游戏开始标志 0未开始 1游戏中
	int step = 0;// 记录棋子步数
	int depth;// 搜索深度
	int backi = 0, backj = 0;// 悔棋时使用
	int chessBoardBack[][] = new int[15][15];// 0，1，2分别代表AI，人的棋子和空格
	int changeTimes = 0;// 计数器，用来记录面面板的颜色被改过多少次，方便左右箭头的衔接
	int x, y;// 鼠标位置
	int locationX = 0, locationY = 0;// 即将落子的位置
	int startbw = 1;// 先手标记，默认是人
	int forbid = 1;// 禁手的标记，默认是打开的
	int counter = 0;// 这里是后来的多线程部分用到的，游戏启动到运行2秒之间，刷新界面，解决背景不能正常加载的异常
	// int tick=0;//本意是实现最后一步的闪烁，但是这个模块遇到了无法解决的异常，但是代码部分暂时不删除，仅注释掉，以备后用
	int c = 0;// 秒表寄存器
	boolean firstTip = true;// 是否是第一次提醒，因为考虑到第一次提醒游戏结束，而第二次是游戏已经结束
	boolean hasWin = false;// 游戏结束标志
	Dimension currentPos = new Dimension();// 用于后来计算x、y的值
	String[] flagTitle = { "1", "2", "3" };// 等级
	private Image img;// 画背景
	// Button b1 = new Button("开 始 游 戏");
	Button b0 = new Button("查 看 战 绩");
	Button b10 = new Button("清 空 战 绩");
	Button b1 = new Button("开 始 游 戏");
	Button b2 = new Button("重 新 开 始");
	Button b3 = new Button("退 出 游 戏");
	Button b4 = new Button("清 空 排 行");
	Button b5 = new Button("游 戏 说 明");
	Button b6 = new Button("<=");// 用来改变棋盘颜色
	Button b7 = new Button("=>");
	Button b8 = new Button("悔 棋 一 步");
	Button b9 = new Button("播 放 音 乐");
	Label changeBackground = new Label("更换背景颜色");
	Label stepMessage = new Label("步数统计");
	Label startSide = new Label("先手:");
	Label steplab = new Label("步数:");
	Label locationlab = new Label("落点:");
	Label locationText = new Label("落子点:");
	Label timeText = new Label("计时:");
	Label timelab = new Label("耗时:");
	Label level = new Label("级别:");
	Label gameState = new Label("状态");
	Label gameOver = new Label("游戏状态");
	Label message = new Label("提示:");
	Checkbox ckbHB[] = new Checkbox[2];// 单选框，实现先手的选择
	CheckboxGroup ckgHB = new CheckboxGroup();
	JComboBox levels;// 下拉菜单，有的时候不能正常加载，这个异常一直无法解决 attention here!

	static JFrame frame = new JFrame();
	static MenuBar mb = new MenuBar();
	static Menu menu0 = new Menu("游  戏 ");
	static Menu menu1 = new Menu("设  置 ");
	static Menu menu2 = new Menu("帮  助 ");
	static Menu mi1_0 = new Menu("棋盘背景");
	static Menu mi1_1 = new Menu("禁手规则");
	static MenuItem mi0 = new MenuItem("重新开始");
	static MenuItem mi2 = new MenuItem("五子棋文化");
	static MenuItem mi3 = new MenuItem("退  出");
	static MenuItem mi2_0 = new MenuItem("说  明");
	static MenuItem mi2_1 = new MenuItem("开发工具");
	static MenuItem mi1_0_0 = new MenuItem("蓝色");
	static MenuItem mi1_0_1 = new MenuItem("桔黄");
	static MenuItem mi1_0_2 = new MenuItem("绿色");
	static MenuItem mi1_0_3 = new MenuItem("灰色");
	static MenuItem mi1_0_4 = new MenuItem("自定义");
	static MenuItem mi1_1_0 = new MenuItem("打开");
	static MenuItem mi1_1_1 = new MenuItem("关闭");
	static JTextArea paihangtext = new JTextArea();
	static ImageIcon icon = new ImageIcon("resource/FiveStone.jpg");

	// static JDialog dlg_1=new JDialog(frame);
	// static JDialog dlg_2=new JDialog(frame);
	// static JDialog paihang=new JDialog(frame);
	// static JTextArea paihangtext=new JTextArea();
	// static JTextArea dlg_1_text=new JTextArea();
	// static JTextArea dlg_2_text=new JTextArea();
	static String colorSign = "lightgray"; // 棋盘背景
	static Color newColor;

	public Main() {
		// 相对路经,方便后来的打包生成exe文件
		img = Toolkit.getDefaultToolkit().getImage("resource/1.jpg");// 装载游戏背景
	}

	public static void main(String args[]) // 两种运行方式 applecation 以及 applet
	{
		Main fs = new Main();
		GSplashWindow gsw = new GSplashWindow("resource/1.gif");
		gsw.start();
		gsw.setStatus("游戏正在加载预设……");
		new JWindowDemo().start();
		
		// 加载菜单
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
		frame.setTitle("五子棋 V1.1");
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

		ckbHB[0] = new Checkbox("人      先", ckgHB, false);
		ckbHB[0].setBounds(590, 115, 70, 20);
		ckbHB[1] = new Checkbox("电 脑 先", ckgHB, false);
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
		// 先画背景
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

		// 画出行列的坐标
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
		// 棋盘中间的五个点
		g.fillOval(237, 257, 6, 6);
		g.fillOval(147, 167, 6, 6);
		g.fillOval(327, 167, 6, 6);
		g.fillOval(147, 347, 6, 6);
		g.fillOval(327, 347, 6, 6);
		// 解决下拉菜单不能正常加载的异常，我自己画了一个向下的箭头
		g.drawLine(644, 212, 654, 212);
		g.drawLine(644, 212, 649, 217);
		g.drawLine(654, 212, 649, 217);
		g.drawLine(645, 213, 653, 213);
		// 为了美观界面，描粗了一些显示的空白处
		g.draw3DRect(590, 205, 70, 20, true);
		g.draw3DRect(589, 63, 162, 22, true);
		g.draw3DRect(589, 14, 162, 22, true);
		// 画出棋盘上的纵横线
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
		// 画棋子
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

	// 主要是针对级别和先手选择菜单而写的itemStateChanged函数
	public void itemStateChanged(ItemEvent e) {
		Graphics g = getGraphics();
		if (ckbHB[1].getState()) // 选择电脑先还是人先
		{
			gameOver.setText("计算机先手");
			forbid = 0;
		} else {
			forbid = 1;
			gameOver.setText("您先手");
		}
		if (levels.getSelectedIndex() == 0) {
			depth = 1;
			gameOver.setText("简单水平");
		} else if (levels.getSelectedIndex() == 1) {
			depth = 2;
			gameOver.setText("标准水平");
		} else if (levels.getSelectedIndex() == 2) {
			depth = 3;
			gameOver.setText("专家水平");
		}
	}

	// 监视鼠标动作
	public void actionPerformed(ActionEvent e) {
		Graphics g = getGraphics();
		if (e.getSource() == b1)// 游戏开始
		{
			game_start();
		} else if (e.getSource() == b2)// 重新开始
		{
			game_re();
		} else if (e.getSource() == b3)// 退出游戏
		{
			frame.dispose();
		} else if (e.getSource() == b5)// 游戏简介
		{
			CheckResult cr = new CheckResult();
			cr.readMessage();
		} else if (e.getSource() == b6)// 快速改变棋盘颜色
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
		} else if (e.getSource() == b7)// 快捷改变棋盘颜色
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

		} else if (e.getSource() == b0)// 查看战绩
		{
			CheckResult cr = new CheckResult();
			cr.displayScore();
		}else if (e.getSource() == b10)// 清空战绩
		{
			CheckResult cr = new CheckResult();
			cr.clearScore();
		}else if (e.getSource() == b8)// 悔棋
		{
			if (step < 2)// 只有在双方都有落子的情况下才能悔棋，否则可能会导致else语句的异常出现
			{
				gameOver.setText("游戏未开始");
				JOptionPane.showMessageDialog(this, "尚未落子", "Tips",
						JOptionPane.INFORMATION_MESSAGE);
			} else {
				chessBoard[backi][backj] = 2;
				step--;
				chessBoard[locationX][locationY] = 2;
				step--;
				hasWin = false;// 以防最后一步悔棋
				stepMessage.setText("第" + step + "步");
				repaint();
			}
		} else if (e.getSource() == mi0)// 重新开始
		{
			game_re();
		}/*
		 * else if(e.getSource()==mi1&&intgame_Start==0) {
		 * gameOver.setText("游戏还未开始"); JOptionPane.showMessageDialog(this,
		 * "游戏尚未开始","Tips",JOptionPane.INFORMATION_MESSAGE); } else
		 * if(e.getSource()==mi1&&intgame_Start==1&&step>=2) {
		 * //backFiveStone++; repaint(); } else
		 * if(e.getSource()==mi1&&intgame_Start==1&&step<2) {
		 * gameOver.setText("第一步不能悔棋！"); }
		 */
		else if (e.getSource() == mi2) {
			JOptionPane.showMessageDialog(this, "五子棋是我国古代的、传统的黑白棋种之一，"
					+ "\n大约在南北朝时期随围棋一起先后传入朝鲜、日本等地。" + "\n五子棋在日本叫“连珠棋”。"
					+ "\n通过一系列的规则变化使连珠五子棋这一简单的游戏复杂化、规范化，"
					+ "\n而最终成为今天的职业连珠五子棋，同时也成为一种国际比赛棋。", "五子棋文化",
					JOptionPane.INFORMATION_MESSAGE);
		} else if (e.getSource() == mi3)// 退出菜单
		{
			frame.dispose();
		} else if (e.getSource() == mi1_0_0)// 改变颜色菜单
		{
			colorSign = "blue";
			repaint();
		} else if (e.getSource() == mi1_0_1) {
			colorSign = "orange";
			repaint();
		} else if (e.getSource() == mi1_0_2) {
			colorSign = "green";
			repaint();
		} else if (e.getSource() == mi1_1_1)// 关闭禁手规则菜单
		{
			forbid = 0;

		} else if (e.getSource() == mi1_1_0)// 打开禁手规则菜单
		{
			forbid = 1;
			JOptionPane.showMessageDialog(this, "该禁手规则只适合人先手的情况，"
					+ "\n如果你选择了先手，该规则才会生效", "Tips",
					JOptionPane.INFORMATION_MESSAGE);
		} else if (e.getSource() == mi1_0_3) {
			colorSign = "lightgray";
			repaint();
		} else if (e.getSource() == mi1_0_4)// 自定义颜色
		{
			newColor = JColorChooser.showDialog(null, "自定义颜色", null);
			if (newColor != null) {
				colorSign = "new";
				repaint();
			}
		} else if (e.getSource() == mi2_1) {
			JOptionPane.showMessageDialog(this, "开发工具：eclipse 3.4.2，java"
					+ "\n打包工具：eclipse 3.2" + "\n运行环境：任何配置了Java 运行环境"
					+ "\n         （jre）的平台" + "\n关键技术：极大极小剪枝搜索"
					+ "\n实现功能：人机对弈，双人对战" + "\n级别难度：总共分为三级，适合不同水平层"
					+ "\n          次的朋友。", "相关",
					JOptionPane.INFORMATION_MESSAGE);
		} else if (e.getSource() == mi2_0) {
			JOptionPane.showMessageDialog(this, "五子棋游戏 " + "\n作者: 管超 "
					+ "\n版本:version 1.0  " + "\n性质：SIT开发", "说明",
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
		// 根据返回的单击位置，检测是否在棋盘中
		currentPos.width = e.getX();
		currentPos.height = e.getY();
		if (currentPos.width > 15 & currentPos.width < 485
				& currentPos.height > 35 & currentPos.height < 485) // 15*15的画布中
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
			// 在棋盘中才执行
			if (x != 20 && y != 20) {
				if (chessBoard[x][y] == 2) {
					set_Qizi(x, y, 1);
					c = 1;
				} else // 提醒重复落子
				{
					JOptionPane.showMessageDialog(this, "请勿重复落子", "提示",
							JOptionPane.INFORMATION_MESSAGE);
					return;
				}
				if (hasWin)// 游戏已经结束
				{
					JOptionPane.showMessageDialog(this, "游戏已经结束", "游戏结束",
							JOptionPane.INFORMATION_MESSAGE);
					return;
				}
			}
			if (isWin(x, y, 1))// 判断是否结束
			{
				gameOver.setText("游戏结束");
				if (firstTip) {
					JOptionPane.showMessageDialog(this, "你赢了", "游戏结束",
							JOptionPane.INFORMATION_MESSAGE);
					int i = JOptionPane.showConfirmDialog(null, "存储提示：是否存储本局结果？", "友情提示",
							JOptionPane.OK_CANCEL_OPTION);
					if (i == JOptionPane.YES_OPTION){
						CheckResult cr = new CheckResult();
						cr.setScore(1);
					}
					firstTip = false;
					hasWin = true;
				} else
					JOptionPane.showMessageDialog(this, "游戏已经结束", "游戏结束",
							JOptionPane.INFORMATION_MESSAGE);
				intgame_Start = 0;
				return;
			}
			if (forbid == 1 & isForbid(x, y))// 判断是否禁手
			{
				gameOver.setText("游戏结束");
				if (firstTip) {
					JOptionPane.showMessageDialog(this, "该点禁手，你输了", "游戏结束",
							JOptionPane.INFORMATION_MESSAGE);
					firstTip = false;
				} else
					JOptionPane.showMessageDialog(this, "游戏已经结束", "游戏结束",
							JOptionPane.INFORMATION_MESSAGE);
				intgame_Start = 0;
				return;
			}
			// getNext();
			// set_Qizi(locationX,locationY,0);
			computeSet(0);// //////
		}

	}

	public void set_Qizi(int x, int y, int side) // 落子
	{
		Graphics g = getGraphics();
		int a, b;
		if (step == 225)// 没有空格
		{
			gameState.setText("和局");
		}
		if (intgame_Start == 0) // 判断游戏是否开始
		{
			return;
		}

		if (chessBoard[x][y] != 2)// 不是空格
		{
			return;
		}
		if (intgame_Start == 1 && chessBoard[x][y] == 2)
			step++;
		stepMessage.setText("第" + step + "步");
		if (side == 1)// 判断黑子还是白子
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

	public void game_start_csh() // 游戏开始初始化
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
		gameOver.setText("准备就绪");
		stepMessage.setText("尚未落子");
	}

	public void game_re() // 游戏重新开始
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

	public void game_start() // 游戏开始
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
		gameOver.setText("游戏已经开始");
		if (ckbHB[1].getState()) {
			Graphics g = getGraphics();
			g.setColor(Color.black);
			g.fillOval(230, 250, 20, 20);
			chessBoard[7][7] = 0;
			// color_Qizi=0;
			step++;
			stepMessage.setText("第" + step + "步");
		}
		c = 1;
		repaint();
	}

	public int[] count(int x, int y, int ex, int ey, int k)// 该函数测试结束，运行正常
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

	public boolean makesence(int x, int y, int ex, int ey, int bwf)// 判断余下的空间能否构成五子连珠
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

	protected int findMax(int alpha, int beta, int depth)// 核心算法
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

	protected boolean isWin(int x, int y, int bw)// 判断输赢
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

	protected boolean isForbid(int x, int y)// 判断禁手
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

	static void sort2(int[][] a)// 对得到的值按照估值的大小（第二维）排序
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

	protected int getType(int x, int y, int bwf)// 判断棋型
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

	protected int getMark(int k)// 估值函数部分，不排除有更好的估值
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

	protected int evaluate()// 得到整个盘面的分数
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

	protected int[][] getBests(int bwf)// 为了减小搜索空间，先得到几个分数较高的点
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

	protected void computeSet(int bwf)// AI下棋
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
			gameOver.setText("游戏结束");
			if (firstTip) {
				JOptionPane.showMessageDialog(this, "你输了", "游戏结束",
						JOptionPane.INFORMATION_MESSAGE);
				int i = JOptionPane.showConfirmDialog(null, "存储提示：是否存储本局结果？", "友情提示",
						JOptionPane.OK_CANCEL_OPTION);
				if (i == JOptionPane.YES_OPTION){
					CheckResult cr = new CheckResult();
					cr.setScore(2);
				}
				firstTip = false;
			} else
				JOptionPane.showMessageDialog(this, "游戏已经结束", "游戏结束",
						JOptionPane.INFORMATION_MESSAGE);
			intgame_Start = 0;
		}
	}

	protected void autoUpdate()// 自动更新，多线程块
	{

		Timer time = new Timer(false);
		time.schedule(new TimerTask() {
			public void run() {

				if (intgame_Start != 1 && counter < 15) {
					repaint();
					counter++;
				}
				// tick++;
				timeText.setText(c + "秒");
				c++;
			}

		}, 0, 1000);
	}

	protected boolean randomTest(int kt) {
		Random rm = new Random();
		return rm.nextInt() % kt == 0;
	}
}
