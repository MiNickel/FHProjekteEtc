package p3;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class ReadFile {
	String text = "";
	
	public String readFile(String fileName) {
		File file = new File(fileName);
		if(!file.canRead() || !file.isFile()) {
			System.out.println("File cant be read");
		}
		BufferedReader in = null;
		try {
			in = new BufferedReader(new FileReader(fileName));
			String line = null;
			while ((line = in.readLine()) != null) {
				text = text + line + "\n";
			}
		}catch (IOException e) {
			System.out.println("Error");
		}finally {
			if(in != null) {
				try {
					in.close();
				}catch (IOException e) {
					System.out.println("Error");
				}
			}
		}
		return text;
	}
	

}
