ordenarDois([],Menor,Menor).
ordenarDois([X|Resto],Menor,Ans):-menor(X,Menor,Resto2),ordenarDois(Resto,Resto2,Ans).
   
menor(X,[Y|Resto],[Y|Resto2]):-X>Y,menor(X,Resto,Resto2).
menor(X,[Y|Resto],[X,Y|Resto]):-X=<Y.
menor(X,[],[X]).

ordenar(List,Ans):-ordenarDois(List,[],Ans).