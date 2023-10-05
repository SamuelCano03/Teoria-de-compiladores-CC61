import java.io.FileInputStream;
import java.io.InputStream;
import java.util.List;
import java.util.Map;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;

public class translate {
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
		ParseTreeWalker walker = new ParseTreeWalker();
        listener myListener = new listener();
        Map<String, List<Object[]>> obj=myListener.tupleMap;


       
		walker.walk(myListener, tree);
        
        imprimirMapComoJSON(obj);
	}
    
    private static void imprimirMapComoJSON(Map<String, List<Object[]>> resultado) {
        System.out.print("{");
        for (Map.Entry<String, List<Object[]>> entry : resultado.entrySet()) {
            String clave = entry.getKey();
            List<Object[]> lista = entry.getValue();
            
            System.out.print("\"" + clave + "\":{\n");
            for (int i = 0; i < lista.size(); i++) {
                Object[] tupla = lista.get(i);
                String elemento1 = (String) tupla[0];
                String elemento2 = (String) tupla[1];
                
                System.out.print("\t[\"" + elemento1 + "\"," + elemento2 + "]");
                if (i < lista.size() - 1) {
                    System.out.print(",\n");
                }
            }
            System.out.print("\n}");
            
            if (!entry.equals(resultado.entrySet().toArray()[resultado.size() - 1])) {
                System.out.print(",\n");
            }
        }
        System.out.println("\n}");
    }
}
