// Generated from graphiz.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link graphizParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface graphizVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link graphizParser#graph}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGraph(graphizParser.GraphContext ctx);
	/**
	 * Visit a parse tree produced by {@link graphizParser#stmt_list}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStmt_list(graphizParser.Stmt_listContext ctx);
	/**
	 * Visit a parse tree produced by the {@code nodeStm}
	 * labeled alternative in {@link graphizParser#stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNodeStm(graphizParser.NodeStmContext ctx);
	/**
	 * Visit a parse tree produced by the {@code edgeStm}
	 * labeled alternative in {@link graphizParser#stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEdgeStm(graphizParser.EdgeStmContext ctx);
	/**
	 * Visit a parse tree produced by the {@code attrStm}
	 * labeled alternative in {@link graphizParser#stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAttrStm(graphizParser.AttrStmContext ctx);
	/**
	 * Visit a parse tree produced by the {@code assignStm}
	 * labeled alternative in {@link graphizParser#stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAssignStm(graphizParser.AssignStmContext ctx);
	/**
	 * Visit a parse tree produced by the {@code subgraphStm}
	 * labeled alternative in {@link graphizParser#stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSubgraphStm(graphizParser.SubgraphStmContext ctx);
	/**
	 * Visit a parse tree produced by {@link graphizParser#attr_stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAttr_stmt(graphizParser.Attr_stmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link graphizParser#attr_list}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAttr_list(graphizParser.Attr_listContext ctx);
	/**
	 * Visit a parse tree produced by {@link graphizParser#a_list}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitA_list(graphizParser.A_listContext ctx);
	/**
	 * Visit a parse tree produced by {@link graphizParser#edge_stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEdge_stmt(graphizParser.Edge_stmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link graphizParser#edgeRHS}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEdgeRHS(graphizParser.EdgeRHSContext ctx);
	/**
	 * Visit a parse tree produced by {@link graphizParser#node_stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNode_stmt(graphizParser.Node_stmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link graphizParser#node_id}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNode_id(graphizParser.Node_idContext ctx);
	/**
	 * Visit a parse tree produced by {@link graphizParser#port}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPort(graphizParser.PortContext ctx);
	/**
	 * Visit a parse tree produced by {@link graphizParser#subgraph}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSubgraph(graphizParser.SubgraphContext ctx);
	/**
	 * Visit a parse tree produced by {@link graphizParser#compass_pt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCompass_pt(graphizParser.Compass_ptContext ctx);
	/**
	 * Visit a parse tree produced by {@link graphizParser#id}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitId(graphizParser.IdContext ctx);
	/**
	 * Visit a parse tree produced by {@link graphizParser#edgeop}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEdgeop(graphizParser.EdgeopContext ctx);
}