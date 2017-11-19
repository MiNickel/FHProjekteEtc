package p3;

import java.util.Properties;

import javax.activation.DataHandler;
import javax.activation.DataSource;
import javax.activation.FileDataSource;
import javax.mail.BodyPart;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Multipart;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;

public class Mail {

	public static void main(String[] args) {
		//Inhalt einlesen
		ReadFile contentReader = new ReadFile();
		String mailText = contentReader.readFile("C:/Users/Jan Augstein/eclipse-workspace/VSPraktikum3Mail/src/inhalt.txt");
		//Empfaengerliste einlesen und in Array eintragen
		ReadFile recipientReader = new ReadFile();
		String recipList = recipientReader.readFile("C:/Users/Jan Augstein/eclipse-workspace/VSPraktikum3Mail/src/empfaenger.txt");
		String recipient[] = recipList.split("\n");
		//Attribut
		String email = "jaugstein@fh-bielefeld.de";
		//Eigenschaften
		Properties props = new Properties();
		props.setProperty("mail.transport.protocol", "smtp");
		props.setProperty("mail.smtp.host", "smtp.fh-bielefeld.de");
		props.setProperty("mail.smtp.port", "587");
		props.setProperty("mail.smtp.auth", "true");
		props.setProperty("mail.smtp.starttls.enable", "true");
		//Session erstellen und Authentication durchführen
		Session session = Session.getInstance(props, new javax.mail.Authenticator() {
			protected PasswordAuthentication getPasswordAuthentication() {
				return new PasswordAuthentication("jaugstein@fh-bielefeld.de", "jan97315");
			}
		});
		
		try {
			//E-Mail erstellen mit Betreff und Sender
			Message message = new MimeMessage(session);
			message.setFrom(new InternetAddress(email));
			message.setSubject("Test E-Mail");
			//Text erstellen
			BodyPart msgBodyPart = new MimeBodyPart();
			msgBodyPart.setText(mailText);
			Multipart multipart = new MimeMultipart();
			multipart.addBodyPart(msgBodyPart);
			//Anhang erstellen
			DataSource source = new FileDataSource("C:/Users/Jan Augstein/eclipse-workspace/VSPraktikum3Mail/src/quellen.txt");
			msgBodyPart = new MimeBodyPart();
			msgBodyPart.setDataHandler(new DataHandler(source));
			msgBodyPart.setFileName("quellen.txt");
			multipart.addBodyPart(msgBodyPart);
			//E-Mail Inhalt setzen
			message.setContent(multipart);
			//E-Mail an alle aus der Liste schicken
			for(int i=0;i<recipient.length;i++) {
				System.out.println(i);
				message.setRecipients(Message.RecipientType.TO, InternetAddress.parse(recipient[i]));
				System.out.println(i);
				Transport.send(message);
			}
			System.out.println("Erfolg");
		}catch (MessagingException mex) {
			mex.printStackTrace();
		}

	}

}
