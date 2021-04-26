gerar(P,P,[P]).
gerar(P,U,[P|Resto]) :- P < U, Pnext is P + 1, gerar(Pnext,U,Resto).