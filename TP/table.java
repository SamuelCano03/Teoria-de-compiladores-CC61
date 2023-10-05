import java.io.FileInputStream;
import java.io.InputStream;

import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
public class table {
    public static void main(String[] args) throws Exception {
        String inputFile = null;
		if (args.length > 0) inputFile = args[0];
		InputStream is = System.in;
		if (inputFile != null) is = new FileInputStream(inputFile);
		CharStream input = CharStreams.fromStream(is);
		graphizLexer lexer = new graphizLexer(input);
		CommonTokenStream tokens = new CommonTokenStream(lexer);
        
		graphizParser parser = new graphizParser(tokens);
		ParseTree tree = parser.graph();

		System.out.println(tree.toStringTree(parser));
    }
}
