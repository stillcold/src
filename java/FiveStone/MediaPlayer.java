package FiveStone;

import sun.audio.*; //����sun.audio��
import java.io.*;

import javax.swing.JOptionPane;

/**
* @ClassName: MediaPlayer
* @Description: ��Ƶ���Ŵ���ģ��
* @author �ܳ�
* @date ��󱣴����� ��2011-3-22 ����03:11:37
*
*/
public class MediaPlayer {
	public MediaPlayer() {
		int i = JOptionPane.showConfirmDialog(null,
				"��ȷ���ڱ�������û�в����������ʹ��\n    �����ܣ������ظ�ռ��ϵͳ��Դ" +
				"\n                  �Ƿ�������ţ�\n   ", "��ʾ:",
				JOptionPane.YES_NO_OPTION);
		if (i == JOptionPane.OK_OPTION) {
			try {
				FileInputStream fileau = new FileInputStream("resource\\2.wav");
				AudioStream Music = new AudioStream(fileau);
				AudioPlayer.player.start(Music);
				// AudioPlayer.player.stop(Music);
			} catch (Exception f) {
			}
		} else {
		}

		
	}

	public static void main(String args[]) {
		new MediaPlayer();
	}
}
