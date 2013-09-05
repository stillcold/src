package FiveStone;

import java.awt.Button;
import java.awt.Font;
import java.awt.Insets;
import java.awt.Label;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.FileInputStream;
import java.io.FileOutputStream;

import javax.swing.ImageIcon;
import javax.swing.JDialog;
import javax.swing.JOptionPane;
import javax.swing.JTextArea;

/**
* @ClassName: CheckResult
* @Description: 查看和保存战绩
* @author 管超
* @date 最后保存日期： 2011-3-22 下午03:12:38
*
*/
public class CheckResult implements ActionListener{
	Button b1 = new Button("清 空 记录");
	static int score[] = new int[11];
	static JDialog paihang = new JDialog();
	static JTextArea paihangtext = new JTextArea();
	static JTextArea dlg_1_text=new JTextArea();
	static JDialog dlg_1=new JDialog();
	static ImageIcon icon=new ImageIcon("resource/FiveStone.jpg");

	public void getResult() {
		String strpai = null;
		String st = "";
		char paih[] = new char[50];

		int offset = 0, count = 0, j = 0;
		try {
			FileInputStream io = new FileInputStream("resource/score.txt");// 得到路径
			byte a[] = new byte[io.available()];
			io.read(a);
			io.close();
			strpai = new String(a);
		} catch (Exception g) {
		}
		paih = strpai.toCharArray();
		for (int i = 0; i < strpai.toCharArray().length; i++) {
			if (paih[i] != '#')// #只是一个标记
			{
				count++;
			}
			if (paih[i] == '#') {
				score[j] = Integer.parseInt(st.valueOf(paih, offset, count));
				offset += count + 1;
				count = 0;
				j++;
			}
		}
	}

	public void setScore(int s) {
		getResult();
		String str = "";
		String str1 = "";
		if (score[9] != 0) {
			int i = JOptionPane.showConfirmDialog(null, "tips",
					"存储空间已满，本次存储操作放弃，需要清理以后才能继续存储，是否继续？",
					JOptionPane.OK_CANCEL_OPTION);
			if (i == JOptionPane.YES_OPTION) {
				clearScore();
				return;
			} else
				return;
		}
		for (int i = 0; i < 10; i++) {
			if (score[i] == 0) {
				str = str.valueOf(s);
				str = str.concat("#");
				str1 = str1.concat(str);
				break;
			} else {
				str = str.valueOf(score[i]);
				str = str.concat("#");
				str1 = str1.concat(str);
			}
		}
		try {
			FileOutputStream fo = new FileOutputStream("resource/score.txt");
			fo.write(str1.getBytes());
			fo.close();
		} catch (Exception h) {
		}
	}

	public void clearScore() {
		Label lab = new Label("真的要清空战绩 ?");
		int i = JOptionPane.showConfirmDialog(null, lab, "清空战绩",
				JOptionPane.OK_CANCEL_OPTION);
		if (i == JOptionPane.YES_OPTION) {
			paihangtext.setText("");
			String str = "0#0#0#0#0#0#0#0#0#0#";
			try {
				FileOutputStream fo = new FileOutputStream("resource/score.txt");
				fo.write(str.getBytes());
				fo.close();
			} catch (Exception h) {
			}
		}
	}

	public void displayScore() {
		getResult();
		int i;
		Insets ints = new Insets(10, 130, 0, 10);
		paihang.setLayout(null);
		paihang.setTitle("★ 游戏信息统计 ★");
		// paihang.setIconImage(icon.getImage());
		paihang.setSize(490, 370);
		paihang.setLocation(250, 150);
		paihangtext.setText("");
		paihangtext.setBounds(0, 0, 485, 300);
		paihang.add(paihangtext);
		paihang.add(b1);
		b1.setBounds(5, 305, 470, 30);
		b1.addActionListener(this);
		paihangtext.setFont(new Font("宋体", Font.PLAIN, 20));
		paihang.setResizable(false);
		paihangtext.setEditable(false);
		paihangtext.setMargin(ints);
		paihangtext.setText("★   游戏信息统计   ★" + "\n");
		if (score[0] == 0){
			paihangtext.setMargin(ints);// 设置文本在中间显示
			paihangtext.append("目前无统计信息！");
		}
		for (i = 0; i < 9; i++) {
			if ((score[i] != 0)) {
				paihangtext.setMargin(ints);// 设置文本在中间显示
				paihangtext.append("第  " + (i + 1) + "  局      "
						+ (score[i] == 1 ? "胜    √" : "败    ×") + "\n");
			} else
				continue;
		}
		if (score[i] != 0)
			paihangtext.append("第  " + (i + 1) + " 局      "
					+ (score[i] == 1 ? "胜    √" : "败    ×") + "\n");
		paihang.show();
		paihang.addWindowListener(new WinLis1());
	}
	public void readMessage()
	{
		dlg_1_text.setText("");
		try{
        FileInputStream io=new FileInputStream("resource/guanyu.txt");//得到路径
	    byte a[]=new byte[io.available()];
	    io.read(a);
	    io.close();
	    String strguanyu=new String(a);
	    dlg_1_text.setFont(new Font("宋体",Font.PLAIN,20));
	    dlg_1_text.setSize(100,100);
	    dlg_1_text.setEditable(false);
	    dlg_1_text.setText(strguanyu);
	    }
	    catch(Exception a){
		}
		
		dlg_1.setTitle("★  有关五子棋介绍 ★ ");
		dlg_1.setSize(400,220);
		dlg_1.add(dlg_1_text);
		dlg_1.setLocation (350,250);
		//dlg_1.setIconImage(icon.getImage());
		dlg_1.setResizable(false);
		dlg_1.show();
		dlg_1.addWindowListener(new WinLis1());
	}

	static class WinLis1 extends WindowAdapter {
		public void windowClosing(WindowEvent e) {
			dlg_1.dispose();
			// dlg_2.dispose();
			paihang.dispose();
		}
	}
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == b1){
			clearScore();
		}
	}
	public static void main(String args[]) {
		CheckResult cr = new CheckResult();
		cr.displayScore();
		// cr.clearScore();
		cr.setScore(1);
		cr.readMessage();
	}


}
