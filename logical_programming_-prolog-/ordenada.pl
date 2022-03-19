%aproveitando da lista IV de prolog
menor(X,[],[X]).
menor(X,[Y|Resto],[X,Y|Resto]):-X=<Y.
menor(X,[Y|Resto],[Y|Resto2]):-X>Y,menor(X,Resto,Resto2).
ordenarDois([],Menor,Menor).
ordenarDois([X|Resto],Menor,Ans):-menor(X,Menor,Resto2),ordenarDois(Resto,Resto2,Ans).
ordenar(List,Ans):-ordenarDois(List,[],Ans).

ordenada(X):- ordenar(X, Ordem), Ordem == X.
