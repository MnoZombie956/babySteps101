split(0,L,[],L).
split(N,[X|Xs],[X|Ys],Zs) :- N > 0, N1 is N - 1, split(N1,Xs,Ys,Zs).
rotacionar(_,[],[]) :- !.
rotacionar(L1,L2) :- split(1,L1,S1,S2), append(S2,S1,L2).
