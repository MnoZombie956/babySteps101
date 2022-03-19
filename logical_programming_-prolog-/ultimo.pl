ultimo([X],X).
ultimo([_|Resto],X) :- ultimo(Resto,X).
