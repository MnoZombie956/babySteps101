nelementos([],0).
nelementos([_|Resto], Nexttam ) :- nelementos(Resto,Tam), Nexttam is Tam+1.
split(0,L,[],L).
split(N,[X|Xs],[X|Ys],Zs) :- N > 0, N1 is N - 1, split(N1,Xs,Ys,Zs).

rotacionarn(_,[],[]) :- !.
rotacionarn(N,L1,L2) :- nelementos(L1,NL1), N1 is N mod NL1, split(N1,L1,S1,S2), append(S2,S1,L2).
