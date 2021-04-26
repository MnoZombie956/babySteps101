nelementos([],0).
nelementos([_|Resto], Nexttam ) :- nelementos(Resto,Tam), Nexttam is Tam+1.