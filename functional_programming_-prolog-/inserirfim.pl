inserirfim(X,[],[X]).
inserirfim(X,[Y|Resto],[Y|Resto1]):-inserirfim(X,Resto,Resto1).