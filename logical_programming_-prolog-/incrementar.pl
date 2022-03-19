incrementar([],[]).
incrementar([X | List], [X2 | List2]) :- incrementar(List,List2), X2 is X + 1.
