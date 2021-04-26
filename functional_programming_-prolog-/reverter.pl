reverter(Resto1,Resto2) :- reverter(Resto1,Resto2,[]).

reverter([],Resto2,Resto2) :- !.
reverter([X|Resto],Resto2,Y) :- reverter(Resto,Resto2,[X|Y]).