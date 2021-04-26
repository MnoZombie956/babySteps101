remover(_, [], []).
remover(X, [X|Resto], Y) :- remover(X, Resto, Y).
remover(X, [Y|Resto], [Y|Resto2]) :- dif(X, Y), remover(X, Resto, Resto2).

%remover(X, [X|T], T).
%remover(X, [Y|T], [Y|NT]) :- X \== Y, remover(X, T, NT).

%remover(X,[X|Tail],Tail).
%remover(X,[Y|Tail],[Y|Tail1]):- remover(X,Tail,Tail1).
