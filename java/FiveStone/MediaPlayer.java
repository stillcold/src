package FiveStone;

import sun.audio.*; //引入sun.audio包
import java.io.*;

import javax.swing.JOptionPane;

/**
* @ClassName: MediaPlayer
* @Description: 音频播放处理模块
* @author 管超
* @date 最后保存日期 ：2011-3-22 下午03:11:37
*
*/
public class MediaPlayer {
	public MediaPlayer() {
		int i = JOptionPane.showConfirmDialog(null,
				"请确保在背景音乐没有播出的情况下使用\n    本功能，否则将重复占用系统资源" +
				"\n                  是否继续播放？\n   ", "提示:",
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
