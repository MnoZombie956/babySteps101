concatenar([], L, L).
concatenar([X|L1], L2, [X|L3]) :- concatenar(L1, L2, L3).

linearizar([[X|Resto]|Resto1],[X|Resto2]) :- concatenar(Resto,Resto1,Resto2).