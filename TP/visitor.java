import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.List;

import java.io.FileInputStream;
import java.io.InputStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;

public class visitor extends graphizBaseListener{
    public Map<String, List<Object[]>> tupleMap = new HashMap<>();
    public void agregar(String clave, Object[] valor) {
        // Verificamos si la clave ya existe en el mapa
        if (tupleMap.containsKey(clave)) {
            // Si la clave ya existe, obtenemos la lista actual y le añadimos el valor
            List<Object[]> listaActual = tupleMap.get(clave);
            listaActual.add(valor);
        } else {
            // Si la clave no existe, creamos una nueva lista y añadimos el valor
            List<Object[]> nuevaLista = new ArrayList<>();
            nuevaLista.add(valor);
            tupleMap.put(clave, nuevaLista);
        }
    }
    /* edge_stmt */
    @Override
    public void enterEdge_stmt(graphizParser.Edge_stmtContext ctx){
        
        String src = ctx.node_id().ID().getText();
        String edge = ctx.edgeRHS().node_id().getText();
        String weight;
        if(ctx.attr_list() != null && ctx.attr_list().a_list() !=null){
            weight=ctx.attr_list().a_list().id(1).getText();
        }
        else{
            weight="0";
        }
        agregar(src, new Object []{edge, weight});

    }

}
