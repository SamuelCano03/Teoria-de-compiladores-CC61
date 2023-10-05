import java.io.FileInputStream;
import java.io.InputStream;

import org.antlr.v4.runtime.*;
public class tokens {
    public static void main(String[] args) throws Exception {
        String inputFile = null;
		if (args.length > 0) inputFile = args[0];
		InputStream is = System.in;
		if (inputFile != null) is = new FileInputStream(inputFile);
		CharStream input = CharStreams.fromStream(is);
		graphizLexer lexer = new graphizLexer(input);
		CommonTokenStream tokenStream = new CommonTokenStream(lexer);
        
        for (Token token : tokenStream.getTokens()) {
            System.out.print("'" + token.getText() + "<" + token.getType() + ">' ");
        }

		
    }
    
    
}
