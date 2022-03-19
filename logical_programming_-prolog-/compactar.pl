remove(X,[],[],[X]).
remove(X,[Y|Resto2],[Y|Resto2],[X]) :- X \= Y.
remove(X,[X|Resto1],Resto2,[X|Resto1_cmp]) :- remove(X,Resto1,Resto2,Resto1_cmp).
numLetra([],[]).
numLetra([[X|Resto1]|Resto2],[[Z,X]|Resto1_cmp]) :- numLetra(Resto2,Resto1_cmp),length([X|Resto1],Z).
junta([],[]).
junta([X|Resto1],[Z|Resto1_cmp]) :- remove(X,Resto1,Resto2,Z), junta(Resto2,Resto1_cmp).


compactar(Lista1,ListaRetorno) :- numLetra(JuntaSoma,ListaRetorno),junta(Lista1,JuntaSoma).
