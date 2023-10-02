grammar graphiz;

graph: 'strict'? ('graph' | 'digraph') ID '{' stmt_list '}';

stmt_list: (stmt ';' stmt_list)?;

stmt: node_stmt     # nodeStm
    | edge_stmt     # edgeStm
    | attr_stmt     # attrStm
    | id '=' id    # assignStm
    | subgraph      # subgraphStm
    ; 

attr_stmt: ('graph' | 'node' | 'edge') attr_list; 

attr_list: '[' (a_list? ']' attr_list?)?;

a_list: id '=' id (';' | ',')? a_list?;

edge_stmt: (node_id | subgraph) edgeRHS attr_list?;

edgeRHS: edgeop (node_id | subgraph) edgeRHS?;

node_stmt: node_id attr_list?;

node_id: ID (port)?;

port: ':' ID (':' compass_pt)?;

subgraph: ('subgraph' ID) '{' stmt_list '}';

compass_pt: ('n' | 'ne' | 'e' | 'se' | 's' | 'sw' | 'w' | 'nw'  | '_');

id: 
    (ID | STR | INT)
    ;
// Define tokens
INT : [0-9]+;
ID: [a-zA-Z_] [a-zA-Z_0-9]*;
WS: [ \t\n\r\f]+ -> skip ;
STR: '"' ( '\\"' | . )*? '"';
edgeop: '--' | '->';
