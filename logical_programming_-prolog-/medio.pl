nelementos([],0).
nelementos([_|Resto], Nexttam ) :- nelementos(Resto,Tam), Nexttam is Tam+1.
soma([],0).
soma([X|Resto],Acumula):-soma(Resto,Temp),Acumula=Temp+X.
medio(L,Ans) :- soma(L,Soma), nelementos(L,QntE), Ans is Soma/QntE.
            
