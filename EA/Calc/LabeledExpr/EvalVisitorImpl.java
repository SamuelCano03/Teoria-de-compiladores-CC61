import java.util.HashMap;
import java.util.Map;

/* added the Impl at the end of the class to avoid it being .gitignored sorry */
public class EvalVisitorImpl extends calciBaseVisitor<Integer> {
	Map<String, Integer> memory = new HashMap<String, Integer>();

	/* ID '=' expr NEWLINE */
	@Override
	public Integer visitAssign(calciParser.AssignContext ctx) {
		String id = ctx.ID().getText();
		int value = visit(ctx.expr());
		memory.put(id, value);
		return value;
	}

	/* expr NEWLINE */
	@Override
	public Integer visitPrintExpr(calciParser.PrintExprContext ctx) {
		Integer value = visit(ctx.expr());
		System.out.println(value);
		return 0;
	}

	/* INT */
	@Override
	public Integer visitInt(calciParser.IntContext ctx) {
		return Integer.valueOf(ctx.INT().getText());
	}

	/* ID */
	@Override
	public Integer visitId(calciParser.IdContext ctx) {
		String id = ctx.ID().getText();
		if (memory.containsKey(id)) return memory.get(id);
		return 0;
	}

	/* expr expr op=('^'|'|'| '&')  */
	@Override
	public Integer visitBitwise(calciParser.BitwiseContext ctx) {
		int left = visit(ctx.expr(0));
		int right = visit(ctx.expr(1));
		if (ctx.op.getType() == calciParser.AND) {

			return (left | right);
		} 
		else if( ctx.op.getType() == calciLexer.AND){
			return (left & right);
		}
		else{
			return (left ^ right);
		}
	}

	/* expr expr op=('*'|'/')  */
	@Override
	public Integer visitMulDivi(calciParser.MulDiviContext ctx) {
		int left = visit(ctx.expr(0));
		int right = visit(ctx.expr(1));
		if (ctx.op.getType() == calciParser.MUL) {
			return left * right;
		} else {
			return left / right;
		}
	}

	/* expr expr op=('+'|'-')  */
	@Override
	public Integer visitAddSub(calciParser.AddSubContext ctx) {
		int left = visit(ctx.expr(0));
		int right = visit(ctx.expr(1));
		if (ctx.op.getType() == calciParser.ADD) {
			return left + right;
		} else {
			return left - right;
		}
	}
	
	/* '(' expr ')' */
	@Override
	public Integer visitParens(calciParser.ParensContext ctx) {
		return visit(ctx.expr());
	}
}