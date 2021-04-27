primeiroLista [] = 0
--primeiroLista [_] = 0
primeiroLista (x:resto) = x --head

cauda [] = []
cauda (x:resto) =
  [x1 | x1 <- resto]

somaParciais [x] = [x]--caso contrario continuariam dando appending to infinity
somaParciais [] = [] --so pra cobrir o caso de lista vazia
somaParciais (x:resto) =
  [x]++somaParciais([x + primeiroLista (resto)]++cauda(resto))--criaLista([x]++resto) 

main = do
	let lista = [2,16,5,4]
	print(somaParciais lista)