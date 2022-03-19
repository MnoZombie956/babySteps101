lembraMaior([],Y,Y).
lembraMaior([X|Resto],Y,Maior) :- X > Y,lembraMaior(Resto,X,Maior).
lembraMaior([X|Resto],Y,Maior) :- X =< Y, lembraMaior(Resto,Y,Maior).
maior(Lista,Maior) :- Lista = [X|_], lembraMaior(Lista,X,Maior).
