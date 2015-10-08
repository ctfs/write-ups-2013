import java.io.*;
import java.util.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
class Untitled {
  public static void main(String[] args) throws Exception {
		BufferedImage image = ImageIO.read(new File("/Users/andy/Desktop/steg.png"));
		String fin = "";
		File file = new File("/Users/andy/Desktop/loloutput.txt");
		if (!file.exists()) {
			file.createNewFile();
		}
		FileWriter fw = new FileWriter(file.getAbsoluteFile());
		BufferedWriter bw = new BufferedWriter(fw);
								
		for(int y=0;y<image.getHeight();y++) {
			for(int x=0; x<image.getWidth();x++) {
				String r = pad(Integer.toBinaryString((image.getRGB(x,y))&0xFF)).substring(7);
				String g = pad(Integer.toBinaryString((image.getRGB(x,y)>>8)&0xFF)).substring(7);
				String b = pad(Integer.toBinaryString((image.getRGB(x,y)>>16)&0xFF)).substring(7);
				bw.write(b+g+r);
			}
		}			
	}
	static String pad(String s) {
		while(s.length()!=8) s="0"+s;
		return s;
	}
}
