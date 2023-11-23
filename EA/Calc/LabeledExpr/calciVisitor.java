// Generated from calci.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link calciParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface calciVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link calciParser#prog}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProg(calciParser.ProgContext ctx);
	/**
	 * Visit a parse tree produced by the {@code printExpr}
	 * labeled alternative in {@link calciParser#stat}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPrintExpr(calciParser.PrintExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code assign}
	 * labeled alternative in {@link calciParser#stat}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAssign(calciParser.AssignContext ctx);
	/**
	 * Visit a parse tree produced by the {@code blank}
	 * labeled alternative in {@link calciParser#stat}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBlank(calciParser.BlankContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Bitwise}
	 * labeled alternative in {@link calciParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBitwise(calciParser.BitwiseContext ctx);
	/**
	 * Visit a parse tree produced by the {@code MulDivi}
	 * labeled alternative in {@link calciParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMulDivi(calciParser.MulDiviContext ctx);
	/**
	 * Visit a parse tree produced by the {@code AddSub}
	 * labeled alternative in {@link calciParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAddSub(calciParser.AddSubContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Parens}
	 * labeled alternative in {@link calciParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitParens(calciParser.ParensContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Id}
	 * labeled alternative in {@link calciParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitId(calciParser.IdContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Int}
	 * labeled alternative in {@link calciParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInt(calciParser.IntContext ctx);
}